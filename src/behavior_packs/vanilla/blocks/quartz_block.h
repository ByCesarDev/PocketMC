#pragma once
#include "../../../world/level/tile/QuartzBlockTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_quartz_block(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:quartz_block"))
            .legacyId(155).descriptionId("quartzBlock")
            .destroyTime(0.8f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new QuartzBlockTile(id))->init(); })
            .build()
    );
}
