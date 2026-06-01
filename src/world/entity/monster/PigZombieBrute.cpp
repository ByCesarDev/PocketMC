#include "PigZombieBrute.h"
#include "../../item/Item.h"
#include "../../item/ItemInstance.h"
#include "../EntityTypes.h"

PigZombieBrute::PigZombieBrute(Level* level)
	: super(level)
{
	textureName = "mob/brutepigzombie.png";
	runSpeed = 1.05f; // 1.5x standard PigZombie speed (0.7f * 1.5)
	attackDamage = 6;
	weapon = ItemInstance(Item::hatchet_gold);
}

std::string PigZombieBrute::getTexture() {
	return "mob/brutepigzombie.png";
}

int PigZombieBrute::getMaxHealth() {
	return 36; // 3x standard health (12 * 3)
}

int PigZombieBrute::getEntityTypeId() const {
	return 37; // MobTypes::PigZombieBrute
}
