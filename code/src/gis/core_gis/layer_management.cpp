#include "layer_management.h"

#include <algorithm>

#include "Layer.h"
#include "layer_controller.h"
#include "layer_renderer.h"
#include "layer_configurator.h"

#include "sdl_application/sdl_application.h"

#include "utility/parameter_set.h"

#include "spdlog/spdlog.h"

namespace gis {
    bool LayerManagement::Initialize() {
        mIsInitialized = true;

        LayerConfigurator configurator(this);
        configurator.Configure(mLayerConfigurationPath);

        // Katmanlari ilklendirelim
        for (auto& layer : mLayers) {
            if (false == layer->Initialize()) {
                spdlog::info("Layer {} initialization failed!", layer->Name());
            }
        }
        
        ResetIterator();
        
        return mIsInitialized;
    }

    void LayerManagement::Update()    {
        // Katman islerini burada hallediyoruz
        while (!mLayerOps.IsEmpty()) {
            std::pair<LayerOp, unsigned int> opToConsume;
            mLayerOps.Pop(opToConsume);
            if (opToConsume.first == LayerOp::MoveUp) {
                if (opToConsume.second >= 1) {
                    auto itr_i = std::next(mLayers.begin(), opToConsume.second);
                    auto itr_j = std::next(mLayers.begin(), opToConsume.second - 1);

                    std::iter_swap(itr_i, itr_j);
                }
            }
            else if (opToConsume.first == LayerOp::MoveDown) {
                if (opToConsume.second < (mLayers.size() - 1)) {
                    auto itr_i = std::next(mLayers.begin(), opToConsume.second);
                    auto itr_j = std::next(mLayers.begin(), opToConsume.second + 1);

                    std::iter_swap(itr_i, itr_j);
                }
            }
        }

        // Ilk cizilen arkada kalacagiz icin geriden geliyoruz
        for (const auto& layer : mLayers) {
            if (layer->Status() != LayerStatus::NotActive) {
                auto controller = layer->Controller();
                
                if (nullptr != controller)
                    controller->Update();
            }    
        } 
    } 

    void LayerManagement::Display() {
        // UI disindaki katmanlari once cizdirelim
        // Ilk cizilen arkada kalacagiz icin geriden geliyoruz
        for (const auto& layer : mLayers) {
            if (true == layer->IsLayerVisible()
                && 
                LayerType::UI != layer->Type()) {
                auto renderer = layer->Renderer();
                
                if (nullptr != renderer)
                    renderer->DisplayGeometry();
            }
        }

        // Label display pass
        // Ilk cizilen arkada kalacagiz icin geriden geliyoruz
        for (const auto& layer : mLayers) {
            if (true == layer->IsLayerVisible()
                &&
                true == layer->HasLabelDisplay()
                &&
                LayerType::UI != layer->Type()) {
                auto renderer = layer->Renderer();

                if (nullptr != renderer)
                    renderer->DisplayLabel();
            }
        }

        // UI katmanlari cizdirelim
        if (mPreUIHook != nullptr)
            mPreUIHook(mSDLParams.IsGLEnabled);

        for (const auto& layer : mLayers) {
            if (true == layer->IsLayerVisible()
                &&
                LayerType::UI == layer->Type()) {
                auto renderer = layer->Renderer();

                if (nullptr != renderer)
                    renderer->DisplayLabel();
            }
        }

        if (mPostUIHook != nullptr)
            mPostUIHook(mSDLParams.IsGLEnabled);
    }

    void LayerManagement::AddLayer(SharedLayer layer, uint32_t priority) {
        if (layer != nullptr)  {
            auto layerIndex = priority;

            if (layerIndex > static_cast<uint32_t>(mLayers.size())) {
                layerIndex = static_cast<uint32_t>(mLayers.size());
            }
            mLayers.insert(mLayers.begin() + layerIndex, layer);
        }
        else {
            spdlog::error("Null layer is provided for add!");
        }
    }

