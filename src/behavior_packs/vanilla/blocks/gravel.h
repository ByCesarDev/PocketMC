#pragma once
#include "../../../world/level/tile/GravelTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_gravel(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:gravel"))
            .legacyId(13).descriptionId("gravel")
            .destroyTime(0.6f)
            .soundType(Tile::SOUND_GRAVEL)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new GravelTile(id, 19))->init(); })
            .build()
    );
}
