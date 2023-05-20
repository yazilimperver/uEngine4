/**
 * @file   layer.h
 * @date   4/30/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_LAYER_H
#define INC_LAYER_H

#include <utility>
#include <cstdint>
#include <string>
#include <string_view>

#include "layer_type.h"
#include "layer_status.h"

namespace gis {
	class LayerRenderer;
	class LayerController;

	class Layer	{
	public:
		bool IsLayerVisible() const {
			return (GetLayerStatus() == LayerStatus::Visible);
		}
		virtual bool Initialize() = 0;
		virtual LayerStatus GetLayerStatus() const = 0;
		virtual void SetLayerStatus(LayerStatus status) = 0;
		virtual std::string GetLayerName() const = 0;
		virtual void SetLayerName(std::string_view layerName) = 0;
 		virtual std::shared_ptr<LayerRenderer> Get2DRenderer() = 0;
		virtual std::shared_ptr<LayerController> Get2DController() = 0;
		virtual LayerType GetLayerType() = 0;
		virtual bool HasLayerLabelDisplay() const = 0;
	};
}

#endif	// INC_LAYER_H

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


