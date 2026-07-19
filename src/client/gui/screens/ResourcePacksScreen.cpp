#include "ResourcePacksScreen.h"
#include "../../Minecraft.h"
#include "../../Options.h"
#include "locale/I18n.h"

ResourcePacksScreen::ResourcePacksScreen() : group(nullptr) {}
ResourcePacksScreen::~ResourcePacksScreen() { delete group; }

void ResourcePacksScreen::init() {
    btnDone = new Button(0, width / 2 - 100, height - 30, 200, 20, I18n::get("gui.done"));
    buttons.push_back(btnDone);
    group = new OptionsGroup("options.resourcepack");
    group->x = width / 2 - 150;
    group->y = 40;
    group->width = 300;
    group->height = height - 80;
    group->setupPositions();
}

void ResourcePacksScreen::buttonClicked(Button* button) {
    if (button->id == 0) {
        minecraft->popScreen();
    }
}

void ResourcePacksScreen::render(int xm, int ym, float a) {
    renderBackground();
    drawCenteredString(font, I18n::get("options.resourcepack"), width / 2, 15, 0xffffff);
    if (group) group->render(minecraft, xm, ym);
    Screen::render(xm, ym, a);
}

void ResourcePacksScreen::mouseClicked(int x, int y, int buttonNum) {
    Screen::mouseClicked(x, y, buttonNum);
    if (group) group->mouseClicked(minecraft, x, y, buttonNum);
}

void ResourcePacksScreen::mouseReleased(int x, int y, int buttonNum) {
    Screen::mouseReleased(x, y, buttonNum);
    if (group) group->mouseReleased(minecraft, x, y, buttonNum);
}

void ResourcePacksScreen::mouseWheel(int dx, int dy, int xm, int ym) {
    Screen::mouseWheel(dx, dy, xm, ym);
    if (group) group->mouseWheel(dx, dy, xm, ym);
}

void ResourcePacksScreen::renderBackground() {
    Screen::renderBackground();
}

void ResourcePacksScreen::keyPressed(int eventKey) {
    if (eventKey == Keyboard::KEY_ESCAPE) {
        minecraft->popScreen();
    }
}

void ResourcePacksScreen::tick() {
    if (group) group->tick(minecraft);
    Screen::tick();
}
