#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchSelectWorldScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchSelectWorldScreen_H__

#include "../ConfirmScreen.h"
#include "../../Screen.h"
#include "../../components/Button.h"
#include "../../components/TextBox.h"
#include "../../../Minecraft.h"
#include "../../../../world/level/storage/LevelStorageSource.h"
// Reuse the vertical-list widget from the desktop screen
#include "../SelectWorldScreen.h"

namespace Touch {

//
// Delete confirmation screen
//
class TouchDeleteWorldScreen: public ConfirmScreen
{
public:
    TouchDeleteWorldScreen(const LevelSummary& level);
protected:
    virtual void postResult(bool isOk);
private:
    LevelSummary _level;
};


//
// Select world screen (Java-edition vertical list layout)
//
class SelectWorldScreen: public Screen
{
public:
    SelectWorldScreen();
    virtual ~SelectWorldScreen();

    virtual void init() override;
    virtual void setupPositions() override;
    virtual void tick() override;
    virtual void render(int xm, int ym, float a) override;

    virtual bool handleBackEvent(bool isDown) override;
    virtual void buttonClicked(Button* button) override;
    virtual void mouseClicked(int x, int y, int buttonNum) override;
    virtual void keyPressed(int eventKey) override;
    virtual void charPressed(char c) override;

    virtual void mouseWheel(int dx, int dy, int xm, int ym) override;
    bool isInGameScreen() override;

private:
    void loadLevels();
    std::string getUniqueLevelName(const std::string& base);
    void updateButtonStates();

    // Buttons matching reference image (ids 1-6)
    Button bPlay;       // 1  Play Selected World
    Button bCreate;     // 2  Create New World
    Button bEdit;       // 3  Edit
    Button bDelete;     // 4  Delete
    Button bRecreate;   // 5  Re-Create
    Button bCancel;     // 6  Cancel

    TextBox tSearch;

    WorldListWidget* worldList;
    LevelSummaryList levels;

    bool _hasStartedLevel;
};

} // namespace Touch

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchSelectWorldScreen_H__*/
