#include "AddServerScreen.h"
#include "CustomServerList.h"
#include "ScreenChooser.h"
#include "../Font.h"
#include "../../Minecraft.h"
#include "../../../locale/I18n.h"
#include "../../../platform/input/Keyboard.h"

AddServerScreen::AddServerScreen(int editIndex)
:   editingIndex(editIndex),
    bDone(0, I18n::get(editIndex >= 0 ? "addServer.add" : "addServer.add")),
    bCancel(1, I18n::get("gui.cancel")),
    tName(2, ""),
    tIP(3, "")
{
    if (editingIndex >= 0 && editingIndex < (int)CustomServerList::servers.size()) {
        tName.text = CustomServerList::servers[editingIndex].name.C_String();
        tIP.text = CustomServerList::servers[editingIndex].address.ToString(true, ':');
    } else {
        tName.text = "Minecraft Server";
        tIP.text = "";
    }
}

AddServerScreen::~AddServerScreen() {}

void AddServerScreen::init() {
    buttons.push_back(&bDone);
    buttons.push_back(&bCancel);
    textBoxes.push_back(&tName);
    textBoxes.push_back(&tIP);
#ifdef ANDROID
    tabButtons.push_back(&bDone);
    tabButtons.push_back(&bCancel);
#endif
}

void AddServerScreen::setupPositions() {
    int yBase = height / 4 + 72 + 12;

    bDone.width = 100;
    bDone.height = 20;
    bDone.x = width / 2 - 100 - 2;
    bDone.y = yBase;

    bCancel.width = 100;
    bCancel.height = 20;
    bCancel.x = width / 2 + 2;
    bCancel.y = yBase;

    tName.width = 200;
    tName.height = 20;
    tName.x = width / 2 - 100;
    tName.y = height / 4;

    tIP.width = 200;
    tIP.height = 20;
    tIP.x = width / 2 - 100;
    tIP.y = height / 4 + 36;
}

void AddServerScreen::tick() {
    Screen::tick();
    bDone.active = !tIP.text.empty() && !tName.text.empty();
}

void AddServerScreen::render(int xm, int ym, float a) {
    renderBackground();

    const std::string title = (editingIndex >= 0)
        ? I18n::get("addServer.title")
        : I18n::get("addServer.addTitle");
    drawCenteredString(minecraft->font, title, width / 2, 17, 0xffffffff);
    drawString(minecraft->font, I18n::get("addServer.enterName"), width / 2 - 100, height / 4 - 10, 0xa0a0a0);
    drawString(minecraft->font, I18n::get("addServer.enterIp"), width / 2 - 100, height / 4 + 36 - 10, 0xa0a0a0);

    Screen::render(xm, ym, a);
}

void AddServerScreen::buttonClicked(Button* button) {
    if (button->id == bCancel.id) {
        minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
    } else if (button->id == bDone.id) {
        PingedCompatibleServer s;
        s.name = tName.text.c_str();
        // Try IPv6-style first (with |), then port-colon style
        if (!s.address.FromString(tIP.text.c_str(), '|', 0)) {
            s.address.FromString(tIP.text.c_str(), ':', 0);
        }
        s.isSpecial = false;

        if (editingIndex >= 0 && editingIndex < (int)CustomServerList::servers.size()) {
            CustomServerList::servers[editingIndex] = s;
        } else {
            CustomServerList::servers.push_back(s);
        }
        CustomServerList::save(minecraft);

        minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
    }
}

void AddServerScreen::keyPressed(int eventKey) {
    if (eventKey == Keyboard::KEY_ESCAPE) {
        minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
        return;
    }
    Screen::keyPressed(eventKey);
}
