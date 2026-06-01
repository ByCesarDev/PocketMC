#ifndef NET_MINECRAFT_WORLD_ENTITY_PLAYER__JInventory_H__
#define NET_MINECRAFT_WORLD_ENTITY_PLAYER__JInventory_H__

#include "../../inventory/FillingContainer.h"
#include "../../inventory/BaseContainerMenu.h"
#include <vector>

class Tile;
class Entity;
class Player;
class ListTag;
class CompoundTag;

class Inventory: public FillingContainer, public BaseContainerMenu
{
	typedef FillingContainer super;
public:
	static const int INVENTORY_SIZE_DEMO = 27;
	static const int MAX_SELECTION_SIZE = 9; // Including "More..." right now
	static const int POP_TIME_DURATION = 5;

    Inventory(Player* player, bool creativeMode);
	~Inventory();

	void clearInventoryWithDefault();

	void			selectSlot(int slot);
    ItemInstance*	getSelected();
    
	static int		getSelectionSize();

	bool			moveToSelectionSlot(int selectionSlot, int inventorySlot, bool propagate);
	bool			moveToSelectedSlot(int inventorySlot, bool propagate);
	bool			moveToEmptySelectionSlot(int inventorySlot);

	bool			removeItem(const ItemInstance* samePtr);

    int removeResource(ItemInstance& item, bool isAnyAuxValue = false);

	void			doDrop(ItemInstance* item, bool randomly);
	bool			stillValid(Player* player);
	bool			add(ItemInstance* item);

    BaseContainerMenu::ItemList getItems() override;
    void setSlot(int, ItemInstance*) override;
    bool tileEntityDestroyedIsInvalid(int) override;

	int				getAttackDamage(Entity* entity);
	float			getDestroySpeed(Tile* tile);
	bool			canDestroy(Tile* tile);
private:
	void			setupDefault();
public:

    int selected;
    Player* player;
};

#endif /*NET_MINECRAFT_WORLD_ENTITY_PLAYER__JInventory_H__*/
