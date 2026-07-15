#include "TouchJoinGameScreen.h"
#include "../StartMenuScreen.h"
#include "../JoinByIPScreen.h"
#include "../AddServerScreen.h"
#include "../ProgressScreen.h"
#include "../ScreenChooser.h"
#include "../../Font.h"
#include "../../../Minecraft.h"
#include "../../../renderer/Textures.h"
#include "../../../../locale/I18n.h"
#include "../../../../network/ClientSideNetworkHandler.h"
#include "../CustomServerList.h"
#include "../EditServerScreen.h"
#include "../../../renderer/Tesselator.h"

#undef min
#undef max

namespace Touch {

//
// Games list
//

static bool strContainsCITouch(const std::string& haystack, const std::string& needle)
{
    if (needle.empty()) return true;
    std::string h = haystack, n = needle;
    std::transform(h.begin(), h.end(), h.begin(), ::tolower);
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);
    return h.find(n) != std::string::npos;
}

ServerListWidget::ServerListWidget(Minecraft* mc, int x, int y, int w, int h)
    : _mc(mc), _x(x), _y(y), _w(w), _h(h),
      _selected(-1), _scrollOffset(0), _lastClickIndex(-1),
      _lastClickTime(std::chrono::steady_clock::now())
{}

void ServerListWidget::setBounds(int x, int y, int w, int h)
{
    _x = x; _y = y; _w = w; _h = h;
    int maxScroll = std::max(0, (int)_filtered.size() * SLOT_H - _h);
    if (_scrollOffset > maxScroll) _scrollOffset = maxScroll;
}

void ServerListWidget::loadServers(const std::vector<PingedCompatibleServer>& servers)
{
    _all = servers;
    rebuildFiltered();
}

void ServerListWidget::setFilter(const std::string& filter)
{
    _filter = filter;
    int prevSel = _selected;
    rebuildFiltered();
    if (prevSel >= (int)_filtered.size())
        _selected = _filtered.empty() ? -1 : 0;
}

void ServerListWidget::rebuildFiltered()
{
    _filtered.clear();
    for (const PingedCompatibleServer& s : _all) {
        if (strContainsCITouch(s.name.C_String(), _filter) || strContainsCITouch(s.address.ToString(false), _filter)) {
            _filtered.push_back(s);
        }
    }
    if (_selected >= (int)_filtered.size())
        _selected = _filtered.empty() ? -1 : (int)_filtered.size() - 1;
    int maxScroll = std::max(0, (int)_filtered.size() * SLOT_H - _h);
    if (_scrollOffset > maxScroll) _scrollOffset = maxScroll;
}

void ServerListWidget::scroll(int delta)
{
    _scrollOffset -= delta;
    int maxScroll = std::max(0, (int)_filtered.size() * SLOT_H - _h);
    if (_scrollOffset < 0) _scrollOffset = 0;
    if (_scrollOffset > maxScroll) _scrollOffset = maxScroll;
}

bool ServerListWidget::mouseClicked(int xm, int ym, int btn)
{
    if (btn != 1) return false;
    if (xm < _x || xm > _x + _w) return false;
    if (ym < _y || ym > _y + _h) return false;

    int relY = ym - _y + _scrollOffset;
    int idx  = relY / SLOT_H;
    if (idx >= 0 && idx < (int)_filtered.size()) {
        const auto now = std::chrono::steady_clock::now();
        const int elapsedMs = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastClickTime).count();
        bool activate = false;
#if defined(ANDROID) || defined(__APPLE__)
        activate = true;
#else
        activate = (_selected == idx && _lastClickIndex == idx && elapsedMs > 0 && elapsedMs <= 500);
#endif
        _selected = idx;
        _lastClickIndex = idx;
        _lastClickTime = now;
        return activate;
    }
    return false;
}

void ServerListWidget::render(int xm, int ym, float /*a*/)
{
    fill(_x, _y, _x + _w, _y + _h, 0x80000000);
    int startSlot = _scrollOffset / SLOT_H;
    int endSlot   = std::min((int)_filtered.size(), startSlot + _h / SLOT_H + 2);

    for (int i = startSlot; i < endSlot; ++i) {
        int slotY = _y + i * SLOT_H - _scrollOffset;
        if (slotY + SLOT_H < _y || slotY > _y + _h) continue;
        drawSlot(i, slotY, i == _selected, xm, ym);
    }
    fillGradient(_x, _y,           _x + _w, _y + 4,  0x60000000, 0x00000000);
    fillGradient(_x, _y + _h - 4,  _x + _w, _y + _h, 0x00000000, 0x60000000);
}

