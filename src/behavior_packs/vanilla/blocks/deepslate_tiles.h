#pragma once
#include "../../../world/level/tile/DeepslateTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_deepslate_tiles(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:deepslate_tiles"))
            .legacyId(182).descriptionId("deepslateTiles")
            .destroyTime(1.5f).explosionResistance(6.0f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new DeepslateTilesTile(id))->init(); })
            .build()
    );
}
