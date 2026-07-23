#pragma once
#include "../../../world/level/tile/NetherQuartzOreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_quartz_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:quartz_ore"))
            .legacyId(117).descriptionId("netherQuartzOre")
            .destroyTime(3.0f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new NetherQuartzOreTile(id, 7 + 16 | Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}
