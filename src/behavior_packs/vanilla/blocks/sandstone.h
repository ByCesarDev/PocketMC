#pragma once
#include "../../../world/level/tile/SandStoneTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_sandstone(BlockRegistry& blocks) {
    static const int textures[] = { 0 + 16 * 12, 5 + 16 * 14, 6 + 16 * 14 };
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:sandstone"))
            .legacyId(24).descriptionId("sandStone")
            .destroyTime(0.8f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new SandStoneTile(id, textures, 3))->init(); })
            .build()
    );
}
