#pragma once
#include "../../../world/level/tile/BookshelfTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_bookshelf(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:bookshelf"))
            .legacyId(47).descriptionId("bookshelf")
            .destroyTime(1.5f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new BookshelfTile(id, 35))->init(); })
            .build()
    );
}
