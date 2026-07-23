#pragma once
#include "../../../world/level/tile/DoorTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_iron_door(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:iron_door"))
            .legacyId(71).descriptionId("doorIron")
            .destroyTime(5.0f)
            .soundType(Tile::SOUND_METAL)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new DoorTile(id, Material::metal))->init(); })
            .build()
    );
}
