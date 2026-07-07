#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS_NEWPACKSCREEN_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS_NEWPACKSCREEN_H__

#include "../Screen.h"
#include "../components/Button.h"
#include "client/gui/components/TextBox.h"
#include <string>

class NewPackScreen : public Screen
{
	typedef Screen super;
public:
	NewPackScreen();
	virtual ~NewPackScreen();
	
	virtual void init() override;
	virtual void setupPositions() override;
	virtual void render(int xm, int ym, float a) override;
	virtual void tick() override;
	virtual void keyPressed(int eventKey) override;
	virtual void removed() override;

protected:
	virtual void buttonClicked(Button* button) override;

private:
	Button _btnDone;
	Button _btnCancel;
	TextBox tName;
};

#endif
