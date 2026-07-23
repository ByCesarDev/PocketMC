#pragma once
#include "../../../world/level/tile/LadderTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_ladder(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:ladder"))
            .legacyId(65).descriptionId("ladder")
            .destroyTime(0.4f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new LadderTile(id, 3 + 5 * 16))->init(); })
            .build()
    );
}
