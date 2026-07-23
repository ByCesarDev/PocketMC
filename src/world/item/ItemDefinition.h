#pragma once

#include "Item.h"
#include "../../util/ResourceLocation.h"
#include <string>
#include <memory>
#include <functional>

class ItemDefinitionBuilder;

class ItemDefinition {
public:
    ResourceLocation id;
    int legacyId;
    std::string descriptionId;
    int maxStackSize = 64;
    int maxDamage = 0;
    int creativeCategory = 0;
    bool isHandEquipped = false;
    std::function<Item*(int)> factory;

    ItemDefinition(const ResourceLocation& id) : id(id), legacyId(-1) {}

    static ItemDefinitionBuilder builder(const ResourceLocation& id);
};

class ItemDefinitionBuilder {
    ItemDefinition def;
public:
    ItemDefinitionBuilder(const ResourceLocation& id) : def(id) {}

    ItemDefinitionBuilder& legacyId(int id) { def.legacyId = id; return *this; }
    ItemDefinitionBuilder& descriptionId(const std::string& descId) { def.descriptionId = descId; return *this; }
    ItemDefinitionBuilder& maxStackSize(int size) { def.maxStackSize = size; return *this; }
    ItemDefinitionBuilder& maxDamage(int damage) { def.maxDamage = damage; return *this; }
    ItemDefinitionBuilder& creativeCategory(int category) { def.creativeCategory = category; return *this; }
    ItemDefinitionBuilder& handEquipped(bool equipped = true) { def.isHandEquipped = equipped; return *this; }
    
    ItemDefinitionBuilder& factory(std::function<Item*(int)> f) { def.factory = f; return *this; }

    ItemDefinition build() const {
        return def;
    }
};

inline ItemDefinitionBuilder ItemDefinition::builder(const ResourceLocation& id) {
    return ItemDefinitionBuilder(id);
}
