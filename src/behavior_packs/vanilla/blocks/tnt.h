#pragma once
#include "../../../world/level/tile/TntTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_tnt(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:tnt"))
            .legacyId(46).descriptionId("tnt")
            .destroyTime(0.0f)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Tools)
            .factory([](int id) { return (new TntTile(id, 8))->init(); })
            .build()
    );
}
