#pragma once
#include "../../../world/level/tile/HeavyTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_sand(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:sand"))
            .legacyId(12).descriptionId("sand")
            .destroyTime(0.5f)
            .soundType(Tile::SOUND_SAND)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new HeavyTile(id, 18))->init(); })
            .build()
    );
}
