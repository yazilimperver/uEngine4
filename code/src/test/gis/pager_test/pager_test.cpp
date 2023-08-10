#include "gtest/gtest.h"

#include <algorithm>

#include "pager/pager.h"
#include "pager/gtile_file_calculator.h"

#include "core_gis/gis_meta_data.h"

TEST(GoogleTileCalculator, DoesCalculatorCalculateTileCorrectly) {
	gis::GTileFileCalculator tileIdCalculator(".png", R"(D:\git_repos\Yazilimperver\uEngine4\assets\map_data\google_raster\)");

	auto tileID = tileIdCalculator.Path(10, 585, 380);
	ASSERT_STRCASEEQ(tileID.c_str(), R"(D:\git_repos\Yazilimperver\uEngine4\assets\map_data\google_raster\lvl10\585\380.png)");
}

TEST(Pager, PagerDefaultShouldBeSetCorrectly) {
	gis::Pager cutInstance;
	
	ASSERT_EQ(cutInstance.ProvidedPosition().x, 0);
	ASSERT_EQ(cutInstance.ProvidedPosition().y, 0);
	ASSERT_EQ(cutInstance.ProvidedZoom(), 0);
}

TEST(Pager, ReferenceUpdatesShouldBeReflectedCorrectly) {
	gis::Pager cutInstance;

	cutInstance.UpdateReference(PointInPixels{ 2999, 4567 }, 10);

	ASSERT_EQ(cutInstance.ProvidedPosition().x, 2999);
	ASSERT_EQ(cutInstance.ProvidedPosition().y, 4567);
	ASSERT_EQ(cutInstance.ProvidedZoom(), 10);
}

TEST(Pager, ReferenceUpdatesShouldBeReflectedToTileInfoCorrectly_TMS) {
	gis::Pager cutInstance;

	// Referans icin https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#9/33.14/39.86
	uint32_t ankaraZoomLevel1{ 9 };
	PointInPixels ankaraPixelPos1{ 77450, 49800 };

	cutInstance.UpdateReference(ankaraPixelPos1, ankaraZoomLevel1);

	ASSERT_EQ(cutInstance.ProvidedPosition().x, ankaraPixelPos1.x);
	ASSERT_EQ(cutInstance.ProvidedPosition().y, ankaraPixelPos1.y);
	ASSERT_EQ(cutInstance.ProvidedZoom(), ankaraZoomLevel1);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileX, 302);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileY, 317);
	ASSERT_EQ(cutInstance.ProvidedTileId().ZoomLevel, ankaraZoomLevel1);

	// Referans icin https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#4/42.57/36.69
	uint32_t ankaraZoomLevel2{ 4 };
	PointInPixels ankaraPixelPos2{ 2400, 1650};

	cutInstance.UpdateReference(ankaraPixelPos2, ankaraZoomLevel2);

	ASSERT_EQ(cutInstance.ProvidedPosition().x, ankaraPixelPos2.x);
	ASSERT_EQ(cutInstance.ProvidedPosition().y, ankaraPixelPos2.y);
	ASSERT_EQ(cutInstance.ProvidedZoom(), ankaraZoomLevel2);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileX, 9);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileY, 9);
	ASSERT_EQ(cutInstance.ProvidedTileId().ZoomLevel, ankaraZoomLevel2);
}

TEST(Pager, ReferenceUpdatesShouldBeReflectedToTileInfoCorrectly_Google) {
	gis::Pager cutInstance;
	cutInstance.SetOrigin(gis::TileOrigin::Google);

	ASSERT_EQ(cutInstance.Origin(), gis::TileOrigin::Google);

	// Referans icin https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#9/33.14/39.86
	uint32_t ankaraZoomLevel1{ 9 };
	PointInPixels ankaraPixelPos1{ 77450, 49800 };

	cutInstance.UpdateReference(ankaraPixelPos1, ankaraZoomLevel1);

	ASSERT_EQ(cutInstance.ProvidedPosition().x, ankaraPixelPos1.x);
	ASSERT_EQ(cutInstance.ProvidedPosition().y, ankaraPixelPos1.y);
	ASSERT_EQ(cutInstance.ProvidedZoom(), ankaraZoomLevel1);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileX, 302);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileY, 194);
	ASSERT_EQ(cutInstance.ProvidedTileId().ZoomLevel, ankaraZoomLevel1);

	// Referans icin https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#4/42.57/36.69
	uint32_t ankaraZoomLevel2{ 4 };
	PointInPixels ankaraPixelPos2{ 2400, 1650 };

	cutInstance.UpdateReference(ankaraPixelPos2, ankaraZoomLevel2);

	ASSERT_EQ(cutInstance.ProvidedPosition().x, ankaraPixelPos2.x);
	ASSERT_EQ(cutInstance.ProvidedPosition().y, ankaraPixelPos2.y);
	ASSERT_EQ(cutInstance.ProvidedZoom(), ankaraZoomLevel2);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileX, 9);
	ASSERT_EQ(cutInstance.ProvidedTileId().TileY, 6);
	ASSERT_EQ(cutInstance.ProvidedTileId().ZoomLevel, ankaraZoomLevel2);
}