void ServerListWidget::drawSlot(int idx, int slotY, bool isSelected, int /*xm*/, int /*ym*/)
{
    const PingedCompatibleServer& s = _filtered[idx];
    if (isSelected) {
        fill(_x,     slotY,          _x + _w, slotY + SLOT_H, 0x60FFFFFF);
        fill(_x + 1, slotY + 1,      _x + _w - 1, slotY + SLOT_H - 1, 0xC0222222);
    } else {
        int shade = (idx % 2 == 0) ? 0x55000000 : 0x33000000;
        fill(_x, slotY, _x + _w, slotY + SLOT_H, shade);
    }

    const int THUMB = 32;
    const int imgX = _x + 2;
    const int imgY = slotY + (SLOT_H - THUMB) / 2;

    _mc->textures->loadAndBindTexture("gui/default_world.png");
    Tesselator& t = Tesselator::instance;
    t.begin();
    t.color(0xFFFFFFFF);
    t.vertexUV((float)imgX,        (float)(imgY + THUMB), blitOffset, 0, 1);
    t.vertexUV((float)(imgX+THUMB),(float)(imgY + THUMB), blitOffset, 1, 1);
    t.vertexUV((float)(imgX+THUMB),(float)imgY,           blitOffset, 1, 0);
    t.vertexUV((float)imgX,        (float)imgY,           blitOffset, 0, 0);
    t.draw();

    int tx = _x + THUMB + 6;
    int ty = slotY + 3;
    unsigned int color  = s.isSpecial? 0x6090a0 : 0xffffb0;
    unsigned int color2 = 0xffffa0;
    drawString(_mc->font, s.name.C_String(), tx, ty, color);
    drawString(_mc->font, s.address.ToString(false), tx, ty + 10, color2);
}


//
// Join Game screen (Multiplayer)
//
JoinGameScreen::JoinGameScreen()
:	bJoin(   2, I18n::get("selectServer.select")),
	bDirect( 3, I18n::get("selectServer.direct")),
	bAdd(    4, I18n::get("selectServer.add")),
	bEdit(   5, I18n::get("selectServer.edit")),
	bDelete( 6, I18n::get("selectServer.delete")),
	bRefresh(7, I18n::get("selectServer.refresh")),
	bCancel( 8, I18n::get("gui.cancel")),
	tSearch( 0, I18n::get("selectWorld.search")),
	gamesList(NULL),
	selectedCustomIndex(-1)
{
	bJoin.active   = false;
	bEdit.active   = false;
	bDelete.active = false;
}

JoinGameScreen::~JoinGameScreen()
{
	delete gamesList;
}

void JoinGameScreen::init()
{
	CustomServerList::load(minecraft);

	buttons.push_back(&bJoin);
	buttons.push_back(&bDirect);
	buttons.push_back(&bAdd);
	buttons.push_back(&bEdit);
	buttons.push_back(&bDelete);
	buttons.push_back(&bRefresh);
	buttons.push_back(&bCancel);

	int listW = width - 60;
	if (listW > 400) listW = 400;
	int listX = width / 2 - listW / 2;

	gamesList = new ServerListWidget(minecraft, listX, 45, listW, height - 45 - 64 - 4);
	gamesList->loadServers(CustomServerList::servers);

	tSearch.x      = listX;
	tSearch.y      = 22;
	tSearch.width  = listW;
	tSearch.height = 18;
	tSearch.active = true;
	tSearch.visible= true;
	textBoxes.push_back(&tSearch);

#ifdef ANDROID
	tabButtons.push_back(&bJoin);
	tabButtons.push_back(&bDirect);
	tabButtons.push_back(&bAdd);
	tabButtons.push_back(&bEdit);
	tabButtons.push_back(&bDelete);
	tabButtons.push_back(&bRefresh);
	tabButtons.push_back(&bCancel);
#endif
}

void JoinGameScreen::setupPositions() {
	int listW = width - 60;
	if (listW > 400) listW = 400;
	if (listW < 220) listW = width - 12;
	int listX = width / 2 - listW / 2;

	tSearch.x      = listX;
	tSearch.y      = 22;
	tSearch.width  = listW;
	tSearch.height = 18;

	if (gamesList)
		gamesList->setBounds(listX, 45, listW, std::max(36, height - 45 - 64 - 4));

	int bW = 100, bH = 20;
	int row1Y = height - 52;
	int row2Y = height - 28;

	// Row 1 (top row of buttons at bottom):
	// [Join Server] [Direct Connection] [Add Server]
	bJoin.width    = bW; bJoin.height    = bH;
	bDirect.width  = bW; bDirect.height  = bH;
	bAdd.width     = bW; bAdd.height     = bH;

	bJoin.x   = width / 2 - 150 - 2;
	bJoin.y   = row1Y;
	bDirect.x = width / 2 - 50;
	bDirect.y = row1Y;
	bAdd.x    = width / 2 + 52;
	bAdd.y    = row1Y;

	// Row 2 (bottom row):
	// [Edit] [Delete] [Refresh] [Cancel]
	bEdit.width    = bW; bEdit.height    = bH;
	bDelete.width  = bW; bDelete.height  = bH;
	bRefresh.width = bW; bRefresh.height = bH;
	bCancel.width  = bW; bCancel.height  = bH;

	bEdit.x    = width / 2 - 202;
	bEdit.y    = row2Y;
	bDelete.x  = width / 2 - 102;
	bDelete.y  = row2Y;
	bRefresh.x = width / 2;
	bRefresh.y = row2Y;
	bCancel.x  = width / 2 + 102;
	bCancel.y  = row2Y;
}

void JoinGameScreen::buttonClicked(Button* button)
{
	if (button->id == bJoin.id)
	{
		if (gamesList && gamesList->hasSelection())
		{
			PingedCompatibleServer selectedServer = gamesList->selectedServer();
			minecraft->isLookingForMultiplayer = true;
			minecraft->netCallback = new ClientSideNetworkHandler(minecraft, minecraft->raknetInstance);
			minecraft->joinMultiplayer(selectedServer);
			bJoin.active   = false;
			bCancel.active = false;
			minecraft->setScreen(new ProgressScreen());
		}
	}

	if (button->id == bDirect.id)
	{
		minecraft->cancelLocateMultiplayer();
		minecraft->screenChooser.setScreen(SCREEN_JOINBYIP);
	}

	if (button->id == bAdd.id)
	{
		minecraft->cancelLocateMultiplayer();
		minecraft->setScreen(new AddServerScreen(-1));
	}

	if (button->id == bEdit.id)
	{
		if (gamesList && gamesList->hasSelection())
		{
			PingedCompatibleServer sel = gamesList->selectedServer();
			int idx = -1;
			for (size_t i = 0; i < CustomServerList::servers.size(); ++i) {
				if (CustomServerList::servers[i].name == sel.name && CustomServerList::servers[i].address.ToString(false) == sel.address.ToString(false)) {
					idx = (int)i;
					break;
				}
			}
			if (idx != -1) {
				minecraft->cancelLocateMultiplayer();
				minecraft->setScreen(new AddServerScreen(idx));
			}
		}
	}

	if (button->id == bDelete.id)
	{
		if (gamesList && gamesList->hasSelection())
		{
			PingedCompatibleServer sel = gamesList->selectedServer();
			int idx = -1;
			for (size_t i = 0; i < CustomServerList::servers.size(); ++i) {
				if (CustomServerList::servers[i].name == sel.name && CustomServerList::servers[i].address.ToString(false) == sel.address.ToString(false)) {
					idx = (int)i;
					break;
				}
			}
			if (idx != -1) {
				CustomServerList::servers.erase(CustomServerList::servers.begin() + idx);
				CustomServerList::save(minecraft);
				gamesList->loadServers(CustomServerList::servers);
				bJoin.active   = false;
				bEdit.active   = false;
				bDelete.active = false;
			}
		}
	}

	if (button->id == bRefresh.id)
	{
		CustomServerList::load(minecraft);
		if (gamesList) gamesList->loadServers(CustomServerList::servers);
		bJoin.active   = false;
		bEdit.active   = false;
		bDelete.active = false;
	}

	if (button->id == bCancel.id)
	{
		minecraft->cancelLocateMultiplayer();
		minecraft->screenChooser.setScreen(SCREEN_STARTMENU);
	}
}

bool JoinGameScreen::handleBackEvent(bool isDown)
{
	if (!isDown)
	{
		minecraft->cancelLocateMultiplayer();
		minecraft->screenChooser.setScreen(SCREEN_STARTMENU);
	}
	return true;
}


bool JoinGameScreen::isIndexValid( int index )
{
	return false;
}

void JoinGameScreen::tick()
{
	bool valid = gamesList && gamesList->hasSelection();
	bJoin.active   = valid;
	bEdit.active   = valid;
	bDelete.active = valid;
}

void JoinGameScreen::charPressed(char c)
{
	// Screen::charPressed already forwarded to textboxes; just update the filter.
	if (gamesList) gamesList->setFilter(tSearch.text);
}

void JoinGameScreen::mouseWheel(int /*dx*/, int dy, int /*xm*/, int /*ym*/)
{
	if (gamesList)
		gamesList->scroll(dy * 10);
}

void JoinGameScreen::mouseClicked(int x, int y, int buttonNum)
{
	Screen::mouseClicked(x, y, buttonNum);
	if (gamesList) {
		if (gamesList->mouseClicked(x, y, buttonNum) && gamesList->hasSelection())
			buttonClicked(&bJoin);
	}
}

void JoinGameScreen::keyPressed(int eventKey)
{
	Screen::keyPressed(eventKey);
}

void JoinGameScreen::render( int xm, int ym, float a )
{
	renderBackground();
	if (gamesList) gamesList->render(xm, ym, a);
	Screen::render(xm, ym, a);

	drawCenteredString(minecraft->font, I18n::get("selectServer.title"), width / 2, 8, 0xffffffff);
	drawString(minecraft->font, (I18n::get("selectWorld.search") + ":").c_str(), tSearch.x, tSearch.y - 10, 0xFFFFFFFF);
}

bool JoinGameScreen::isInGameScreen() { return false; }

};
