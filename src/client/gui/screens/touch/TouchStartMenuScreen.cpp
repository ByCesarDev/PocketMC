#include "TouchStartMenuScreen.h"
#include <algorithm>
#include "../ProgressScreen.h"
#include "../OptionsScreen.h"
#include "../PauseScreen.h"
#include "../UsernameScreen.h"
#include "../SkindexScreen.h"

#include "../../Font.h"
#include "../../components/GuiElement.h"

#include "../../../Minecraft.h"
#include "../../../renderer/Tesselator.h"
#include "../../../renderer/Textures.h"
#include "../../../renderer/TextureData.h"
#include "../../../model/HumanoidModel.h"
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
	bHost.width = (std::max)(160, font->width(bHost.msg) + 16);
	bOptions.width = (std::max)(160, font->width(bOptions.msg) + 16);
	bJoin.width = (std::max)(160, font->width(bJoin.msg) + 16);
	bQuit.width = (std::max)(160, font->width(bQuit.msg) + 16);
	
	bProfile.width = (std::max)(60, font->width(bProfile.msg) + 16);
	bSkindex.width = (std::max)(60, font->width(bSkindex.msg) + 16);

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
		minecraft->setScreen(new SkindexScreen());
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

		const float maxW = 274.0f;
		const float scale = Mth::Min((float)width * 0.85f, maxW) / maxW;
		const float w = maxW * scale;
		const float h = w * ((float)data->h / (float)data->w);
		
		const float x = (float)width / 2;
		const float y = height / 16;

		// Render title text
		Tesselator& t = Tesselator::instance;
		glColor4f2(1, 1, 1, 1);
		t.begin();
		t.vertexUV(x - w/2, y + h, blitOffset, 0, 1);
		t.vertexUV(x + w/2, y + h, blitOffset, 1, 1);
		t.vertexUV(x + w/2, y, blitOffset, 1, 0);
		t.vertexUV(x - w/2, y, blitOffset, 0, 0);
		t.draw();
	}

	// version bottom-right, copyright bottom-left
	drawString(font, version,   width - font->width(version) - 2,   height - 10, 0xffcccccc);
	drawString(font, copyright, 2, height - 10, 0xffffff);

	// Draw skin preview above bSkindex button
	{
		std::string skinPath = minecraft->options.getStringValue(OPTIONS_SKIN);
		if (skinPath.empty() || skinPath == "Default") skinPath = "mob/char.png";

		TextureId skinTexId = minecraft->textures->loadTexture(skinPath);

		int skinW = 64, skinH = 64;
		const TextureData* tdata = minecraft->textures->getTemporaryTextureData(skinTexId);
		if (tdata) { skinW = tdata->w; skinH = tdata->h; }

		int centerX = bSkindex.x + bSkindex.width / 2;
		int centerY = bSkindex.y - 45;

		// Username label above the skin
		std::string uname = minecraft->options.getStringValue(OPTIONS_USERNAME);
		if (!uname.empty()) {
			int textW = font->width(uname);
			fill(centerX - textW / 2 - 3, centerY - 35 - 2, centerX + textW / 2 + 3, centerY - 35 + 10, 0x50000000);
			drawCenteredString(font, uname, centerX, centerY - 35, 0xffffff);
		}

		minecraft->textures->bind(skinTexId);

		glEnable2(GL_DEPTH_TEST);
		glPushMatrix();
		glTranslatef((float)centerX, (float)centerY, -100);
		float ss = 25.0f; // Slightly larger
		glScalef(-ss, ss, ss);
		glRotatef(180.0f, 0, 1, 0);
		glRotatef(10.0f, 1, 0, 0); // Pitch
		glRotatef(20.0f, 0, 1, 0); // Yaw for 3D effect
		float diffX = (float)(centerX - xm);
		float diffY = (float)((centerY - 35) - ym);
		float headYaw = diffX * 0.5f;
		float headPitch = -diffY * 0.5f;
		if (headYaw > 45.0f) headYaw = 45.0f;
		if (headYaw < -45.0f) headYaw = -45.0f;
		if (headPitch > 45.0f) headPitch = 45.0f;
		if (headPitch < -45.0f) headPitch = -45.0f;

		glColor4f2(1.0f, 1.0f, 1.0f, 1.0f);
		HumanoidModel skinModel(0.0f, 0.0f, skinW, skinH);
		skinModel.render(nullptr, 0, 0, 0, headYaw, headPitch, 0.0625f);
		glPopMatrix();
		glDisable2(GL_DEPTH_TEST);
	}

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
