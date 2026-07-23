#pragma once
#include "../../../world/level/tile/TrapDoorTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_trapdoor(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:trapdoor"))
            .legacyId(96).descriptionId("trapdoor")
            .destroyTime(3.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new TrapDoorTile(id, Material::wood))->init(); })
            .build()
    );
}
