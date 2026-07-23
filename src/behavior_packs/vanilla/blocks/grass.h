#pragma once
#include "../../../world/level/tile/GrassTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_grass(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:grass"))
            .legacyId(2).descriptionId("grass")
            .destroyTime(0.6f)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new GrassTile(id))->init(); })
            .build()
    );
}
