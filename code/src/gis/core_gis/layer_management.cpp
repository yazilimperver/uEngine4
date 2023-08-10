#include "layer_management.h"

#include <algorithm>

#include "Layer.h"
#include "layer_controller.h"
#include "layer_renderer.h"
#include "layer_configurator.h"

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
				spdlog::info("Layer {} initialization failed!", layer->GetLayerName());
			}
		}
		
		ResetIterator();
		
		return mIsInitialized;
	}

	void LayerManagement::Update()	{
		auto itr = mLayers.cbegin();
		while(itr != mLayers.cend()){
			if ((*itr)->GetLayerStatus() != LayerStatus::NotActive)	{
				auto controller = (*itr)->Get2DController();
				controller->Update();
			}	

			itr++;
		}
	}

	void LayerManagement::Display() {

		//! Geometry display pass
		auto itr = mLayers.cbegin();
		while (itr != mLayers.cend()) {
			if (true == (*itr)->IsLayerVisible()) {
				auto renderer = (*itr)->Get2DRenderer();
				renderer->DisplayGeometry();
			}

			itr++;
		}

		// Label display pass
		auto labelItr = mLayersWithLabel.cbegin();
		
		while (labelItr != mLayersWithLabel.cend())	{
			if (true == (*labelItr)->IsLayerVisible()) {
				auto renderer = (*labelItr)->Get2DRenderer();
				renderer->DisplayLabel();
			}

			labelItr++;
		}
	}

	void LayerManagement::AddLayer(std::shared_ptr<Layer> Layer)	{
		if (Layer != nullptr)  {
			auto itr = mRegisteredLayers.find(Layer->GetLayerName());

			if (itr == mRegisteredLayers.end()) {
				mLayers.push_back(Layer);
				mRegisteredLayers[Layer->GetLayerName()] = Layer;

				if (Layer->HasLayerLabelDisplay()) {
					mLayersWithLabel.push_back(Layer);
				}
			}
		}
	}

	void LayerManagement::RegisterLayerFactory(std::unique_ptr<LayerFactory> layerFactory) {
		auto layerTypeStr = static_cast<std::string>(layerFactory->LayerType());

		mLayerFactories[layerTypeStr] = std::move(layerFactory);
		mLayerFactories[layerTypeStr]->SetMapView(mMapView);
		mLayerFactories[layerTypeStr]->SetSDLApplication(mSDLApplication);
	}

	std::optional<std::shared_ptr<Layer>> LayerManagement::GetLayer(const std::string& layerName) {
		auto itr = std::find_if(mLayers.begin(), mLayers.end(), [layerName](std::shared_ptr<Layer> item) {
			return (layerName == item->GetLayerName());
		});

		if (itr != mLayers.end()) {
			return *itr;
		}
		else {
			return std::nullopt;
		}
	}

	std::optional<std::shared_ptr<Layer>> LayerManagement::GetLayer(int32_t layerHandle) {
		if (layerHandle < static_cast<int32_t>(mLayers.size())) {
			return mLayers[layerHandle];
		}
		else {
			return std::nullopt;
		}
	}

	std::optional<LayerStatus> LayerManagement::GetLayerStatus(int32_t layerHandle) {
		if (layerHandle < static_cast<int32_t>(mLayers.size()))	{
			return mLayers[layerHandle]->GetLayerStatus();
		}
		else {
			return std::nullopt;
		}
	}

	std::optional<LayerStatus> LayerManagement::GetLayerStatus(const std::string& layerName)	{
		auto itr = mRegisteredLayers.find(layerName);

		if (itr != mRegisteredLayers.end()){
			return itr->second->GetLayerStatus();
		}
		else {
			return std::nullopt;
		}
	}

	std::optional<int32_t> LayerManagement::GetLayerHandle(const std::string& layerName) {
		return 0;
	}

	void LayerManagement::SetLayerStatus(const std::string& layerName, LayerStatus layerStatus) {
		auto itr = mRegisteredLayers.find(layerName);

		if (itr != mRegisteredLayers.end()) {
			itr->second->SetLayerStatus(layerStatus);
		}
	}

	void LayerManagement::SetLayerStatus(int32_t layerHandle, LayerStatus layerStatus)	{
		if (layerHandle < static_cast<int32_t>(mLayers.size()))	{
			layerStatus = mLayers[layerHandle]->GetLayerStatus();
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

		for (auto& layerFactory : mLayerFactories) {
			layerFactory.second->SetSDLApplication(mSDLApplication);
		}
	}

	void LayerManagement::SetLayerConfigurationPath(std::string_view path) {
		mLayerConfigurationPath = static_cast<std::string>(path);
	}

	void LayerManagement::ResetIterator() {
		mCurrentLayerItr = mLayers.begin();
	}

	void LayerManagement::Next() {
		mCurrentLayerItr++;
	}

	bool LayerManagement::IsDone() const {
		return (mCurrentLayerItr == mLayers.end());
	}
	
	std::shared_ptr<Layer> LayerManagement::Current() {
		return *mCurrentLayerItr;
	}
	
	void LayerManagement::CreateLayer(std::string_view factoryName, ParameterSet layerMetadata) {
		std::string factoryNameStr;

		layerMetadata.GetParameterValue<std::string>("LayerFactory", factoryNameStr);

		if (mLayerFactories.contains(factoryNameStr)) {
			AddLayer(mLayerFactories[factoryNameStr]->CreateLayer(layerMetadata));
		}
	}
}