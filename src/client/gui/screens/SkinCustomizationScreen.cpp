#include "SkinCustomizationScreen.h"
#include "../../Minecraft.h"
#include "../../Options.h"
#include "locale/I18n.h"

SkinCustomizationScreen::SkinCustomizationScreen() : group(nullptr) {}
SkinCustomizationScreen::~SkinCustomizationScreen() { delete group; }

void SkinCustomizationScreen::init() {
    btnDone = new Button(0, width / 2 - 100, height - 30, 200, 20, I18n::get("gui.done"));
    buttons.push_back(btnDone);
    group = new OptionsGroup("options.skinCustomisation");
    group->x = width / 2 - 150;
    group->y = 40;
    group->width = 300;
    group->height = height - 80;
    group->addOptionItem(OPTIONS_SKIN_CAPE, minecraft);
    group->addOptionItem(OPTIONS_SKIN_JACKET, minecraft);
    group->addOptionItem(OPTIONS_SKIN_LEFT_SLEEVE, minecraft);
    group->addOptionItem(OPTIONS_SKIN_RIGHT_SLEEVE, minecraft);
    group->addOptionItem(OPTIONS_SKIN_LEFT_PANTS, minecraft);
    group->addOptionItem(OPTIONS_SKIN_RIGHT_PANTS, minecraft);
    group->addOptionItem(OPTIONS_SKIN_HAT, minecraft);
    group->addOptionItem(OPTIONS_SKIN_MAIN_HAND, minecraft);
    group->setupPositions();
}

void SkinCustomizationScreen::buttonClicked(Button* button) {
    if (button->id == 0) {
        minecraft->popScreen();
    }
}

void SkinCustomizationScreen::render(int xm, int ym, float a) {
    renderBackground();
    drawCenteredString(font, I18n::get("options.skinCustomisation"), width / 2, 15, 0xffffff);
    if (group) group->render(minecraft, xm, ym);
    Screen::render(xm, ym, a);
}

void SkinCustomizationScreen::mouseClicked(int x, int y, int buttonNum) {
    Screen::mouseClicked(x, y, buttonNum);
    if (group) group->mouseClicked(minecraft, x, y, buttonNum);
}

void SkinCustomizationScreen::mouseReleased(int x, int y, int buttonNum) {
    Screen::mouseReleased(x, y, buttonNum);
    if (group) group->mouseReleased(minecraft, x, y, buttonNum);
}

void SkinCustomizationScreen::mouseWheel(int dx, int dy, int xm, int ym) {
    Screen::mouseWheel(dx, dy, xm, ym);
    if (group) group->mouseWheel(dx, dy, xm, ym);
}

void SkinCustomizationScreen::renderBackground() {
    Screen::renderBackground();
}

void SkinCustomizationScreen::keyPressed(int eventKey) {
    if (eventKey == Keyboard::KEY_ESCAPE) {
        minecraft->popScreen();
    }
}

void SkinCustomizationScreen::tick() {
    if (group) group->tick(minecraft);
    Screen::tick();
}
