#include "OptionsScreen.h"

#include "StartMenuScreen.h"
#include "UsernameScreen.h"
#include "DialogDefinitions.h"
#include "../../Minecraft.h"
#include "../../../AppPlatform.h"
#include "CreditsScreen.h"
#include "../../../locale/I18n.h"

#include "../components/ImageButton.h"
#include "../components/OptionsGroup.h"
#include "platform/input/Keyboard.h"
#include "../../sound/SoundEngine.h"

OptionsScreen::OptionsScreen()
	: btnClose(NULL),
	bHeader(NULL),
	btnCredits(NULL),
	selectedCategory(0) {
}

OptionsScreen::~OptionsScreen() {
	if (btnClose != NULL) {
		delete btnClose;
		btnClose = NULL;
	}

	if (bHeader != NULL) {
		delete bHeader;
		bHeader = NULL;
	}

	if (btnCredits != NULL) {
		delete btnCredits;
		btnCredits = NULL;
	}

	for (std::vector<Touch::TButton*>::iterator it = categoryButtons.begin(); it != categoryButtons.end(); ++it) {
		if (*it != NULL) {
			delete* it;
			*it = NULL;
		}
	}

	for (std::vector<OptionsGroup*>::iterator it = optionPanes.begin(); it != optionPanes.end(); ++it) {
		if (*it != NULL) {
			delete* it;
			*it = NULL;
		}
	}

	categoryButtons.clear();
}

void OptionsScreen::init() {
	bHeader = new Touch::THeader(0, I18n::get("options.title"));

	btnClose = new ImageButton(1, "");

	ImageDef def;
	def.name = "gui/touchgui.png";
	def.width = 34;
	def.height = 26;

	def.setSrc(IntRectangle(150, 0, (int)def.width, (int)def.height));
	btnClose->setImageDef(def, true);

	categoryButtons.push_back(new Touch::TButton(2, I18n::get("options.tab.general")));
	categoryButtons.push_back(new Touch::TButton(3, I18n::get("options.tab.game")));
	categoryButtons.push_back(new Touch::TButton(4, I18n::get("options.tab.controls")));
	categoryButtons.push_back(new Touch::TButton(5, I18n::get("options.tab.graphics")));
	categoryButtons.push_back(new Touch::TButton(6, I18n::get("options.tab.tweaks")));
	categoryButtons.push_back(new Touch::TButton(7, I18n::get("options.tab.language")));

	btnCredits = new Touch::TButton(11, I18n::get("options.credits"));

	buttons.push_back(bHeader);
	buttons.push_back(btnClose);
	buttons.push_back(btnCredits);

	for (std::vector<Touch::TButton*>::iterator it = categoryButtons.begin(); it != categoryButtons.end(); ++it) {
		buttons.push_back(*it);
		tabButtons.push_back(*it);
	}

	generateOptionScreens();
	// start with first category selected
	selectCategory(0);
}

void OptionsScreen::setupPositions() {
	int buttonHeight = btnClose->height;

	btnClose->x = width - btnClose->width;
	btnClose->y = 0;

	int offsetNum = 1;

	for (std::vector<Touch::TButton*>::iterator it = categoryButtons.begin(); it != categoryButtons.end(); ++it) {

		(*it)->x = 0;
		(*it)->y = offsetNum * buttonHeight;
		(*it)->selected = false;

		offsetNum++;
	}

	bHeader->x = 0;
	bHeader->y = 0;
	bHeader->width = width - btnClose->width;
	bHeader->height = btnClose->height;

	// Credits button (bottom-right)
	if (btnCredits != NULL) {
		btnCredits->x = width - btnCredits->width;
		btnCredits->y = height - btnCredits->height;
	}

	for (std::vector<OptionsGroup*>::iterator it = optionPanes.begin(); it != optionPanes.end(); ++it) {

		if (categoryButtons.size() > 0 && categoryButtons[0] != NULL) {

			(*it)->x = categoryButtons[0]->width;
			(*it)->y = bHeader->height;
			(*it)->width = width - categoryButtons[0]->width;

			// make the options pane take the available vertical space and allow scrolling
			int availableHeight = height - bHeader->height;
			if (btnCredits != NULL) availableHeight -= btnCredits->height;
			availableHeight -= 6; // small padding
			(*it)->height = availableHeight;

			(*it)->setupPositions();
		}
	}

	// don't override user selection on resize
}


void OptionsScreen::render(int xm, int ym, float a) {
	renderBackground();

	int xmm = xm * width / minecraft->width;
	int ymm = ym * height / minecraft->height - 1;

	if (currentOptionsGroup != NULL)
		currentOptionsGroup->render(minecraft, xmm, ymm);

	super::render(xm, ym, a);
}

