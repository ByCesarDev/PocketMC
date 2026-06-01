#ifndef NET_MINECRAFT_WORLD_ENTITY_MONSTER__PigZombieBrute_H__
#define NET_MINECRAFT_WORLD_ENTITY_MONSTER__PigZombieBrute_H__

#include "PigZombie.h"

class PigZombieBrute : public PigZombie {
	typedef PigZombie super;
public:
	PigZombieBrute(Level* level);
	std::string getTexture() override;
	int getMaxHealth() override;
	int getEntityTypeId() const override;
};

#endif /* NET_MINECRAFT_WORLD_ENTITY_MONSTER__PigZombieBrute_H__ */
