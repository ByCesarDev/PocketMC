#pragma once
#include "../../../world/level/tile/ObsidianTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_obsidian(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:obsidian"))
            .legacyId(49).descriptionId("obsidian")
            .destroyTime(10.0f).explosionResistance(2000)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new ObsidianTile(id, 37, false))->init(); })
            .build()
    );
}
