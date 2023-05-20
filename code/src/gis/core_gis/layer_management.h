/**
 * @file   layer_control.h
 * @date   5/1/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_LAYER_CONTROL_H
#define INC_LAYER_CONTROL_H

#include <cstdint>
#include <vector>
#include <memory>
#include <unordered_map>

#include "map_view.h"
#include "layer_service.h"

class SdlApplication;

namespace gis {
	class Layer;
	enum class LayerStatus;

	class LayerManagement
		: public LayerService	{
	public:

		/** @brief   Katman yoneticisini ilklendirelim */
		bool Initialize();

		/** @brief   Katmanlara kayitli kontrolculeri tetikleyelim */
		virtual void Update();

		/** @brief   Ilgili katman nesnelerini gosterelim */
		virtual void Display();

		/** @brief   Cografik katman ekleyelim */
		virtual void AddLayer(std::shared_ptr<Layer> Layer) override;

		/** @brief   Katman fabrikasi kullanilarak katman ekleme fonksiyonu */
		virtual void CreateLayer(std::string_view layerName, std::string_view layerType) override;

		/** @brief   Fabrikasi kayit ediliyor */
		virtual void RegisterLayerFactory(std::unique_ptr<LayerFactory> layerFactory) override;

		/** @brief   Katman servisleri */
		virtual std::optional<std::shared_ptr<Layer>> GetLayer(const std::string& layerName);
		virtual std::optional<std::shared_ptr<Layer>> GetLayer(int32_t layerHandle);
		virtual std::optional<LayerStatus> GetLayerStatus(int32_t layerHandle);
		virtual std::optional<LayerStatus> GetLayerStatus(const std::string& layerName);
		virtual std::optional<int32_t> GetLayerHandle(const std::string& layerName);
		virtual void SetLayerStatus(const std::string& layerName, LayerStatus layerStatus);
		virtual void SetLayerStatus(int32_t layerHandle, LayerStatus layerStatus);
		
		/** @brief   Her katman icin ortak olarak kullanilacak olan veriler */
		void SetMapView(std::shared_ptr<gis::MapView> mapView);
		void SetSDLApplication(SdlApplication* sdlApplication);
	protected:
		bool mIsInitialized = false;
		SdlApplication* mSDLApplication{ nullptr };
		
		/** @brief  Katman fabrika siniflari */
		std::unordered_map<std::string, std::unique_ptr<LayerFactory>> mLayerFactories;

		/** @brief   Olusturulan/kaydedilen katmanlar */
		std::vector<std::shared_ptr<Layer>> mLayers;

		/** @brief   Etiket iceren kaydedilen katmanlar */
		std::vector<std::shared_ptr<Layer>> mLayersWithLabel;
	
		/** @brief   Isimlerine gore kaydedilen katmanlar */
		std::unordered_map<std::string, std::shared_ptr<Layer>> mRegisteredLayers;

		/** @brief   Katmanin genel cografik veriler icin kullanacagi harita gorunumu */
		std::shared_ptr<gis::MapView> mMapView{ nullptr };
	};
}

#endif	// INC_LAYER_CONTROL_H

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


