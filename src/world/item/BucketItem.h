#ifndef NET_MINECRAFT_WORLD_ITEM__BucketItem_H__
#define NET_MINECRAFT_WORLD_ITEM__BucketItem_H__

#include "Item.h"

class Player;
class Level;
class ItemInstance;

class BucketItem: public Item {
    typedef Item super;
    int contains; // tile id for contained liquid, -1 for milk, 0 for empty
public:
    BucketItem(int id, int contains)
    : super(id), contains(contains)
    {
        if (contains != 0) setMaxStackSize(1);
    }

    bool useOn(ItemInstance* instance, Player* player, Level* level, int x, int y, int z, int face, float clickX, float clickY, float clickZ);
    bool useOn(ItemInstance* instance, Level* level, int x, int y, int z, int face) {
        return false;
    }
    ItemInstance* use(ItemInstance* instance, Level* level, Player* player);
};

#endif
