#include "geographic_gl_view.h"
#include "map_view.h"

#include "spdlog/spdlog.h"

namespace gis {
	// Geographic map extent icerigini de buraya koyalim
	/*bool GeographicGLView::Initialize() {
		mIsInitialized = false;

		if ((0 != mGLPainter)
			&&
			(0 != mMapView)) {
			mIsInitialized = true;
		}
		else {
			spdlog::info("[GeographicGLView] Initialization failed!");
		}

		return mIsInitialized;
	}

	void GeographicGLView::ApplyMapExtent() const {
		mGLPainter->ResetTransform();
		mGLPainter->Translate(mMapView->WinWidth() / 2.0, mMapView->WinHeight() / 2.0);
		mGLPainter->Scale(mMapView->GetScaleX(), mMapView->GetScaleY());
		mGLPainter->Rotate(mMapView->GetRotation());
		mGLPainter->Translate(-mMapView->GetCenterX(), -mMapView->GetCenterY());
	}

	void GeographicGLView::ApplyScreenExtent() const
	{
		mGLPainter->ResetTransform();
	}

	void GeographicGLView::Apply2DDrawSettings() const
	{
		uDecimal64 fLeft = mScreenExtent->GetCenterX() - static_cast<uDecimal64>(mScreenExtent->GetWidth()) / 2.0;
		uDecimal64 fRight = fLeft + static_cast<uDecimal64>(mScreenExtent->GetWidth());
		uDecimal64 fTop = static_cast<uDecimal64>(mScreenExtent->GetCenterY())
			- static_cast<uDecimal64>(mScreenExtent->GetHeight()) / 2.0;
		uDecimal64 fBottom = fTop + static_cast<uDecimal64>(mScreenExtent->GetHeight());
		
		mGLPainter->SetDepthTest(false);
		mGLPainter->SetDisplayExtent(fLeft, fRight, fBottom, fTop);
	}

	void GeographicGLView::SetMapExtent(const uIMapExtent& Extent)
	{
		mMapView = &Extent;
	}

	void GeographicGLView::SetScreenExtent(const uScreenExtent& a_val)
	{
		mScreenExtent = &a_val;
	}

	void GeographicGLView::SetGLPainter(uI2D_GLPainter* a_val)
	{
		mGLPainter = a_val;
	}*/
}