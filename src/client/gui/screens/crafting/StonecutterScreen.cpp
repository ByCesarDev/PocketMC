#include "StonecutterScreen.h"
#include "CraftingFilters.h"
#include "../../../../world/item/crafting/Recipes.h"
#include "../../components/InventoryPane.h"
#include "../../components/ItemPane.h"
#include "../../components/ScrolledSelectionList.h"

StonecutterScreen::StonecutterScreen()
:   super(1)
{
}

bool StonecutterScreen::filterRecipe(const Recipe& recipe)
{
    return recipe.getRecipeType() == RecipeType::StoneCutter || CraftingFilters::isStonecutterItem(recipe.getResultItem());
}
