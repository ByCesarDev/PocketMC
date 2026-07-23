#pragma once
#include "../../../world/level/tile/TreeTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_log_birch(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:log_birch"))
            .legacyId(19).descriptionId("logBirch")
            .destroyTime(2.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new TreeTile(id))->init(); })
            .build()
    );
}
