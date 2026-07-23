#pragma once
#include "../../../world/level/tile/ObsidianTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_glowing_obsidian(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:glowing_obsidian"))
            .legacyId(246).descriptionId("glowingobsidian")
            .destroyTime(10.0f).explosionResistance(2000)
            .lightEmission(14)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new ObsidianTile(id, 10 + 16 * 13, true))->init(); })
            .build()
    );
}
