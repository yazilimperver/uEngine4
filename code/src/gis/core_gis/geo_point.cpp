#include "geo_point.h"

namespace gis {
	GeoPoint::GeoPoint()
		: mLatitude(0.0)
		, mLongitude(0.0) {

	}
	GeoPoint::GeoPoint(double latitude, double longitude)
		: mLatitude{ latitude }, mLongitude{ longitude }{
	}

	double GeoPoint::Latitude() const {
		return mLatitude;
	}	
	double GeoPoint::Longitude() const {
		return mLongitude;
	}
	void GeoPoint::SetLatitude(double lat) {
		mLatitude = lat;
	}
	void GeoPoint::SetLongitude(double longitude) {
		mLongitude = longitude;
	}
}