void OptionsScreen::removed() {
}

void OptionsScreen::buttonClicked(Button* button) {
	if (button == btnClose) {
		minecraft->options.save();
		if (minecraft->screen != NULL) {
			minecraft->setScreen(NULL);
		} else {
			minecraft->screenChooser.setScreen(SCREEN_STARTMENU);
		}
	}
	else if (button->id > 1 && button->id < 8) {
		int categoryButton = button->id - categoryButtons[0]->id;
		selectCategory(categoryButton);
	}
	else if (button == btnCredits) {
		minecraft->setScreen(new CreditsScreen());
	}
	// Handle language selection buttons
	else if (button->id >= 100 && button->id < 102) {
		int langIndex = button->id - 100;
		minecraft->options.set(OPTIONS_LANGUAGE, langIndex);
		// Update button selection states
		for(int i = 0; i < languageButtons.size(); i++) {
			languageButtons[i]->selected = (i == langIndex);
		}
	}
	// Handle apply button
	else if (button == btnApplyLanguage) {
		minecraft->options.save();
		int langIndex = minecraft->options.getIntValue(OPTIONS_LANGUAGE);
		const char* languages[] = {"en_US", "es_ES"};
		if(langIndex >= 0 && langIndex < 2) {
			I18n::loadLanguage(minecraft->platform(), languages[langIndex]);
		}
		// Update language button labels with new language
		const char* langKeys[] = {"options.language.0", "options.language.1"};
		for(int i = 0; i < languageButtons.size(); i++) {
			languageButtons[i]->msg = I18n::get(langKeys[i]);
		}
		btnApplyLanguage->msg = I18n::get("options.applyLanguage");

		// Refresh category tab labels
		const char* categoryKeys[] = {"options.tab.general", "options.tab.game", "options.tab.controls", "options.tab.graphics", "options.tab.tweaks", "options.tab.language"};
		const char* categoryFallbacks[] = {"General", "Game", "Controls", "Graphics", "Tweaks", "Language"};
		for(int i = 0; i < (int)categoryButtons.size() && i < 6; i++) {
			std::string label = I18n::get(categoryKeys[i]);
			// If key not found (ends with '<'), use the hardcoded fallback
			if (!label.empty() && label.back() == '<')
				label = categoryFallbacks[i];
			categoryButtons[i]->msg = label;
		}

		// Refresh option pane headers
		const char* groupKeys[] = {"options.group.general", "options.group.game", "options.group.controls", "options.group.graphics", "options.group.tweaks", "options.group.language"};
		for(int i = 0; i < (int)optionPanes.size() && i < 6; i++) {
			std::string label = I18n::get(groupKeys[i]);
			if (!label.empty() && label.back() == '<')
				label = categoryFallbacks[i];
			optionPanes[i]->setTitle(label);
		}
	}
}

void OptionsScreen::selectCategory(int index) {
	int currentIndex = 0;

	for (std::vector<Touch::TButton*>::iterator it = categoryButtons.begin(); it != categoryButtons.end(); ++it) {

		if (index == currentIndex)
			(*it)->selected = true;
		else
			(*it)->selected = false;

		currentIndex++;
	}

	if (index < (int)optionPanes.size())
		currentOptionsGroup = optionPanes[index];

	selectedCategory = index;
}