TEST(Pager, TilesShouldBeCalculatedWrtCenterCorrectly) {
	gis::Pager cutInstance;

	// Referans icin https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#9/33.14/39.86
	uint32_t ankaraZoomLevel1{ 9 };
	PointInPixels ankaraPixelPos1{ 77450, 49800 };

	// bu konuma karsilik gelen pafta 302, 317

	cutInstance.UpdateReference(ankaraPixelPos1, ankaraZoomLevel1);
	cutInstance.Update();

	auto calculatedTiles = cutInstance.ActiveTiles();
	std::sort(calculatedTiles.begin(), calculatedTiles.end());

	{
		gis::TileId tileToCheck(301, 316, 9);
		ASSERT_EQ(calculatedTiles[0].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[0].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(301, 317, 9);
		ASSERT_EQ(calculatedTiles[1].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[1].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(301, 318, 9);
		ASSERT_EQ(calculatedTiles[2].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[2].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(302, 316, 9);
		ASSERT_EQ(calculatedTiles[3].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[3].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(302, 317, 9);
		ASSERT_EQ(calculatedTiles[4].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[4].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(302, 318, 9);
		ASSERT_EQ(calculatedTiles[5].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[5].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(303, 316, 9);
		ASSERT_EQ(calculatedTiles[6].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[6].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(303, 317, 9);
		ASSERT_EQ(calculatedTiles[7].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[7].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(303, 318, 9);
		ASSERT_EQ(calculatedTiles[8].TileX, tileToCheck.TileX);
		ASSERT_EQ(calculatedTiles[8].TileY, tileToCheck.TileY);
	}
}

TEST(Pager, TilesToBeDisposedShouldBeCalculatedCorrectly) {
	gis::Pager cutInstance;

	// Referans icin https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#9/33.14/39.86
	uint32_t ankaraZoomLevel1{ 9 };
	PointInPixels ankaraPixelPos1{ 77450, 49800 };

	// bu konuma karsilik gelen pafta 302, 317
	cutInstance.UpdateReference(ankaraPixelPos1, ankaraZoomLevel1);
	cutInstance.Update();

	// Simdi 256 pixel saga gidelim
	ankaraPixelPos1.x += gis::cDefaultTileSize;

	cutInstance.UpdateReference(ankaraPixelPos1, ankaraZoomLevel1);
	cutInstance.Update();

	auto tilesToDispose = cutInstance.TilesToDispose();
	std::sort(tilesToDispose.begin(), tilesToDispose.end());

	ASSERT_EQ(tilesToDispose.size(), 3);

	{
		gis::TileId tileToCheck(301, 316, 9);
		ASSERT_EQ(tilesToDispose[0].TileX, tileToCheck.TileX);
		ASSERT_EQ(tilesToDispose[0].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(301, 317, 9);
		ASSERT_EQ(tilesToDispose[1].TileX, tileToCheck.TileX);
		ASSERT_EQ(tilesToDispose[1].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(301, 318, 9);
		ASSERT_EQ(tilesToDispose[2].TileX, tileToCheck.TileX);
		ASSERT_EQ(tilesToDispose[2].TileY, tileToCheck.TileY);
	}
}

TEST(Pager, TilesToBeLoadedShouldBeCalculatedCorrectly) {
	gis::Pager cutInstance;

	// Referans icin https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#9/33.14/39.86
	uint32_t ankaraZoomLevel1{ 9 };
	PointInPixels ankaraPixelPos1{ 77450, 49800 };

	// bu konuma karsilik gelen pafta 302, 317
	cutInstance.UpdateReference(ankaraPixelPos1, ankaraZoomLevel1);
	cutInstance.Update();

	// Simdi 256 pixel saga gidelim
	ankaraPixelPos1.x += gis::cDefaultTileSize;

	cutInstance.UpdateReference(ankaraPixelPos1, ankaraZoomLevel1);
	cutInstance.Update();

	auto tilesToDispose = cutInstance.TilesToLoad();
	std::sort(tilesToDispose.begin(), tilesToDispose.end());

	ASSERT_EQ(tilesToDispose.size(), 3);

	{
		gis::TileId tileToCheck(304, 316, 9);
		ASSERT_EQ(tilesToDispose[0].TileX, tileToCheck.TileX);
		ASSERT_EQ(tilesToDispose[0].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(304, 317, 9);
		ASSERT_EQ(tilesToDispose[1].TileX, tileToCheck.TileX);
		ASSERT_EQ(tilesToDispose[1].TileY, tileToCheck.TileY);
	}

	{
		gis::TileId tileToCheck(304, 318, 9);
		ASSERT_EQ(tilesToDispose[2].TileX, tileToCheck.TileX);
		ASSERT_EQ(tilesToDispose[2].TileY, tileToCheck.TileY);
	}
}