#pragma once
#include "../../../world/level/tile/DeepslateTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_cobbled_deepslate(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:cobbled_deepslate"))
            .legacyId(171).descriptionId("deepslateCobbled")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new DeepslateTile(id, 7 | Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}
