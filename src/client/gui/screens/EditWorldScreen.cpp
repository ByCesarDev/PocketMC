#include "EditWorldScreen.h"
#include "SelectWorldScreen.h"
#include "../../Minecraft.h"
#include "../../../locale/I18n.h"
#include "../../../util/StringUtils.h"

EditWorldScreen::EditWorldScreen(const LevelSummary& level)
    : _level(level),
      tLevelName(0, I18n::get("selectWorld.enterName")),
      bSave(1, I18n::get("selectWorld.renameButton")),
      bCancel(2, I18n::get("gui.cancel"))
{
    tLevelName.text = level.name;
    tLevelName.active = true;
    tLevelName.visible = true;
}

EditWorldScreen::~EditWorldScreen()
{
}

void EditWorldScreen::init()
{
    textBoxes.push_back(&tLevelName);
    buttons.push_back(&bSave);
    buttons.push_back(&bCancel);
}

void EditWorldScreen::setupPositions()
{
    const int CX = width / 2;
    const int TB_W = 200;
    
    tLevelName.width = TB_W;
    tLevelName.height = 20;
    tLevelName.x = CX - TB_W / 2;
    tLevelName.y = height / 2 - 20;

    const int BW = 98;
    const int BH = 20;
    const int GAP = 4;
    
    bSave.width = BW; bSave.height = BH;
    bCancel.width = BW; bCancel.height = BH;

    bSave.x = CX - BW - GAP / 2;
    bSave.y = height / 2 + 10;
    
    bCancel.x = CX + GAP / 2;
    bCancel.y = height / 2 + 10;
}

void EditWorldScreen::tick()
{
    bSave.active = !Util::stringTrim(tLevelName.text).empty();
}

void EditWorldScreen::buttonClicked(Button* button)
{
    if (button->id == bCancel.id) {
        minecraft->screenChooser.setScreen(SCREEN_SELECTWORLD);
    }
    else if (button->id == bSave.id && bSave.active) {
        std::string newName = Util::stringTrim(tLevelName.text);
        if (!newName.empty()) {
            minecraft->getLevelSource()->renameLevel(_level.id, newName);
        }
        minecraft->screenChooser.setScreen(SCREEN_SELECTWORLD);
    }
}

bool EditWorldScreen::handleBackEvent(bool isDown)
{
    if (!isDown) {
        minecraft->screenChooser.setScreen(SCREEN_SELECTWORLD);
    }
    return true;
}

void EditWorldScreen::keyPressed(int eventKey)
{
    Screen::keyPressed(eventKey);
}

void EditWorldScreen::charPressed(char c)
{
    for (TextBox* tb : textBoxes) {
        if (tb->focused) {
            tb->charPressed(minecraft, c);
        }
    }
}

void EditWorldScreen::mouseClicked(int x, int y, int buttonNum)
{
    Screen::mouseClicked(x, y, buttonNum);
}

void EditWorldScreen::render(int xm, int ym, float a)
{
    renderBackground();

    drawCenteredString(minecraft->font, I18n::get("selectWorld.renameTitle").c_str(), width / 2, 20, 0xFFFFFFFF);
    drawString(minecraft->font, I18n::get("selectWorld.enterName").c_str(), tLevelName.x, tLevelName.y - 10, 0xFFA0A0A0);

    Screen::render(xm, ym, a);
}
