#pragma once

#include "../../item/crafting/Recipes.h"
#include "../../../client/gui/screens/crafting/StonecutterScreen.h"
#include "../../../client/gui/screens/ScreenChooser.h"
#include "Tile.h"
#include "../../entity/Player.h"

class StonecutterTile : public Tile {
public:
    StonecutterTile(int id) : Tile(id, Material::stone) {
        tex = 16 * 15 + 12;
        secondary_tex = 16 * 15 + 11;
    }

    virtual int getTexture(int side, int data) {
        if (side == 1) {
            return tex; // Top
        } else if (side == 0) {
            return 16 * 14 + 12; // Bottom
        } else {
            return secondary_tex; // Sides
        }
    }

    virtual bool use(Level* level, int x, int y, int z, Player* player) {
        if (level->isClientSide) {
            Recipes::getInstance()->initStoneCutterRecipes();
            player->getScreenChooser()->pushStonecutterScreen(x, y, z);
        }
        return true;
    }
protected:
    int tex, secondary_tex;
};
