#include "camera.h"

#include "spdlog/spdlog.h"

namespace basic_engine {
	void Camera::Initialize(const WindowParameter& winParameters) {
		mViewBox = { 0, 0, static_cast<float>(winParameters.Width), static_cast<float>(winParameters.Height) };
		mWidth = winParameters.Width;
		mHeight = winParameters.Height;
	}

	void Camera::Update(double deltaTimeInMsec)	{
		if (true == mIsTargetAssigned) {
			mViewBox.Left = mTarget.x - mWidth * 0.5F;
			mViewBox.Top = mTarget.y - mHeight * 0.5F;

			// TODO: Asagidaki kisimlar kamera sinirlamalari icin daha sonra guncellenebilir
			mViewBox.Left = glm::clamp(mViewBox.Left, 0.0F, (2.0F * static_cast<float>(mWidth)));
			mViewBox.Top = glm::clamp(mViewBox.Top, 0.0F, (2.0F * static_cast<float>(mHeight)));

			mCenter = { mViewBox.Left, mViewBox.Top };
		}
	}

	basic_engine::Rectangle<float> Camera::ViewBox() const	{
		return mViewBox;
	}

	Vector2f Camera::Center() const { return mCenter; }

	Vector2f Camera::Target() const	{
		return mTarget;
	}

	void Camera::ResetTarget() {
		mIsTargetAssigned = false;
	}

	void Camera::SetTarget(Vector2f val) {
		mIsTargetAssigned = true;
		mTarget = val;
	}

	void Camera::DisplayInfo() {
		spdlog::info("Camera center: <{}, {}>. Is Target Set:{}, Target Pos: <{}, {}>", mCenter.x, mCenter.y, mIsTargetAssigned, mTarget.x, mTarget.y);
	}

}