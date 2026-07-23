#include "ItemRegistry.h"
#include "Item.h"

void ItemRegistry::registerItem(const ItemDefinition& def) {
    items.push_back(def);
    size_t index = items.size() - 1;
    byId[def.id] = index;
    if (def.legacyId != -1) {
        byLegacyId[def.legacyId] = index;
    }

    if (def.factory && def.legacyId != -1) {
        // Instantiate the Item and put it in Item::items for backwards compatibility
        Item* item = def.factory(def.legacyId);
        item->setDescriptionId(def.descriptionId);
        item->setMaxStackSize(def.maxStackSize);
        item->setMaxDamage(def.maxDamage);
        item->setCategory(def.creativeCategory);
        if (def.isHandEquipped) {
            item->handEquipped();
        }

        instantiatedItems[def.legacyId] = item;
        Item::items[def.legacyId] = item;
    }
}

const ItemDefinition* ItemRegistry::getItem(const ResourceLocation& id) const {
    auto it = byId.find(id);
    if (it != byId.end()) {
        return &items[it->second];
    }
    return nullptr;
}

const ItemDefinition* ItemRegistry::getItem(int legacyId) const {
    auto it = byLegacyId.find(legacyId);
    if (it != byLegacyId.end()) {
        return &items[it->second];
    }
    return nullptr;
}

Item* ItemRegistry::getItemInstance(const ResourceLocation& id) const {
    const ItemDefinition* def = getItem(id);
    if (def && def->legacyId != -1) {
        return getItemInstance(def->legacyId);
    }
    return nullptr;
}

Item* ItemRegistry::getItemInstance(int legacyId) const {
    auto it = instantiatedItems.find(legacyId);
    if (it != instantiatedItems.end()) {
        return it->second;
    }
    return nullptr;
}
