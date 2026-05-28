#ifndef NET_MINECRAFT_WORLD_ITEM_CRAFTING__FurnaceRecipes_H__
#define NET_MINECRAFT_WORLD_ITEM_CRAFTING__FurnaceRecipes_H__

//package net.minecraft.world.item.crafting;

#include "../ItemInstance.h"
#include <map>

class FurnaceRecipes
{
public:
    typedef std::map<int, ItemInstance> Map;

	static void teardownFurnaceRecipes();
    static FurnaceRecipes* getInstance();

    bool isFurnaceItem(int itemId) const;

	ItemInstance getResult(int itemId) const;

    const Map& getRecipes() const;
	void addFurnaceRecipe(int itemId, const ItemInstance& result);

private:
    FurnaceRecipes();

    static FurnaceRecipes* instance;

	Map recipes;
};

#endif /*NET_MINECRAFT_WORLD_ITEM_CRAFTING__FurnaceRecipes_H__*/
