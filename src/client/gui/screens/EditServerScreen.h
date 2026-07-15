#ifndef POCKETMC_EDITSERVERSCREEN_H
#define POCKETMC_EDITSERVERSCREEN_H

#include "../Screen.h"
#include "../components/Button.h"
#include "../components/TextBox.h"

// Screen for editing an existing server entry.
// Receives the index into CustomServerList::servers to edit.
class EditServerScreen : public Screen {
public:
    explicit EditServerScreen(int serverIndex);
    virtual ~EditServerScreen();

    void init() override;
    void setupPositions() override;
    void render(int xm, int ym, float a) override;
    void buttonClicked(Button* button) override;
    void keyPressed(int eventKey) override;
    void tick() override;

private:
    int _serverIndex;

    Button bDone;
    Button bCancel;
    TextBox tName;
    TextBox tIP;
};

#endif // POCKETMC_EDITSERVERSCREEN_H
