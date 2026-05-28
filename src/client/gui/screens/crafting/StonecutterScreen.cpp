#include "StonecutterScreen.h"
#include "../../../../item/crafting/Recipes.h"
#include "../../components/InventoryPane.h"
#include "../../components/ItemPane.h"
#include "../../components/RolledSelectionList.h"

StonecutterScreen::StonecutterScreen()
:   super(Recipes::getInstance()->stoneCutterRecipes)
{
}

bool StonecutterScreen::filterRecipe(const Recipe& recipe)
{
    return true;
}
