#ifndef NET_MINECRAFT_WORLD_LEVEL_DIMENSION__NetherDimension_H__
#define NET_MINECRAFT_WORLD_LEVEL_DIMENSION__NetherDimension_H__

#include "Dimension.h"
#include "../Level.h"

class NetherDimension : public Dimension {
public:
	NetherDimension() {
		id = -1;
		foggy = true;
		ultraWarm = true;
		hasCeiling = true;
	}

	bool isNaturalDimension() override {
		return false;
	}

	float getTimeOfDay(long time, float a) override {
		return 0.0f;
	}

	Vec3 getFogColor(float td, float a) override {
		return Vec3(0.5f, 0.15f, 0.1f);
	}

	void updateLightRamp(float gamma) override {
		for (int i = 0; i <= 15; i++) {
			float f = (float)i / 15.0f;
			brightnessRamp[i] = f * 0.8f + 0.2f;
		}
	}
};

#endif /*NET_MINECRAFT_WORLD_LEVEL_DIMENSION__NetherDimension_H__*/
