/*#include "gis_meta_data.h"

#include "slippy_map_util.h"

#include <tuple>

using namespace gis;

std::tuple<double, double> getChicagoMeters()
{
	return { -9757148.442088600, 5138517.444985110 };
}

std::tuple<double, double> getChicagoLatLon()
{
	return { 41.85, -87.65 };
}

int main() {
	

	auto [lat, lon] = getChicagoLatLon();
	auto [meterX, meterY] = getChicagoMeters();

	GeoPoint chicagoGeo{ lat, lon };

	auto inMeters = SlippyMapUtil::GeographicToMeters(chicagoGeo);

	return 0;
}*/