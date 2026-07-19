#include "ChatSettingsScreen.h"
#include "../../Minecraft.h"
#include "../../Options.h"
#include "locale/I18n.h"

ChatSettingsScreen::ChatSettingsScreen() : group(nullptr) {}
ChatSettingsScreen::~ChatSettingsScreen() { delete group; }

void ChatSettingsScreen::init() {
    btnDone = new Button(0, width / 2 - 100, height - 30, 200, 20, I18n::get("gui.done"));
    buttons.push_back(btnDone);
    group = new OptionsGroup("options.chat.title");
    group->x = width / 2 - 150;
    group->y = 40;
    group->width = 300;
    group->height = height - 80;
    group->addOptionItem(OPTIONS_CHAT_VISIBLE, minecraft);
    group->addOptionItem(OPTIONS_CHAT_COLORS, minecraft);
    group->setupPositions();
}

void ChatSettingsScreen::buttonClicked(Button* button) {
    if (button->id == 0) {
        minecraft->popScreen();
    }
}

void ChatSettingsScreen::render(int xm, int ym, float a) {
    renderBackground();
    drawCenteredString(font, I18n::get("options.chat.title"), width / 2, 15, 0xffffff);
    if (group) group->render(minecraft, xm, ym);
    Screen::render(xm, ym, a);
}

void ChatSettingsScreen::mouseClicked(int x, int y, int buttonNum) {
    Screen::mouseClicked(x, y, buttonNum);
    if (group) group->mouseClicked(minecraft, x, y, buttonNum);
}

void ChatSettingsScreen::mouseReleased(int x, int y, int buttonNum) {
    Screen::mouseReleased(x, y, buttonNum);
    if (group) group->mouseReleased(minecraft, x, y, buttonNum);
}

void ChatSettingsScreen::mouseWheel(int dx, int dy, int xm, int ym) {
    Screen::mouseWheel(dx, dy, xm, ym);
    if (group) group->mouseWheel(dx, dy, xm, ym);
}

void ChatSettingsScreen::renderBackground() {
    Screen::renderBackground();
}

void ChatSettingsScreen::keyPressed(int eventKey) {
    if (eventKey == Keyboard::KEY_ESCAPE) {
        minecraft->popScreen();
    }
}

void ChatSettingsScreen::tick() {
    if (group) group->tick(minecraft);
    Screen::tick();
}
