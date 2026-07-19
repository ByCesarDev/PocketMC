#include "JoinGameScreen.h"
#include "StartMenuScreen.h"
#include "ProgressScreen.h"
#include "../Font.h"
#include "../../../network/RakNetInstance.h"
#include "../../../locale/I18n.h"

#include "CustomServerList.h"
#include "JoinByIPScreen.h"
#include "AddServerScreen.h"

JoinGameScreen::JoinGameScreen()
:	bJoin(  2, I18n::get("selectServer.select")),
	bDirect(3, I18n::get("selectServer.direct")),
	bAdd(   4, I18n::get("selectServer.add")),
	bEdit(  5, I18n::get("selectServer.edit")),
	bDelete(6, I18n::get("selectServer.delete")),
	bRefresh(7, I18n::get("selectServer.refresh")),
	bCancel(8, I18n::get("gui.cancel")),
	gamesList(NULL)
{
	bJoin.active = false;
	bEdit.active = false;
	bDelete.active = false;
	//gamesList->yInertia = 0.5f;
}

JoinGameScreen::~JoinGameScreen()
{
	delete gamesList;
}

void JoinGameScreen::buttonClicked(Button* button)
{
	if (button->id == bJoin.id)
	{
		if (isIndexValid(gamesList->selectedItem))
		{
			PingedCompatibleServer selectedServer = gamesList->copiedServerList[gamesList->selectedItem];
			minecraft->joinMultiplayer(selectedServer);
			{
				bJoin.active = false;
				bCancel.active = false;
				minecraft->setScreen(new ProgressScreen());
			}
		}
	}
	if (button->id == bCancel.id)
	{
		minecraft->cancelLocateMultiplayer();
		minecraft->screenChooser.setScreen(SCREEN_STARTMENU);
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
		if (isIndexValid(gamesList->selectedItem) && gamesList->selectedItem < (int)CustomServerList::servers.size())
		{
			minecraft->cancelLocateMultiplayer();
			minecraft->setScreen(new AddServerScreen(gamesList->selectedItem));
		}
	}
	if (button->id == bDelete.id)
	{
		if (isIndexValid(gamesList->selectedItem) && gamesList->selectedItem < CustomServerList::servers.size())
		{
			CustomServerList::servers.erase(CustomServerList::servers.begin() + gamesList->selectedItem);
			CustomServerList::save(minecraft);
			gamesList->selectedItem = -1;
		}
	}
	if (button->id == bRefresh.id)
	{
		minecraft->raknetInstance->clearServerList();
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
	return gamesList && index >= 0 && index < gamesList->getNumberOfItems();
}

void JoinGameScreen::tick()
{
	const ServerList& orgServerList = minecraft->raknetInstance->getServerList();
	ServerList serverList;
	for (unsigned int i = 0; i < CustomServerList::servers.size(); ++i)
		serverList.push_back(CustomServerList::servers[i]);

	for (unsigned int i = 0; i < orgServerList.size(); ++i)
		if (orgServerList[i].name.GetLength() > 0)
			serverList.push_back(orgServerList[i]);

	if (serverList.size() != gamesList->copiedServerList.size())
	{
		// copy the currently selected item
		PingedCompatibleServer selectedServer;
		bool hasSelection = false;
		if (isIndexValid(gamesList->selectedItem))
		{
			selectedServer = gamesList->copiedServerList[gamesList->selectedItem];
			hasSelection = true;
		}

		gamesList->copiedServerList = serverList;
		gamesList->selectItem(-1, false);

		// re-select previous item if it still exists
		if (hasSelection)
		{
			for (unsigned int i = 0; i < gamesList->copiedServerList.size(); i++)
			{
				if (gamesList->copiedServerList[i].address == selectedServer.address)
				{
					gamesList->selectItem(i, false);
					break;
				}
			}
		}
	} else {
		for (int i = (int)gamesList->copiedServerList.size()-1; i >= 0 ; --i) {
			for (int j = 0; j < (int) serverList.size(); ++j)
				if (serverList[j].address == gamesList->copiedServerList[i].address)
					gamesList->copiedServerList[i].name = serverList[j].name;
		}
	}

	bJoin.active = isIndexValid(gamesList->selectedItem);
	bEdit.active = isIndexValid(gamesList->selectedItem) && gamesList->selectedItem < CustomServerList::servers.size();
	bDelete.active = bEdit.active;
}

void JoinGameScreen::init()
{
	buttons.push_back(&bJoin);
	buttons.push_back(&bDirect);
	buttons.push_back(&bAdd);
	buttons.push_back(&bEdit);
	buttons.push_back(&bDelete);
	buttons.push_back(&bRefresh);
	buttons.push_back(&bCancel);

	CustomServerList::load(minecraft);
	minecraft->raknetInstance->clearServerList();
	gamesList = new AvailableGamesList(minecraft, width, height);

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
	int yBase = height - 52;
	int yBottom = height - 28;

	int btnWidth3 = 100;
	int btnWidth4 = 74;

	// Top row (Join, Direct, Add)
	bJoin.y = yBase; bJoin.width = btnWidth3; bJoin.x = width / 2 - 154;
	bDirect.y = yBase; bDirect.width = btnWidth3; bDirect.x = width / 2 - 50;
	bAdd.y = yBase; bAdd.width = btnWidth3; bAdd.x = width / 2 + 54;

	// Bottom row (Edit, Delete, Refresh, Cancel)
	bEdit.y = yBottom; bEdit.width = btnWidth4; bEdit.x = width / 2 - 154;
	bDelete.y = yBottom; bDelete.width = btnWidth4; bDelete.x = width / 2 - 76;
	bRefresh.y = yBottom; bRefresh.width = btnWidth4; bRefresh.x = width / 2 + 2;
	bCancel.y = yBottom; bCancel.width = btnWidth4; bCancel.x = width / 2 + 80;
}

void JoinGameScreen::render( int xm, int ym, float a )
{
	renderBackground();
	gamesList->render(xm, ym, a);
	Screen::render(xm, ym, a);

	drawCenteredString(minecraft->font, I18n::get("selectServer.title"), width / 2, 8, 0xffffffff);
}

bool JoinGameScreen::isInGameScreen() { return false; }
