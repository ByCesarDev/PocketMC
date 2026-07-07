#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchStartMenuScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchStartMenuScreen_H__

#include "../../Screen.h"
#include "../../components/Button.h"

namespace Touch {

class StartMenuScreen: public Screen
{
public:
	StartMenuScreen();
	virtual ~StartMenuScreen();
	
	void init();
	void setupPositions();

	void tick();
	void render(int xm, int ym, float a);

	void buttonClicked(Button* button);
	virtual void mouseClicked(int x, int y, int buttonNum);
	bool handleBackEvent(bool isDown);
	bool isInGameScreen();
private:
	
	Button bHost;
	Button bJoin;
	Button bOptions;
	Button bProfile;
	Button bSkindex;
	Button bQuit;

	std::string copyright;
	std::string version;
	std::string username;
	int panoramaTicks;
};
};

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchStartMenuScreen_H__*/
