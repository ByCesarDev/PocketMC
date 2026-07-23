#pragma once
#include "../../../world/level/tile/ChestTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_chest(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:chest"))
            .legacyId(54).descriptionId("chest")
            .destroyTime(2.5f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new ChestTile(id))->init(); })
            .build()
    );
}
