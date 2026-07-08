#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS__SelectWorldScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS__SelectWorldScreen_H__

#include "../Screen.h"
#include "../components/Button.h"
#include "../components/TextBox.h"
#include "../../Minecraft.h"
#include "../../../world/level/storage/LevelStorageSource.h"
#include <string>
#include <vector>
#include <algorithm>

class SelectWorldScreen;

//
// Vertical scrolling world selection list (Java-Edition style)
//
class WorldListWidget : public GuiComponent
{
public:
    WorldListWidget(Minecraft* mc, int x, int y, int w, int h);

    void setFilter(const std::string& filter);
    void render(int xm, int ym, float a);
    void mouseClicked(int xm, int ym, int btn);
    void scroll(int delta);

    int  selectedIndex() const { return _selected; }
    bool hasSelection() const  { return _selected >= 0 && _selected < (int)_filtered.size(); }
    const LevelSummary& selectedLevel() const { return _filtered[_selected]; }

    void loadLevels(const LevelSummaryList& levels);

private:
    void rebuildFiltered();
    void drawSlot(int slotIndex, int slotY, bool isSelected, int xm, int ym);

    Minecraft*        _mc;
    int _x, _y, _w, _h;

    LevelSummaryList  _all;
    LevelSummaryList  _filtered;
    std::string       _filter;

    int  _selected;
    int  _scrollOffset;    // pixels scrolled
    static const int SLOT_H = 36;
};


//
// Delete confirmation screen
//
#include "ConfirmScreen.h"
class DeleteWorldScreen: public ConfirmScreen
{
public:
    DeleteWorldScreen(const LevelSummary& level);
protected:
    virtual void postResult(bool isOk);
private:
    LevelSummary _level;
};


//
// Select world screen (Java-edition layout)
//
class SelectWorldScreen: public Screen
{
public:
    SelectWorldScreen();
    virtual ~SelectWorldScreen();

    virtual void init();
    virtual void setupPositions();
    virtual void tick();

    virtual bool handleBackEvent(bool isDown);
    virtual void buttonClicked(Button* button);
    virtual void mouseClicked(int x, int y, int buttonNum);
    virtual void keyPressed(int eventKey);
    virtual void charPressed(char c);

    void render(int xm, int ym, float a);
    virtual void mouseWheel(int dx, int dy, int xm, int ym);
    bool isInGameScreen();

private:
    void loadLevels();
    std::string getUniqueLevelName(const std::string& base);
    void updateButtonStates();

    // Buttons (ids 1-6 matching the reference image)
    Button bPlay;       // 1  Play Selected World
    Button bCreate;     // 2  Create New World
    Button bEdit;       // 3  Edit
    Button bDelete;     // 4  Delete
    Button bRecreate;   // 5  Re-Create
    Button bCancel;     // 6  Cancel

    TextBox tSearch;    // search / filter box

    WorldListWidget* worldList;
    LevelSummaryList levels;

    bool _hasStartedLevel;
};

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS__SelectWorldScreen_H__*/