void OptionsScreen::generateOptionScreens() {
	// how the fuck it works

	optionPanes.push_back(new OptionsGroup("options.group.general"));
	optionPanes.push_back(new OptionsGroup("options.group.game"));
	optionPanes.push_back(new OptionsGroup("options.group.controls"));
	optionPanes.push_back(new OptionsGroup("options.group.graphics"));
	optionPanes.push_back(new OptionsGroup("options.group.tweaks"));
	optionPanes.push_back(new OptionsGroup("options.group.language"));

	// General Pane
	optionPanes[0]->addOptionItem(OPTIONS_USERNAME, minecraft)
		.addOptionItem(OPTIONS_SENSITIVITY, minecraft);

	// Game Pane
	optionPanes[1]->addOptionItem(OPTIONS_DIFFICULTY, minecraft)
		.addOptionItem(OPTIONS_SERVER_VISIBLE, minecraft)
		.addOptionItem(OPTIONS_THIRD_PERSON_VIEW, minecraft)
		.addOptionItem(OPTIONS_GUI_SCALE, minecraft)
		.addOptionItem(OPTIONS_SENSITIVITY, minecraft)
		.addOptionItem(OPTIONS_MUSIC_VOLUME, minecraft)
		.addOptionItem(OPTIONS_SOUND_VOLUME, minecraft)
		.addOptionItem(OPTIONS_SMOOTH_CAMERA, minecraft)
		.addOptionItem(OPTIONS_DESTROY_VIBRATION, minecraft)
		.addOptionItem(OPTIONS_IS_LEFT_HANDED, minecraft);

	// // Controls Pane
	optionPanes[2]->addOptionItem(OPTIONS_INVERT_Y_MOUSE, minecraft)
		.addOptionItem(OPTIONS_USE_TOUCHSCREEN, minecraft)
		.addOptionItem(OPTIONS_AUTOJUMP, minecraft);

	for (int i = OPTIONS_KEY_FORWARD; i <= OPTIONS_KEY_USE; i++) {
		optionPanes[2]->addOptionItem((OptionId)i, minecraft);
	}

	// // Graphics Pane
	optionPanes[3]->addOptionItem(OPTIONS_FANCY_GRAPHICS, minecraft)
		.addOptionItem(OPTIONS_LIMIT_FRAMERATE, minecraft)
		.addOptionItem(OPTIONS_VSYNC, minecraft)
		.addOptionItem(OPTIONS_RENDER_DEBUG, minecraft)
		.addOptionItem(OPTIONS_ANAGLYPH_3D, minecraft)
		.addOptionItem(OPTIONS_VIEW_BOBBING, minecraft)
		.addOptionItem(OPTIONS_AMBIENT_OCCLUSION, minecraft)
		.addOptionItem(OPTIONS_SMOOTH_LIGHTNING, minecraft)
		.addOptionItem(OPTIONS_FOV, minecraft)
		.addOptionItem(OPTIONS_BRIGHTNESS, minecraft);
	
	optionPanes[4]->addOptionItem(OPTIONS_ALLOW_SPRINT, minecraft)
		.addOptionItem(OPTIONS_BAR_ON_TOP, minecraft)
		.addOptionItem(OPTIONS_RPI_CURSOR, minecraft);

	// Language Pane - Add language selection buttons manually
	int langIndex = minecraft->options.getIntValue(OPTIONS_LANGUAGE);
	const char* langKeys[] = {"options.language.0", "options.language.1"};

	for(int i = 0; i < 2; i++) {
		Button* langBtn = new Button(100 + i, I18n::get(langKeys[i]));
		langBtn->selected = (i == langIndex);
		languageButtons.push_back(langBtn);
		optionPanes[5]->addChild(langBtn);
	}

	// Add apply button
	btnApplyLanguage = new Button(200, I18n::get("options.applyLanguage"));
	optionPanes[5]->addChild(btnApplyLanguage);
	optionPanes[5]->setupPositions();
}

void OptionsScreen::mouseClicked(int x, int y, int buttonNum) {
	if (currentOptionsGroup != NULL)
		currentOptionsGroup->mouseClicked(minecraft, x, y, buttonNum);

	if (selectedCategory == 5) {
		int translatedY = y + optionPanes[5]->getScrollOffset();
		for(int i = 0; i < languageButtons.size(); i++) {
			if (languageButtons[i]->clicked(minecraft, x, translatedY)) {
				minecraft->soundEngine->playUI("random.click", 1.0f, 1.0f);
				buttonClicked(languageButtons[i]);
				return;
			}
		}
		if (btnApplyLanguage && btnApplyLanguage->clicked(minecraft, x, translatedY)) {
			minecraft->soundEngine->playUI("random.click", 1.0f, 1.0f);
			buttonClicked(btnApplyLanguage);
			return;
		}
	}

	super::mouseClicked(x, y, buttonNum);
}

void OptionsScreen::mouseWheel(int dx, int dy, int xm, int ym) {
    if (currentOptionsGroup != NULL)
        currentOptionsGroup->mouseWheel(dx, dy, xm, ym);
    super::mouseWheel(dx, dy, xm, ym);
}

void OptionsScreen::mouseReleased(int x, int y, int buttonNum) {
	if (currentOptionsGroup != NULL)
		currentOptionsGroup->mouseReleased(minecraft, x, y, buttonNum);

	super::mouseReleased(x, y, buttonNum);
}

void OptionsScreen::keyPressed(int eventKey) {
	if (currentOptionsGroup != NULL)
		currentOptionsGroup->keyPressed(minecraft, eventKey);
	if (eventKey == Keyboard::KEY_ESCAPE) 
		minecraft->options.save();
	
	super::keyPressed(eventKey);
}

void OptionsScreen::charPressed(char inputChar) {
	if (currentOptionsGroup != NULL)
		currentOptionsGroup->charPressed(minecraft, inputChar);

	super::keyPressed(inputChar);
}

void OptionsScreen::tick() {

	if (currentOptionsGroup != NULL)
		currentOptionsGroup->tick(minecraft);

	super::tick();
}