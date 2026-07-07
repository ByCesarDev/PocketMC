#include "RenameSkinScreen.h"
#include "SkindexScreen.h"
#include "../../Minecraft.h"
#include "../../player/LocalPlayer.h"
#include "../Font.h"
#include "../../../platform/input/Keyboard.h"
#include "../../../AppPlatform.h"
#include "../../../locale/I18n.h"
#include <cstdio>
#include <algorithm>

RenameSkinScreen::RenameSkinScreen(const std::string& skinPath)
:   _btnDone(0, I18n::get("gui.done")),
    _btnCancel(1, I18n::get("gui.cancel")),
    tName(0, ""),
    _skinPath(skinPath)
{
}

RenameSkinScreen::~RenameSkinScreen() {}

void RenameSkinScreen::init() {
    _btnDone.active = false;
    buttons.push_back(&_btnDone);
    buttons.push_back(&_btnCancel);
    textBoxes.push_back(&tName);
    
    // Pre-fill TextBox with current filename (without folder and .png)
    std::string filename = _skinPath;
    size_t pos = filename.find_last_of("\\/");
    if (pos != std::string::npos) {
        filename = filename.substr(pos + 1);
    }
    if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".png") {
        filename = filename.substr(0, filename.length() - 4);
    }
    tName.text = filename;
    _btnDone.active = !tName.text.empty();
    
    setupPositions();
}

void RenameSkinScreen::setupPositions() {
    int cx = width / 2;
    int cy = height / 2;
    
    tName.width = 150;
    tName.height = 20;
    tName.x = (width - tName.width) / 2;
    tName.y = cy - 20;
    
    _btnCancel.width = 70;
    _btnCancel.height = 24;
    _btnCancel.x = width / 2 - _btnCancel.width - 4;
    _btnCancel.y = cy + 20;
    
    _btnDone.width = 70;
    _btnDone.height = 24;
    _btnDone.x = width / 2 + 4;
    _btnDone.y = cy + 20;
}

void RenameSkinScreen::tick() {
    for (auto* tb : textBoxes) {
        tb->tick(minecraft);
    }
}

void RenameSkinScreen::keyPressed(int eventKey) {
    if (eventKey == Keyboard::KEY_RETURN) {
        if (!tName.text.empty()) {
            buttonClicked(&_btnDone);
        }
    }
    Screen::keyPressed(eventKey);
    _btnDone.active = !tName.text.empty();
}

void RenameSkinScreen::removed() {
    minecraft->platform()->hideKeyboard();
}

void RenameSkinScreen::buttonClicked(Button* button) {
    if (button == &_btnCancel) {
        minecraft->setScreen(new SkindexScreen());
    } else if (button == &_btnDone && !tName.text.empty()) {
        std::string newName = tName.text;
        // Clean filename
        static char ILLEGAL_FILE_CHARACTERS[] = {
            '/', '\n', '\r', '\t', '\0', '\f', '`', '?', '*', '\\', '<', '>', '|', '\"', ':'
        };
        for (int i = 0; i < sizeof(ILLEGAL_FILE_CHARACTERS) / sizeof(char); ++i) {
            size_t pos;
            while ((pos = newName.find(ILLEGAL_FILE_CHARACTERS[i])) != std::string::npos) {
                newName.erase(pos, 1);
            }
        }
        
        if (!newName.empty()) {
            std::string folder = "";
            size_t pos = _skinPath.find_last_of("\\/");
            if (pos != std::string::npos) {
                folder = _skinPath.substr(0, pos + 1);
            }
            
            std::string src = _skinPath;
            std::string dest = folder + newName + ".png";
            
            if (src != dest) {
                std::string currentOptionSkin = minecraft->options.getStringValue(OPTIONS_SKIN);
                if (std::rename(src.c_str(), dest.c_str()) == 0) {
                    if (currentOptionSkin == src) {
                        minecraft->options.set(OPTIONS_SKIN, dest);
                        minecraft->options.save();
                        if (minecraft->player) {
                            minecraft->player->textureName = dest;
                        }
                    }
                }
            }
        }
        minecraft->setScreen(new SkindexScreen());
    }
}

void RenameSkinScreen::render(int xm, int ym, float a) {
    renderBackground();
    drawCenteredString(font, "Renombrar Skin", width / 2, height / 2 - 50, 0xffffff);
    super::render(xm, ym, a);
}
