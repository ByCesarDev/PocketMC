#include "EditServerScreen.h"
#include "CustomServerList.h"
#include "ScreenChooser.h"
#include "../Font.h"
#include "../../Minecraft.h"
#include "../../../locale/I18n.h"
#include "../../../platform/input/Keyboard.h"

EditServerScreen::EditServerScreen(int serverIndex)
:   _serverIndex(serverIndex),
    bDone  (0, I18n::get("addServer.add")),
    bCancel(1, I18n::get("gui.cancel")),
    tName  (2, ""),
    tIP    (3, "")
{
    // Pre-fill with current server data
    if (_serverIndex >= 0 && _serverIndex < (int)CustomServerList::servers.size()) {
        tName.text = CustomServerList::servers[_serverIndex].name.C_String();
        tIP.text   = CustomServerList::servers[_serverIndex].address.ToString(true, ':');
    }
}

EditServerScreen::~EditServerScreen() {}

void EditServerScreen::init() {
    buttons.push_back(&bDone);
    buttons.push_back(&bCancel);
    textBoxes.push_back(&tName);
    textBoxes.push_back(&tIP);
}

void EditServerScreen::setupPositions() {
    int yBase = height / 4 + 72 + 12;

    bDone.width  = 100; bDone.height  = 20;
    bDone.x = width / 2 - 100 - 2;
    bDone.y = yBase;

    bCancel.width  = 100; bCancel.height  = 20;
    bCancel.x = width / 2 + 2;
    bCancel.y = yBase;

    tName.width = 200; tName.height = 20;
    tName.x = width / 2 - 100;
    tName.y = height / 4;

    tIP.width = 200; tIP.height = 20;
    tIP.x = width / 2 - 100;
    tIP.y = height / 4 + 36;
}

void EditServerScreen::tick() {
    Screen::tick();
    bDone.active = !tIP.text.empty() && !tName.text.empty();
}

void EditServerScreen::render(int xm, int ym, float a) {
    renderBackground();

    drawCenteredString(minecraft->font, I18n::get("addServer.title"), width / 2, 17, 0xffffffff);
    drawString(minecraft->font, I18n::get("addServer.enterName"),
               tName.x, tName.y - 10, 0xa0a0a0);
    drawString(minecraft->font, I18n::get("addServer.enterIp"),
               tIP.x,   tIP.y   - 10, 0xa0a0a0);

    Screen::render(xm, ym, a);
}

void EditServerScreen::buttonClicked(Button* button) {
    if (button->id == bCancel.id) {
        minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
        return;
    }
    if (button->id == bDone.id) {
        if (_serverIndex >= 0 && _serverIndex < (int)CustomServerList::servers.size()) {
            PingedCompatibleServer& s = CustomServerList::servers[_serverIndex];
            s.name = tName.text.c_str();
            if (!s.address.FromString(tIP.text.c_str(), '|', 0))
                s.address.FromString(tIP.text.c_str(), ':', 0);
            CustomServerList::save(minecraft);
        }
        minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
    }
}

void EditServerScreen::keyPressed(int eventKey) {
    if (eventKey == Keyboard::KEY_ESCAPE) {
        minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
        return;
    }
    Screen::keyPressed(eventKey);
}
