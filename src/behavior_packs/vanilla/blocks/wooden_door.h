#pragma once
#include "../../../world/level/tile/DoorTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_wooden_door(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:wooden_door"))
            .legacyId(64).descriptionId("doorWood")
            .destroyTime(3.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new DoorTile(id, Material::wood))->init(); })
            .build()
    );
}
