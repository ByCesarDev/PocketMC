#pragma once
#include "../../../world/level/tile/ReedTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_reeds(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:reeds"))
            .legacyId(83).descriptionId("reeds")
            .destroyTime(0.0f)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new ReedTile(id, 16 * 4 + 9))->init(); })
            .build()
    );
}