    void LayerManagement::RegisterLayerFactory(std::unique_ptr<LayerFactory> layerFactory) {
        auto layerTypeStr = static_cast<std::string>(layerFactory->LayerType());

        mLayerFactories[layerTypeStr] = std::move(layerFactory);
        mLayerFactories[layerTypeStr]->SetMapView(mMapView);
        mLayerFactories[layerTypeStr]->SetSDLApplication(mSDLApplication);
        mLayerFactories[layerTypeStr]->SetLayerIterator(this);
        mLayerFactories[layerTypeStr]->SetLayerService(this);
    }

    void LayerManagement::SetPreUIDisplayHook(std::function<void(bool)> hookFunc) {
        mPreUIHook = hookFunc;
    }

    void LayerManagement::SetPostUIDisplayHook(std::function<void(bool)> hookFunc) {
        mPostUIHook = hookFunc;
    }

    std::optional<LayerService::SharedLayer> LayerManagement::Layer(std::string_view layerName) {
        if (auto itr = FindLayerByName(layerName); itr != mLayers.end()) {
            return *itr;
        }
        else {
            return std::nullopt;
        }
    }

    std::optional<LayerStatus> LayerManagement::Status(std::string_view layerName)    {
        if (auto itr = FindLayerByName(layerName); itr != mLayers.end()) {
            return (*itr)->Status();
        }
        else {
            return std::nullopt;
        }
    }

    void LayerManagement::SetStatus(std::string_view layerName, LayerStatus layerStatus) {
        if (auto itr = FindLayerByName(layerName); itr != mLayers.end()) {
            return (*itr)->SetStatus(layerStatus);
        }
    }
    
    void LayerManagement::SetMapView(std::shared_ptr<gis::MapView> mapView) {
        mMapView = mapView;
        
        for (auto& layerFactory : mLayerFactories) {
            layerFactory.second->SetMapView(mMapView);
        }
    }

    void LayerManagement::SetSDLApplication(SdlApplication* sdlApplication) {
        mSDLApplication = sdlApplication;
        mSDLParams = mSDLApplication->GetSDLParameters();

        for (auto& layerFactory : mLayerFactories) {
            layerFactory.second->SetSDLApplication(mSDLApplication);
        }
    }

    void LayerManagement::SetLayerConfigurationPath(std::string_view path) {
        mLayerConfigurationPath = static_cast<std::string>(path);
    }

    void LayerManagement::ResetIterator() {
        mCurrentLayerIndex = 0;
    }

    void LayerManagement::Next() {
        mCurrentLayerIndex++;

        if (mCurrentLayerIndex >= mLayers.size()){
            mCurrentLayerIndex = static_cast<int>(mLayers.size());
        }
    }

    bool LayerManagement::IsDone() const {
        return mCurrentLayerIndex >= mLayers.size();
    }
    
    LayerService::SharedLayer LayerManagement::Current() {
        return mLayers[mCurrentLayerIndex];
    }

    std::vector<LayerService::SharedLayer>::iterator LayerManagement::FindLayerByName(std::string_view layerName) {
        return std::find_if(mLayers.begin(), mLayers.end(), [layerName](SharedLayer item) {
            return (layerName == item->Name());
            });
    }
    
    void LayerManagement::CreateLayer(std::string_view factoryName, ParameterSet layerMetadata) {
        std::string factoryNameStr;
        uint32_t priority;

        layerMetadata.GetParameterValue<std::string>("LayerFactory", factoryNameStr);
        layerMetadata.GetParameterValue<uint32_t>("Priority", priority);

        if (mLayerFactories.contains(factoryNameStr)) {
            AddLayer(mLayerFactories[factoryNameStr]->CreateLayer(layerMetadata), priority);
        }
    }

    unsigned int LayerManagement::Size() const {
        return static_cast<unsigned int>(mLayers.size());
    }
    
    void LayerManagement::MoveUp(int layerIndexToMove) {
        auto opToAdd = std::make_pair<LayerOp, unsigned int>(LayerOp::MoveUp, layerIndexToMove);
        mLayerOps.Push(opToAdd);
    }

    void LayerManagement::MoveDown(int layerIndexToMove) {
        auto opToAdd = std::make_pair<LayerOp, unsigned int>(LayerOp::MoveDown, layerIndexToMove);
        mLayerOps.Push(opToAdd);
    }
}