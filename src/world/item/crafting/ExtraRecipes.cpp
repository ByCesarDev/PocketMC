#include "ExtraRecipes.h"
#include "Recipes.h"
#include "../../item/Item.h"
#include "../../level/tile/Tile.h"

void ExtraRecipes::addRecipes(Recipes* r)
{
    // Birch and Spruce logs -> 4 respective planks (terrain2 atlas)
    r->addShapedRecipe(ItemInstance(Tile::birchPlanks, 4), //
        "#", //
        definition('#', Tile::birchTrunk));

    r->addShapedRecipe(ItemInstance(Tile::sprucePlanks, 4), //
        "#", //
        definition('#', Tile::spruceTrunk));

    // Recetas de Palos (Sticks)
    r->addShapedRecipe(ItemInstance(Item::stick, 4), "#", "#", definition('#', Tile::birchPlanks));
    r->addShapedRecipe(ItemInstance(Item::stick, 4), "#", "#", definition('#', Tile::sprucePlanks));

    // Recetas de Mesa de Trabajo (Workbench)
    r->addShapedRecipe(ItemInstance(Tile::workBench, 1), 
        "##", 
        "##", 
        definition('#', Tile::birchPlanks));
    r->addShapedRecipe(ItemInstance(Tile::workBench, 1), 
        "##", 
        "##", 
        definition('#', Tile::sprucePlanks));

    // Slabs (3 planks -> 6 slabs)
    r->addShapedRecipe(ItemInstance(Tile::spruceSlabHalf, 6), "###", definition('#', Tile::sprucePlanks));
    r->addShapedRecipe(ItemInstance(Tile::birchSlabHalf, 6), "###", definition('#', Tile::birchPlanks));

    // Stairs (6 planks -> 4 stairs)
    r->addShapedRecipe(ItemInstance(Tile::stairs_spruce, 4), "#  ", "## ", "###", definition('#', Tile::sprucePlanks));
    r->addShapedRecipe(ItemInstance(Tile::stairs_birch, 4), "#  ", "## ", "###", definition('#', Tile::birchPlanks));

    // Fences (4 planks + 2 sticks -> 3 fences)
    r->addShapedRecipe(ItemInstance(Tile::fenceSpruce, 3), "P#P", "P#P", definition('P', Tile::sprucePlanks, '#', Item::stick));
    r->addShapedRecipe(ItemInstance(Tile::fenceBirch, 3), "P#P", "P#P", definition('P', Tile::birchPlanks, '#', Item::stick));

    // Fence Gates (2 planks + 4 sticks -> 1 gate)
    r->addShapedRecipe(ItemInstance(Tile::fenceGateSpruce, 1), "#P#", "#P#", definition('P', Tile::sprucePlanks, '#', Item::stick));
    r->addShapedRecipe(ItemInstance(Tile::fenceGateBirch, 1), "#P#", "#P#", definition('P', Tile::birchPlanks, '#', Item::stick));
}
