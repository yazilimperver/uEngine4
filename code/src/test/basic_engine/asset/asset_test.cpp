#include "gtest/gtest.h"

#include "asset/asset_info.h"

using namespace infra;

TEST(AssetInfo, AssetInfoDefaultParams) {
	AssetInfo instance;

	ASSERT_EQ(instance.mHandle, 0);
	ASSERT_EQ(instance.mStatus, AssetStatus::NotActive);
	ASSERT_STREQ(instance.mLabel.c_str(), "");
	ASSERT_STREQ(instance.mPath.c_str(), "");
}