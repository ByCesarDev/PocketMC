#include "TouchStartMenuScreen.h"
#include "../ProgressScreen.h"
#include "../OptionsScreen.h"
#include "../PauseScreen.h"
#include "../UsernameScreen.h"

#include "../../Font.h"
#include "../../components/GuiElement.h"

#include "../../../Minecraft.h"
#include "../../../renderer/Tesselator.h"
#include "../../../renderer/Textures.h"
#include "../../../renderer/TextureData.h"
#include "../../../../SharedConstants.h"
#include "../../../../AppPlatform.h"
#include "../../../../LicenseCodes.h"
#include "../../../../util/Mth.h"

#include "../DialogDefinitions.h"
#include "../SimpleChooseLevelScreen.h"
#include "../../../../locale/I18n.h"

namespace Touch {

//
// Start menu screen implementation
//

StartMenuScreen::StartMenuScreen()
:	bHost(    2, 0, 0, 160, 24, I18n::get("menu.startGame")),
	bOptions( 4, 0, 0, 160, 24, I18n::get("menu.options")),
	bJoin(    3, 0, 0, 160, 24, I18n::get("menu.joinGame")),
	bProfile( 6, 0, 0, 60,  24, I18n::get("menu.profile")),
	bSkindex( 7, 0, 0, 60,  24, I18n::get("menu.skindex")),
	bQuit(    5, 0, 0, 160, 24, I18n::get("menu.quit")),
	panoramaTicks(0)
{
}

StartMenuScreen::~StartMenuScreen()
{
}

void StartMenuScreen::init()
{
	bHost.active = bOptions.active = bJoin.active = true;

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

	copyright = "\xffMojang AB";

	std::string versionString = Common::getGameVersionString();

	std::string _username = minecraft->options.getStringValue(OPTIONS_USERNAME);
	if (_username.empty()) _username = "unknown";

	username = _username;

	#ifdef DEMO_MODE
        #ifdef __APPLE__
            version = versionString + " (Lite)";
        #else
            version = versionString + " (Demo)";
        #endif
	#else
		version = versionString;
	#endif

    #ifdef APPLE_DEMO_PROMOTION
        version = versionString + " (Demo)";
    #endif
}

void StartMenuScreen::setupPositions() {
	// Four center buttons stacked vertically
	int totalH = 4 * 24 + 3 * 4; // 4 buttons + 3 gaps
	int yBase = (height - totalH) / 2;

	bHost.x    = (width - bHost.width)    / 2;
	bHost.y    = yBase;

	bOptions.x = (width - bOptions.width) / 2;
	bOptions.y = yBase + 24 + 4;

	bJoin.x    = (width - bJoin.width)    / 2;
	bJoin.y    = yBase + 2 * (24 + 4);

	bQuit.x    = (width - bQuit.width)    / 2;
	bQuit.y    = yBase + 3 * (24 + 4);

	// Bottom-left: Profile
	bProfile.x = 2;
	bProfile.y = height - 24 - 20;

	// Bottom-right: Dressing Room
	bSkindex.x = width - bSkindex.width - 2;
	bSkindex.y = height - 24 - 20;
}

void StartMenuScreen::buttonClicked(::Button* button) {

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
        #ifdef APPLE_DEMO_PROMOTION
            minecraft->platform()->createUserInput(DialogDefinitions::DIALOG_DEMO_FEATURE_DISABLED);
        #else
            minecraft->locateMultiplayer();
            minecraft->screenChooser.setScreen(SCREEN_JOINGAME);
        #endif
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
		// TODO: Vestidor/Skindex screen
	}
	if (button->id == bQuit.id)
	{
		minecraft->quit();
	}
}

bool StartMenuScreen::isInGameScreen() { return false; }

void StartMenuScreen::tick() {
	panoramaTicks++;
}

void StartMenuScreen::render( int xm, int ym, float a )
{
	renderPanorama(panoramaTicks, a);

    glEnable2(GL_BLEND);
	glBlendFunc2(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if defined(RPI)
	TextureId id = minecraft->textures->loadTexture("gui/pi_title.png");
#else
	TextureId id = minecraft->textures->loadTexture("gui/title.png");
#endif
	const TextureData* data = minecraft->textures->getTemporaryTextureData(id);

	if (data) {
		minecraft->textures->bind(id);

		const float x = (float)width / 2;
		const float y = height / 8.0f;
		const float wh = Mth::Min((float)width / 2.0f, (float)data->w / 2);
		const float scale = 2.0f * wh / (float)data->w;
		const float h = scale * (float)data->h;

		Tesselator& t = Tesselator::instance;
		glColor4f2(1, 1, 1, 1);
		t.begin();
			t.vertexUV(x-wh, y+h, blitOffset, 0, 1);
			t.vertexUV(x+wh, y+h, blitOffset, 1, 1);
			t.vertexUV(x+wh, y+0, blitOffset, 1, 0);
			t.vertexUV(x-wh, y+0, blitOffset, 0, 0);
		t.draw();
	}

	// version bottom-right, copyright bottom-left
	drawString(font, version,   width - font->width(version) - 2,   height - 10, 0xffcccccc);
	drawString(font, copyright, 2, height - 10, 0xffffff);

	Screen::render(xm, ym, a);
    glDisable2(GL_BLEND);
}

bool StartMenuScreen::handleBackEvent( bool isDown ) {
	minecraft->quit();
	return true;
}

void StartMenuScreen::mouseClicked(int x, int y, int buttonNum) {
	Screen::mouseClicked(x, y, buttonNum);
}

} // namespace Touch
