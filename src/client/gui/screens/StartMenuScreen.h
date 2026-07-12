#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS__StartMenuScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS__StartMenuScreen_H__

#include "../Screen.h"
#include "../components/Button.h"

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
	bool handleBackEvent(bool isDown);
	bool isInGameScreen();
private:

	Button bHost;
	Button bJoin;
	Button bOptions;
	Button bProfile;
	Button bSkindex;
	Button bMods;
	Button bQuit; // X button in top-right corner

	std::string copyright;
	int copyrightPosX;

	std::string version;
	int versionPosX;

	std::string username;
	int panoramaTicks;
};

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS__StartMenuScreen_H__*/
