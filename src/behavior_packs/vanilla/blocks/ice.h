#pragma once
#include "../../../world/level/tile/IceTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_ice(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:ice"))
            .legacyId(79).descriptionId("ice")
            .destroyTime(0.5f).lightBlock(3)
            .soundType(Tile::SOUND_GLASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new IceTile(id, 16 * 4 + 3))->init(); })
            .build()
    );
}
