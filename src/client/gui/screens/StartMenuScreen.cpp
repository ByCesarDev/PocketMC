#include "StartMenuScreen.h"
#include "UsernameScreen.h"
#include "SelectWorldScreen.h"
#include "ProgressScreen.h"
#include "JoinGameScreen.h"
#include "OptionsScreen.h"
#include "PauseScreen.h"
#include "PrerenderTilesScreen.h" // test button
#include "../components/ImageButton.h"

#include "../../../util/Mth.h"

#include "../Font.h"
#include "../components/ScrolledSelectionList.h"

#include "../../Minecraft.h"
#include "../../renderer/Tesselator.h"
#include "../../../AppPlatform.h"
#include "../../../LicenseCodes.h"
#include "SimpleChooseLevelScreen.h"
#include "../../renderer/Textures.h"
#include "../../../SharedConstants.h"
#include "../../../locale/I18n.h"

// Some kind of default settings, might be overridden in ::init
StartMenuScreen::StartMenuScreen()
:	bHost(    2, 0, 0, 160, 24, I18n::get("menu.startGame")),
	bJoin(    3, 0, 0, 160, 24, I18n::get("menu.joinGame")),
	bOptions( 4, 0, 0, 160, 24, I18n::get("menu.options")),
	bProfile( 6, 0, 0, 60, 24, I18n::get("menu.profile")),
	bSkindex(7, 0, 0, 60, 24, I18n::get("menu.skindex")),
	bQuit(    5, 0, 0, 160, 24, I18n::get("menu.quit")),
	panoramaTicks(0)
{
}

StartMenuScreen::~StartMenuScreen()
{
}

void StartMenuScreen::init()
{
	bJoin.active = bHost.active = bOptions.active = true;

	if (minecraft->options.getStringValue(OPTIONS_USERNAME).empty()) {
		return; // tick() will redirect to UsernameScreen
	}

	buttons.push_back(&bHost);
	buttons.push_back(&bOptions);
	buttons.push_back(&bJoin);
	buttons.push_back(&bQuit);
	buttons.push_back(&bProfile);
	buttons.push_back(&bSkindex);

	tabButtons.push_back(&bHost);
	tabButtons.push_back(&bOptions);
	tabButtons.push_back(&bJoin);
	tabButtons.push_back(&bQuit);
	tabButtons.push_back(&bProfile);
	tabButtons.push_back(&bSkindex);

	copyright = "\xffMojang AB";//. Do not distribute!";

	// always show base version string, suffix was previously added for Android builds
	std::string versionString = Common::getGameVersionString();

	std::string _username = minecraft->options.getStringValue(OPTIONS_USERNAME);
	if (_username.empty()) _username = "unknown";

	username = "Username: " + _username;

	#ifdef DEMO_MODE
	#ifdef __APPLE__
		version = versionString + " (Lite)";
	#else
		version = versionString + " (Demo)";
	#endif
	#else
		#ifdef RPI
			version = "v0.1.1 alpha";//(MCPE " + versionString + " compatible)";
		#else
			version = versionString;
		#endif
	#endif
}

void StartMenuScreen::setupPositions() {
	// Four center buttons stacked vertically
	int totalH = 4 * 24 + 3 * 4; // 4 buttons + 3 gaps
	int yBase = (height - totalH) / 2;

	bHost.y = yBase;
	bOptions.y = bHost.y + 24 + 4;
	bJoin.y = bOptions.y + 24 + 4;
	bQuit.y = bJoin.y + 24 + 4;

	// Center buttons
	bHost.x = (width - bHost.width) / 2;
	bOptions.x = (width - bOptions.width) / 2;
	bJoin.x = (width - bJoin.width) / 2;
	bQuit.x = (width - bQuit.width) / 2;

	bProfile.x = 2;
	bProfile.y = height - 24 - 20;

	bSkindex.x = width - bSkindex.width - 2;
	bSkindex.y = height - 24 - 20;
}

void StartMenuScreen::tick() {
	panoramaTicks++;
}

void StartMenuScreen::buttonClicked(Button* button) {

	if (button->id == bHost.id)
	{
        #if defined(DEMO_MODE) || defined(APPLE_DEMO_PROMOTION)
			minecraft->setScreen( new SimpleChooseLevelScreen("_DemoLevel") );
		#else
			minecraft->screenChooser.setScreen(SCREEN_SELECTWORLD);
		#endif
	}
	if (button->id == bJoin.id)
	{
		minecraft->locateMultiplayer();
		minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
	}
	if (button->id == bOptions.id)
	{
		minecraft->setScreen(new OptionsScreen());
	}
	if (button->id == bProfile.id)
	{
		minecraft->setScreen(new UsernameScreen());
	}
	if (button->id == bSkindex.id)
	{
		// TODO: Vestidor screen
	}
	if (button->id == bQuit.id)
	{
		minecraft->quit();
	}
}

bool StartMenuScreen::isInGameScreen() { return false; }

void StartMenuScreen::render( int xm, int ym, float a )
{
	renderPanorama(panoramaTicks, a);

#if defined(RPI)
	TextureId id = minecraft->textures->loadTexture("gui/pi_title.png");
#else
	TextureId id = minecraft->textures->loadTexture("gui/title.png");
#endif
	const TextureData* data = minecraft->textures->getTemporaryTextureData(id);

	if (data) {
		minecraft->textures->bind(id);

		const float x = (float)width / 2;
		const float y = height/16;
		const float wh = Mth::Min((float)width/2.0f, (float)data->w / 2);
		const float scale = 2.0f * wh / (float)data->w;
		const float h = scale * (float)data->h;

		// Render title text
		Tesselator& t = Tesselator::instance;
		glColor4f2(1, 1, 1, 1);
		t.begin();
		t.vertexUV(x-wh, y+h, blitOffset, 0, 1);
		t.vertexUV(x+wh, y+h, blitOffset, 1, 1);
		t.vertexUV(x+wh, y+0, blitOffset, 1, 0);
		t.vertexUV(x-wh, y+0, blitOffset, 0, 0);
		t.draw();
	}

#if defined(RPI)
	if (Textures::isTextureIdValid(minecraft->textures->loadAndBindTexture("gui/logo/raknet_high_72.png")))
		blit(0, height - 12, 0, 0, 43, 12, 256, 72+72);
#endif

	drawString(font, version, width - font->width(version) - 2, height - 10, 0xffcccccc);
	drawString(font, copyright, 2, height - 10, 0xffffff);
	
	Screen::render(xm, ym, a);
}

bool StartMenuScreen::handleBackEvent( bool isDown ) {
	minecraft->quit();
	return true;
}
