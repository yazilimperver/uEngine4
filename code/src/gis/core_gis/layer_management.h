/**
 * @file   layer_control.h
 * @date   5/1/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef LAYER_MANAGEMENT
#define LAYER_MANAGEMENT

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include "data_structures/unbounded_shared_queue.h"

#include "map_view.h"

#include "layer_service.h"
#include "layer_iterator.h"

#include "sdl_application/sdl_parameters.h"

class SdlApplication;

namespace gis {
	class Layer;
	enum class LayerStatus;

	class LayerManagement
        : public LayerService
        , public LayerIterator 	{
    private:
        enum class LayerOp{
            MoveUp,
            MoveDown,
            Remove,
            Add
        };
	public:
        /** @brief   Katman yoneticisini ilklendirelim */
        bool Initialize();

        /** @brief   Katmanlara kayitli kontrolculeri tetikleyelim */
        virtual void Update();

        /** @brief   Ilgili katman nesnelerini gosterelim */
        virtual void Display();

        /** @brief   Cografik katman ekleyelim */
        virtual void AddLayer(SharedLayer layer, uint32_t priority = 0) override;

        /** @brief   Fabrikasi kayit ediliyor */
        virtual void RegisterLayerFactory(std::unique_ptr<LayerFactory> layerFactory) override;
        
        virtual void SetPreUIDisplayHook(std::function<void(bool)> hookFunc) override;

        virtual void SetPostUIDisplayHook(std::function<void(bool)> hookFunc) override;

        /** @brief   Katman servisleri */      
        virtual void MoveUp(int layerIndexToMove) override;
        virtual void MoveDown(int layerIndexToMove) override;
        virtual std::optional<SharedLayer> GetLayer(std::string_view layerName) override;
        virtual std::optional<LayerStatus> Status(std::string_view layerName) override;
        virtual void SetStatus(std::string_view layerName, LayerStatus layerStatus) override;
        
        /** @brief   Her katman icin ortak olarak kullanilacak olan veriler */
        void SetMapView(std::shared_ptr<gis::MapView> mapView);
        void SetSDLApplication(SdlApplication* sdlApplication);
        void SetLayerConfigurationPath(std::string_view path);

        /** @brief  Katmanlara iterator oruntusu ile erismek uzere sunulacak olan API'lerdir */
        virtual void ResetIterator() override;
        virtual void Next() override;
        virtual bool IsDone() const override;
        virtual SharedLayer Current() override;
        virtual unsigned int Size() const override;

        UnboundedSharedQueue<std::pair<LayerOp, unsigned int>> mLayerOps;
	protected:

        /** @brief   UI katman gosterimleri oncesi ve sonrasi icin kullanilacak fonksiyonlar */
        std::function<void(bool)> mPreUIHook;
        std::function<void(bool)> mPostUIHook;

        /** @brief   Ilgili katmani ismine gore doner */
        std::vector<LayerService::SharedLayer>::iterator FindLayerByName(std::string_view layerName);

        /** @brief   Full pathname of the layer configuration file */
        std::string mLayerConfigurationPath;

        bool mIsInitialized = false;
        SdlApplication* mSDLApplication{ nullptr };
        SdlParameters mSDLParams;
        
        /** @brief  Katman fabrika siniflari */
        std::unordered_map<std::string, std::unique_ptr<LayerFactory>> mLayerFactories;

        /** @brief   Olusturulan/kaydedilen katmanlar */
        std::vector<SharedLayer> mLayers;

        /** @brief   Iterator ile kullanilan mevcut katman */
        int mCurrentLayerIndex{ 0 };
        LayerIteratorType mCurrentLayerItr;

        /** @brief   Katmanin genel cografik veriler icin kullanacagi harita gorunumu */
        std::shared_ptr<gis::MapView> mMapView{ nullptr };

        // Inherited via LayerService
        virtual void CreateLayer(std::string_view factoryName, ParameterSet layerType) override;
	};
}

#endif /* LAYER_MANAGEMENT */

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */


