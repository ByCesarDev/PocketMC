#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchJoinGameScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchJoinGameScreen_H__

#include "../../Screen.h"
#include "../../components/Button.h"
#include "../../components/TextBox.h"
#include "../../../Minecraft.h"
#include "../../../../platform/input/Multitouch.h"
#include "../../../../network/RakNetInstance.h"
#include "../CustomServerList.h"
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>

namespace Touch {

class JoinGameScreen;

class ServerListWidget : public GuiComponent
{
public:
    ServerListWidget(Minecraft* mc, int x, int y, int w, int h);

    void setFilter(const std::string& filter);
    void render(int xm, int ym, float a);
    bool mouseClicked(int xm, int ym, int btn);
    void scroll(int delta);
    void setBounds(int x, int y, int w, int h);

    // Returns the index into CustomServerList::servers for the selected entry, or -1
    int  selectedRealIndex() const { return (_selected >= 0 && _selected < (int)_filteredIndices.size()) ? _filteredIndices[_selected] : -1; }
    bool hasSelection() const  { return _selected >= 0 && _selected < (int)_filtered.size(); }
    PingedCompatibleServer selectedServer() const { return _filtered[_selected]; }

    void loadServers(const std::vector<PingedCompatibleServer>& servers);

private:
    void rebuildFiltered();
    void drawSlot(int slotIndex, int slotY, bool isSelected, int xm, int ym);

    Minecraft*        _mc;
    int _x, _y, _w, _h;

    std::vector<PingedCompatibleServer> _all;
    std::vector<PingedCompatibleServer> _filtered;
    std::vector<int>                    _filteredIndices; // real index into _all
    std::string       _filter;

    int  _selected;
    int  _scrollOffset;    
    int  _lastClickIndex;
    std::chrono::steady_clock::time_point _lastClickTime;
    static const int SLOT_H = 36;
};

class JoinGameScreen: public Screen
{
public:
	JoinGameScreen();
	virtual ~JoinGameScreen();

	void init();
	void setupPositions();

	virtual bool handleBackEvent(bool isDown);

	virtual bool isIndexValid(int index);

	virtual void tick();
	void render(int xm, int ym, float a);

	void buttonClicked(Button* button);
	virtual void mouseClicked(int x, int y, int buttonNum);
	virtual void keyPressed(int eventKey);
	virtual void charPressed(char c);
	virtual void mouseWheel(int dx, int dy, int xm, int ym);

	bool isInGameScreen();
private:
	Button bJoin;
	Button bDirect;
	Button bAdd;
	Button bEdit;
	Button bDelete;
	Button bRefresh;
	Button bCancel;
	TextBox tSearch;
	ServerListWidget* gamesList;
	int selectedCustomIndex;
};

};

#endif /*NET_MINECRAFT_CLIENT_GUI_SCREENS_TOUCH__TouchJoinGameScreen_H__*/
