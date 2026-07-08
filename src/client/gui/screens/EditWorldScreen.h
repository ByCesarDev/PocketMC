#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS__EditWorldScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS__EditWorldScreen_H__

#include "../Screen.h"
#include "../components/TextBox.h"
#include "../components/Button.h"
#include "../../../world/level/storage/LevelStorageSource.h"

class EditWorldScreen : public Screen
{
public:
    EditWorldScreen(const LevelSummary& level);
    virtual ~EditWorldScreen();

    virtual void init() override;
    virtual void setupPositions() override;
    virtual void tick() override;
    virtual void render(int xm, int ym, float a) override;

    virtual void buttonClicked(Button* button) override;
    virtual bool handleBackEvent(bool isDown) override;
    virtual void keyPressed(int eventKey) override;
    virtual void charPressed(char c) override;
    virtual void mouseClicked(int x, int y, int buttonNum) override;

private:
    LevelSummary _level;

    TextBox tLevelName;
    Button bSave;
    Button bCancel;
};

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS__EditWorldScreen_H__*/
