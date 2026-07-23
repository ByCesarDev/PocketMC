#pragma once
#include "../../../world/level/tile/NetherPortalTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_portal(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:portal"))
            .legacyId(90).descriptionId("netherPortal")
            .destroyTime(-1.0f).lightEmission(11)
            .soundType(Tile::SOUND_GLASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new NetherPortalTile(id, 250))->init(); })
            .build()
    );
}
