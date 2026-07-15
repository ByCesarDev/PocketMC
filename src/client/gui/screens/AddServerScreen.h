#ifndef POCKETMC_ADDSERVERSCREEN_H
#define POCKETMC_ADDSERVERSCREEN_H

#include "../Screen.h"
#include "../components/Button.h"
#include "../components/TextBox.h"

class AddServerScreen : public Screen {
public:
    AddServerScreen(int editIndex = -1);
    virtual ~AddServerScreen();

    void init() override;
    void setupPositions() override;
    void render(int xm, int ym, float a) override;
    void buttonClicked(Button* button) override;
    void keyPressed(int eventKey) override;
    void tick() override;

private:
    int editingIndex;

    Button bDone;
    Button bCancel;
    TextBox tName;
    TextBox tIP;
};

#endif
