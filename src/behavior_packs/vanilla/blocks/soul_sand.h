#pragma once
#include "../../../world/level/tile/SoulSandTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_soul_sand(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:soul_sand"))
            .legacyId(119).descriptionId("soulSand")
            .destroyTime(0.5f)
            .soundType(Tile::SOUND_SAND)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new SoulSandTile(id, 9 + 16 | Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}
