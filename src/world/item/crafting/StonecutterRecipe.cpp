#include "StonecutterRecipe.h"
#include "../../inventory/CraftingContainer.h"

StonecutterRecipe::StonecutterRecipe(ItemInstance output, ItemInstance input)
    : output(output), input(input) {
    myItems.add(input.id, 1);
}

bool StonecutterRecipe::matches(CraftingContainer* craftSlots) {
    ItemInstance* item = craftSlots->getItem(0);
    if (item) {
        return item->id == input.id;
    }
    return false;
}

ItemInstance StonecutterRecipe::assemble(CraftingContainer* craftSlots) {
    return output;
}

int StonecutterRecipe::getCraftingSize() {
    return 1;
}

ItemInstance StonecutterRecipe::getResultItem() const {
    return output;
}

int StonecutterRecipe::getMaxCraftCount(ItemPack& fromItems) {
    return fromItems.getCount(input.id);
}

int StonecutterRecipe::size() {
    return 1;
}
