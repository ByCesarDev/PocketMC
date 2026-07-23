#pragma once
#include "../../../world/level/tile/WorkbenchTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_crafting_table(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:crafting_table"))
            .legacyId(58).descriptionId("workbench")
            .destroyTime(2.5f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new WorkbenchTile(id))->init(); })
            .build()
    );
}
