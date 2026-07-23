#pragma once
#include "../../../world/level/tile/NetherReactor.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_nether_reactor(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:nether_reactor"))
            .legacyId(247).descriptionId("netherreactor")
            .destroyTime(3.0f)
            .soundType(Tile::SOUND_METAL)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new NetherReactor(id, 10 + 14 * 16, Material::metal))->init(); })
            .build()
    );
}
