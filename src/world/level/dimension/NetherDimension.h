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
		return 0.5f;
	}

	Vec3 getFogColor(float td, float a) override {
		return Vec3(0.2f, 0.03f, 0.03f);
	}
};

#endif /*NET_MINECRAFT_WORLD_LEVEL_DIMENSION__NetherDimension_H__*/
