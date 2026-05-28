#include "StonecutterScreen.h"
#include "../../../item/crafting/Recipes.h"
#include "../../components/InventoryPane.h"
#include "../../components/ItemPane.h"
#include "../../components/RolledSelectionList.h"

StonecutterScreen::StonecutterScreen()
:   super(Recipes::getInstance()->stoneCutterRecipes)
{
}

void StonecutterScreen::onShow()
{
    super::onShow();
}

void StonecutterScreen::onHide()
{
    super::onHide();
}
