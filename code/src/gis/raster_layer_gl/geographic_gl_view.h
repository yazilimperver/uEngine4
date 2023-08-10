/**
 * @file GeographicGLView.h
 * @date 2015/05/07 18:36
 * @brief
 * @author Mehmet Fatih ULUAT
 *
 * @details
 *
 * Copyright © 2015, uEngine V3.0 Mehmet Fatih ULUAT <fatihuluat@gmail.com>
 */

#pragma once

#include <Common/uEngineBasicTypes.h>
#include <Common/uErrorCode.h>
#include <GLCore/uI2D_GLPainter.h>

namespace gl {
	class GLBasicPainter;
}
namespace gis {
	class MapView;

	class GeographicGLView {
	public:
		//! Initialize, check whether necessary arrangments are applied
		bool Initialize();

		//! apply necessary transformations to obtain a GIS based open gl extent
		void ApplyMapExtent() const;

		//! Return back screen coordinates
		void ApplyScreenExtent() const;

		//! apply necessary opengl calls to draw 2D object in the scene
		void Apply2DDrawSettings() const;

		//! pass services
		void SetMapView(const MapView* mapView);
		void SetGLPainter(gl::GLBasicPainter* painter);

	protected:
		//! Is initialized
		uBool mIsInitialized{ false };

		//! Kullanilacak harita ekrani
		const MapView* mMapView{ nullptr };

		//! Opengl painter
		gl::GLBasicPainter* mGLPainter{ nullptr };
	};
}
