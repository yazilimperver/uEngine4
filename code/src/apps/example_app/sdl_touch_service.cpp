#include "sdl_touch_service.h"
#include "application_base/touch_data.h"

#include "SDL.h"

int32_t SdlTouchService::GetTouchFingerCount(int64_t touchId) {
    return SDL_GetNumTouchFingers(touchId);
}

std::optional<FingerData> SdlTouchService::GetTouchFingerData(int64_t touchId, int32_t index) {
    SDL_Finger* rawFingerData = SDL_GetTouchFinger(touchId, index);

    if (nullptr != rawFingerData) {
        FingerData fingerData;

        fingerData.Pressure = rawFingerData->pressure;
        fingerData.X = rawFingerData->x;
        fingerData.Y = rawFingerData->y;

        return fingerData;
    }
    else {
        return std::nullopt;
    }
}

std::optional<int64_t> SdlTouchService::GetTouchDeviceId(int32_t index){
    int64_t touchId = SDL_GetTouchDevice(index);

    if (0 != touchId) {
        return touchId;
    }
    else {
        return std::nullopt;
    }
}

int32_t SdlTouchService::GetTouchDeviceCount() {
    return SDL_GetNumTouchDevices();
}