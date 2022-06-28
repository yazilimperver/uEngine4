#include "gis_sample_app.h"
#include "map_viewer_client_app.h"

GisSampleApp::GisSampleApp() {
	mClientGraphicalApplication = std::make_shared<MapViewerClientApp>();
}
