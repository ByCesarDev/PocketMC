#include "MusicSoundScreen.h"
#include "../../Minecraft.h"
#include "../../Options.h"
#include "locale/I18n.h"

MusicSoundScreen::MusicSoundScreen() : group(nullptr) {}
MusicSoundScreen::~MusicSoundScreen() { delete group; }

void MusicSoundScreen::init() {
    btnDone = new Button(0, width / 2 - 100, height - 30, 200, 20, I18n::get("gui.done"));
    buttons.push_back(btnDone);
    group = new OptionsGroup("options.musicAndSounds");
    group->x = width / 2 - 150;
    group->y = 40;
    group->width = 300;
    group->height = height - 80;
    group->addOptionItem(OPTIONS_MUSIC_VOLUME, minecraft);
    group->addOptionItem(OPTIONS_SOUND_VOLUME, minecraft);
    group->setupPositions();
}

void MusicSoundScreen::buttonClicked(Button* button) {
    if (button->id == 0) {
        minecraft->popScreen();
    }
}

void MusicSoundScreen::render(int xm, int ym, float a) {
    renderBackground();
    drawCenteredString(font, I18n::get("options.musicAndSounds"), width / 2, 15, 0xffffff);
    if (group) group->render(minecraft, xm, ym);
    Screen::render(xm, ym, a);
}

void MusicSoundScreen::mouseClicked(int x, int y, int buttonNum) {
    Screen::mouseClicked(x, y, buttonNum);
    if (group) group->mouseClicked(minecraft, x, y, buttonNum);
}

void MusicSoundScreen::mouseReleased(int x, int y, int buttonNum) {
    Screen::mouseReleased(x, y, buttonNum);
    if (group) group->mouseReleased(minecraft, x, y, buttonNum);
}

void MusicSoundScreen::mouseWheel(int dx, int dy, int xm, int ym) {
    Screen::mouseWheel(dx, dy, xm, ym);
    if (group) group->mouseWheel(dx, dy, xm, ym);
}

void MusicSoundScreen::renderBackground() {
    Screen::renderBackground();
}

void MusicSoundScreen::keyPressed(int eventKey) {
    if (eventKey == Keyboard::KEY_ESCAPE) {
        minecraft->popScreen();
    }
}

void MusicSoundScreen::tick() {
    if (group) group->tick(minecraft);
    Screen::tick();
}
