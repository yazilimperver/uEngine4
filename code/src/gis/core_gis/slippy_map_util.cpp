#include "slippy_map_util.h"

namespace gis {
	GeoPoint SlippyMapUtil::PixelToGeographic(const PointInPixels& inputInPixels, uint32_t zoomLevel) {
		PointInMeters inputInMeters;
		inputInMeters.x = inputInPixels.x * GisMetaData::Resolution(zoomLevel) - cOriginShift;
		inputInMeters.y = inputInPixels.y * GisMetaData::Resolution(zoomLevel) - cOriginShift;
		return MeterToGeographic(GetSignedMeters(inputInMeters, inputInPixels, zoomLevel));
	}

	// Converts pixel coordinates in given zoom level of pyramid to EPSG: 3857

	PointInMeters SlippyMapUtil::PixelToMeter(const PointInPixels& inputInPixels, uint32_t zoomLevel) {
		return PointInMeters{ inputInPixels.x * GisMetaData::Resolution(zoomLevel) - cOriginShift,
			inputInPixels.y * GisMetaData::Resolution(zoomLevel) - cOriginShift };
	}

	GeoPoint SlippyMapUtil::MeterToGeographic(const PointInMeters& input) {
		auto longitude = (input.x / cOriginShift) * 180.0;
		auto latitude = (input.y / cOriginShift) * 180.0;

		latitude = 180.0 / PI * (2 * atan(exp(latitude * PI / 180.0)) - PI / 2.0);

		return { latitude, longitude };
	}

	PointInPixels SlippyMapUtil::MeterToPixels(const PointInMeters& inputInMeters, uint32_t zoomLevel) {
		return PointInPixels{ (inputInMeters.x + cOriginShift) / GisMetaData::Resolution(zoomLevel),
			(inputInMeters.y + cOriginShift) / GisMetaData::Resolution(zoomLevel) };
	}

	PointInMeters SlippyMapUtil::GeographicToMeters(const GeoPoint& input) {
		auto meterX = input.Longitude() * cOriginShift / 180.0;
		auto meterY = std::log(std::tan((90.0 + input.Latitude()) * PI / 360.0)) / (PI / 180.0);
		return { meterX, meterY * cOriginShift / 180.0 };
	}

	PointInPixels SlippyMapUtil::GeographicToPixel(const GeoPoint& inputInGeog, uint32_t zoomLevel) {
		auto inputInMeter = GeographicToMeters(inputInGeog);
		PointInPixels result{ (inputInMeter.x + cOriginShift) / GisMetaData::Resolution(zoomLevel),
			(inputInMeter.y - cOriginShift) / GisMetaData::Resolution(zoomLevel) };

		result.x = static_cast<int32_t>(std::abs(std::round(result.x)));
		result.y = static_cast<int32_t>(std::abs(std::round(result.y)));

		return result;
	}

	GeoPoint SlippyMapUtil::GetGeographic(double latitude, double longitude) {
		return GeoPoint{ latitude, longitude };
	}

	PointInMeters SlippyMapUtil::GetSignedMeters(const PointInMeters& inputInMeters, const PointInPixels& inputInPixel, uint32_t zoomLevel) {
		auto halfSize = cDefaultTileSize * (1 << zoomLevel) * 0.5;

		PointInMeters result;
		result.x = std::abs(inputInMeters.x);
		result.y = std::abs(inputInMeters.y);

		if (inputInPixel.x < halfSize) {
			result.x *= -1;
		}
		if (inputInPixel.y > halfSize) {
			result.y *= -1;
		}
		return result;
	}

}