#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS_CRAFTING__StonecutterScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS_CRAFTING__StonecutterScreen_H__

#include "PaneCraftingScreen.h"

class StonecutterScreen: public PaneCraftingScreen
{
	typedef PaneCraftingScreen super;
public:
    StonecutterScreen();

    bool filterRecipe(const Recipe& recipe) override;
};

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS_CRAFTING__StonecutterScreen_H__*/
