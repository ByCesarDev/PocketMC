#pragma once
#include "../../../world/level/tile/DirtTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_dirt(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:dirt"))
            .legacyId(3).descriptionId("dirt")
            .destroyTime(0.5f)
            .soundType(Tile::SOUND_GRAVEL)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new DirtTile(id, 2))->init(); })
            .build()
    );
}
