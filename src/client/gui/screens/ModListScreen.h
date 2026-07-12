#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS__ModListScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS__ModListScreen_H__

#include "../Screen.h"
#include "../components/Button.h"
#include "../../../mods/ModRegistry.h"

#include <vector>

class ModListScreen: public Screen
{
public:
    ModListScreen();

    void init();
    void setupPositions();
    void render(int xm, int ym, float a);
    void mouseClicked(int x, int y, int buttonNum);
    void mouseWheel(int dx, int dy, int xm, int ym);
    bool handleBackEvent(bool isDown);
    bool isInGameScreen();

protected:
    void buttonClicked(Button* button);

private:
    int modAt(int x, int y) const;
    void openModsFolder();

    Button bOpenFolder;
    Button bDone;
    std::vector<ModInfo> mods;
    int selected;
    int scrollOffset;
    int listX;
    int listY;
    int listW;
    int listH;
    int detailX;
    int detailY;
    int detailW;
    int detailH;
};

#endif
