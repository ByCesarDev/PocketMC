#pragma once
#include "../../../world/level/tile/WebTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_web(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:web"))
            .legacyId(30).descriptionId("web")
            .destroyTime(4.0f).lightBlock(1)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new WebTile(id, 11))->init(); })
            .build()
    );
}
