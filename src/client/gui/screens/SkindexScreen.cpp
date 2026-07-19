#include "SkindexScreen.h"
#include "RenameSkinScreen.h"
#include "NewPackScreen.h"
#include <algorithm>
#include "../../Minecraft.h"
#include "../../Options.h"
#include "../../player/LocalPlayer.h"
#include "../../renderer/entity/EntityRenderDispatcher.h"
#include "../../renderer/Textures.h"
#include "../../model/HumanoidModel.h"
#include "../../../locale/I18n.h"
#include "../../../util/Mth.h"
#include "world/level/storage/FolderMethods.h"
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#else
#include <dirent.h>
#endif

SkindexScreen::SkindexScreen()
:	btnConfirm(0, 0, 0, 100, 24, I18n::get("gui.done")),
	btnCancel(1, 0, 0, 100, 24, I18n::get("gui.cancel")),
	btnImport(4, 0, 0, 100, 24, I18n::get("gui.import")),
	btnPrev(2, 0, 0, 30, 24, "<"),
	btnNext(3, 0, 0, 30, 24, ">"),
	btnPackPrev(5, 0, 0, 20, 20, "<"),
	btnPackNext(6, 0, 0, 20, 20, ">"),
	btnRename(7, 0, 0, 60, 20, I18n::get("gui.rename")),
	btnDelete(8, 0, 0, 60, 20, I18n::get("gui.delete")),
	btnNewPack(9, 0, 0, 80, 20, I18n::get("gui.newPack")),
	currentPackIndex(0),
	currentSkinIndex(0),
	playerRot(0.0f)
{
}

SkindexScreen::~SkindexScreen() {
}

void SkindexScreen::ensureSkinsDir() {
	createFolderIfNotExists("games");
	createFolderIfNotExists("games/com.mojang");
	createFolderIfNotExists("games/com.mojang/skins");
	createFolderIfNotExists("games/com.mojang/skins/Default");
}

void SkindexScreen::scanSkins() {
	skinPacks.clear();
	ensureSkinsDir();

	// Initialize default skins in games/com.mojang/skins/Default
#ifdef _WIN32
	CopyFileA("data/images/skins/steve.png", "games/com.mojang/skins/Default/steve.png", FALSE);
	CopyFileA("data/images/skins/cesar.png", "games/com.mojang/skins/Default/cesar.png", FALSE);
	CopyFileA("data/images/skins/cesar malo.png", "games/com.mojang/skins/Default/cesar malo.png", FALSE);
#elif defined(ANDROID)
	extern void extractAsset_JNI(const char* asset, const char* dest);
	extractAsset_JNI("images/skins/steve.png", "games/com.mojang/skins/Default/steve.png");
	extractAsset_JNI("images/skins/cesar.png", "games/com.mojang/skins/Default/cesar.png");
	extractAsset_JNI("images/skins/cesar malo.png", "games/com.mojang/skins/Default/cesar malo.png");
#else
	auto copyFile = [](const std::string& src, const std::string& dest) {
		std::ifstream source(src, std::ios::binary);
		std::ofstream destination(dest, std::ios::binary);
		destination << source.rdbuf();
	};
	copyFile("data/images/skins/steve.png", "games/com.mojang/skins/Default/steve.png");
	copyFile("data/images/skins/cesar.png", "games/com.mojang/skins/Default/cesar.png");
	copyFile("data/images/skins/cesar malo.png", "games/com.mojang/skins/Default/cesar malo.png");
#endif

#ifdef _WIN32
	WIN32_FIND_DATAA findDirData;
	HANDLE hFindDir = FindFirstFileA("games\\com.mojang\\skins\\*", &findDirData);
	if (hFindDir != INVALID_HANDLE_VALUE) {
		do {
			if (findDirData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				std::string dirName = findDirData.cFileName;
				if (dirName != "." && dirName != "..") {
					SkinPack pack;
					pack.name = dirName;
					
					std::string searchPath = "games\\com.mojang\\skins\\" + dirName + "\\*.png";
					WIN32_FIND_DATAA findFileData;
					HANDLE hFindFile = FindFirstFileA(searchPath.c_str(), &findFileData);
					if (hFindFile != INVALID_HANDLE_VALUE) {
						do {
							if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
								pack.skins.push_back("games/com.mojang/skins/" + dirName + "/" + findFileData.cFileName);
							}
						} while (FindNextFileA(hFindFile, &findFileData) != 0);
						FindClose(hFindFile);
					}
					skinPacks.push_back(pack);
				}
			}
		} while (FindNextFileA(hFindDir, &findDirData) != 0);
		FindClose(hFindDir);
	}
#else
	DIR* dir = opendir("games/com.mojang/skins");
	if (dir != NULL) {
		struct dirent* ent;
		while ((ent = readdir(dir)) != NULL) {
			std::string dirName = ent->d_name;
			if (dirName != "." && dirName != "..") {
				std::string fullDirPath = "games/com.mojang/skins/" + dirName;
				DIR* subDir = opendir(fullDirPath.c_str());
				if (subDir != NULL) {
					SkinPack pack;
					pack.name = dirName;
					struct dirent* subEnt;
					while ((subEnt = readdir(subDir)) != NULL) {
						std::string fileName = subEnt->d_name;
						if (fileName.length() > 4 && fileName.substr(fileName.length() - 4) == ".png") {
							pack.skins.push_back(fullDirPath + "/" + fileName);
						}
					}
					closedir(subDir);
					skinPacks.push_back(pack);
				}
			}
		}
		closedir(dir);
	}
#endif

	if (skinPacks.empty()) {
		SkinPack pack;
		pack.name = "Default";
		pack.skins.push_back("games/com.mojang/skins/Default/steve.png");
		skinPacks.push_back(pack);
	}
}

void SkindexScreen::init() {
	scanSkins();

	std::string currentSkin = minecraft->options.getStringValue(OPTIONS_SKIN);
	if (currentSkin == "" || currentSkin == "Default") currentSkin = "games/com.mojang/skins/Default/steve.png";

	currentPackIndex = 0;
	currentSkinIndex = 0;

	bool found = false;
	for (size_t p = 0; p < skinPacks.size(); ++p) {
		for (size_t s = 0; s < skinPacks[p].skins.size(); ++s) {
			if (skinPacks[p].skins[s] == currentSkin) {
				currentPackIndex = p;
				currentSkinIndex = s;
				found = true;
				break;
			}
		}
		if (found) break;
	}

	buttons.push_back(&btnConfirm);
	buttons.push_back(&btnCancel);
	buttons.push_back(&btnImport);
	buttons.push_back(&btnPrev);
	buttons.push_back(&btnNext);
	
	buttons.push_back(&btnPackPrev);
	buttons.push_back(&btnPackNext);
	buttons.push_back(&btnRename);
	buttons.push_back(&btnDelete);
	buttons.push_back(&btnNewPack);
}

void SkindexScreen::setupPositions() {
	btnConfirm.width = (std::max)(100, font->width(btnConfirm.msg) + 16);
	btnCancel.width = (std::max)(100, font->width(btnCancel.msg) + 16);

	int yBase = height - 30;
	
	btnCancel.x = width / 2 - btnCancel.width - 4;
	btnCancel.y = yBase;
	
	btnConfirm.x = width / 2 + 4;
	btnConfirm.y = yBase;

	btnPrev.x = width / 2 - 80;
	btnPrev.y = height / 2 - 12;

	btnNext.x = width / 2 + 80 - btnNext.width;
	btnNext.y = height / 2 - 12;

	btnImport.width = (std::max)(80, font->width(btnImport.msg) + 16);
	btnImport.x = width - btnImport.width - 4;
	btnImport.y = 4;

	btnNewPack.width = (std::max)(80, font->width(btnNewPack.msg) + 16);
	btnNewPack.x = 4;
	btnNewPack.y = 4;

	int packY = yBase - 26;
	btnPackPrev.x = width / 2 - 80;
	btnPackPrev.y = packY;
	btnPackNext.x = width / 2 + 80 - btnPackNext.width;
	btnPackNext.y = packY;

	btnRename.x = width - btnRename.width - 10;
	btnRename.y = height / 2 - 20;

	btnDelete.x = width - btnDelete.width - 10;
	btnDelete.y = height / 2 + 5;
}

void SkindexScreen::tick() {
	playerRot += 1.5f;
	if (playerRot >= 360.0f) playerRot -= 360.0f;
}

void SkindexScreen::render(int xm, int ym, float a) {
	renderDirtBackground(0);
	
	SkinPack& activePack = skinPacks[currentPackIndex];
	std::string currentSkin = activePack.skins.empty() ? "mob/char.png" : activePack.skins[currentSkinIndex];
	
	std::string displayName = currentSkin;
	size_t slashPos = displayName.find_last_of("\\/");
	if (slashPos != std::string::npos) {
		displayName = displayName.substr(slashPos + 1);
	}
	if (displayName.length() > 4 && displayName.substr(displayName.length() - 4) == ".png") {
		displayName = displayName.substr(0, displayName.length() - 4);
	}

	drawCenteredString(font, I18n::get("skindex.title"), width / 2, 10, 0xffffff);
	drawCenteredString(font, displayName, width / 2, height / 2 - 80, 0xffff00);

	std::string packText = "Pack: " + activePack.name;
	drawCenteredString(font, I18n::get("skindex.pack") + activePack.name, width / 2, btnPackPrev.y + 6, 0xffffff);

	// Controls validation
	bool isBuiltin = false;
	if (!activePack.skins.empty()) {
		std::string fname = activePack.skins[currentSkinIndex];
		size_t pos = fname.find_last_of("\\/");
		if (pos != std::string::npos) fname = fname.substr(pos + 1);
		if (fname == "steve.png" || fname == "cesar.png" || fname == "cesar malo.png" || fname == "char.png") {
			isBuiltin = true;
		}
	} else {
		isBuiltin = true;
	}
	btnRename.active = !isBuiltin;
	btnDelete.active = !isBuiltin;
	btnConfirm.active = !activePack.skins.empty();

	Screen::render(xm, ym, a);

	if (!activePack.skins.empty()) {
		std::string newTexture = currentSkin;
		
		TextureId textureId = minecraft->textures->loadTexture(newTexture, false);
		minecraft->textures->bind(textureId);

		int skinW = 64, skinH = 64;
		const TextureData* tdata = minecraft->textures->getTemporaryTextureData(textureId);
		if (tdata) {
			skinW = tdata->w;
			skinH = tdata->h;
		}

		glEnable2(GL_DEPTH_TEST);
		glPushMatrix();
		glTranslatef((float)(width / 2), (float)(height / 2 - 20), -200);
		float ss = 60.0f;
		glScalef(-ss, ss, ss);
		glRotatef(180.0f, 0, 1, 0);
		glRotatef(15.0f, 1, 0, 0);
		glRotatef(playerRot, 0, 1, 0);

		glColor4f2(1.0f, 1.0f, 1.0f, 1.0f);
		HumanoidModel model(0.0f, 0.0f, skinW, skinH);
		model.render(nullptr, 0, 0, 0, 0, 0, 0.0625f);

		glPopMatrix();
		glDisable2(GL_DEPTH_TEST);
	} else {
		drawCenteredString(font, I18n::get("skindex.noSkins"), width / 2, height / 2 - 10, 0xffaaaaaa);
	}
}

void SkindexScreen::buttonClicked(Button* button) {
	if (button->id == btnCancel.id) {
		minecraft->setScreen(nullptr);
	} else if (button->id == btnConfirm.id) {
		SkinPack& activePack = skinPacks[currentPackIndex];
		if (!activePack.skins.empty()) {
			minecraft->options.set(OPTIONS_SKIN, activePack.skins[currentSkinIndex]);
			minecraft->options.save();
			
			if (minecraft->player) {
				minecraft->player->textureName = activePack.skins[currentSkinIndex];
			}
		}
		minecraft->setScreen(nullptr);
	} else if (button->id == btnPrev.id) {
		SkinPack& activePack = skinPacks[currentPackIndex];
		if (!activePack.skins.empty()) {
			currentSkinIndex--;
			if (currentSkinIndex < 0) currentSkinIndex = activePack.skins.size() - 1;
		}
	} else if (button->id == btnNext.id) {
		SkinPack& activePack = skinPacks[currentPackIndex];
		if (!activePack.skins.empty()) {
			currentSkinIndex++;
			if (currentSkinIndex >= activePack.skins.size()) currentSkinIndex = 0;
		}
	} else if (button->id == btnPackPrev.id) {
		currentPackIndex--;
		if (currentPackIndex < 0) currentPackIndex = skinPacks.size() - 1;
		currentSkinIndex = 0;
	} else if (button->id == btnPackNext.id) {
		currentPackIndex++;
		if (currentPackIndex >= skinPacks.size()) currentPackIndex = 0;
		currentSkinIndex = 0;
	} else if (button->id == btnImport.id) {
#ifdef _WIN32
		OPENFILENAMEA ofn;
		char szFile[260] = {0};
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "PNG Images\0*.PNG\0All Files\0*.*\0";
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		
		if (GetOpenFileNameA(&ofn) == TRUE) {
			std::string src = szFile;
			std::string filename = src;
			size_t pos = filename.find_last_of("\\/");
			if (pos != std::string::npos) {
				filename = filename.substr(pos + 1);
			}
			
			std::string dest = "games\\com.mojang\\skins\\" + skinPacks[currentPackIndex].name + "\\" + filename;
			if (CopyFileA(src.c_str(), dest.c_str(), FALSE) || GetLastError() == ERROR_ALREADY_EXISTS) {
				scanSkins();
				for (size_t i = 0; i < skinPacks[currentPackIndex].skins.size(); ++i) {
					if (skinPacks[currentPackIndex].skins[i] == "games/com.mojang/skins/" + skinPacks[currentPackIndex].name + "/" + filename) {
						currentSkinIndex = i;
						break;
					}
				}
			}
		}
#elif defined(ANDROID)
		extern void pickImage_JNI();
		pickImage_JNI();
		// scanSkins will need to be reloaded later by the user opening the screen again for now.
#endif
	} else if (button->id == btnRename.id) {
		SkinPack& activePack = skinPacks[currentPackIndex];
		if (!activePack.skins.empty()) {
			minecraft->setScreen(new RenameSkinScreen(activePack.skins[currentSkinIndex]));
		}
	} else if (button->id == btnNewPack.id) {
		minecraft->setScreen(new NewPackScreen());
	} else if (button->id == btnDelete.id) {
		SkinPack& activePack = skinPacks[currentPackIndex];
		if (!activePack.skins.empty()) {
			std::string currentSkin = activePack.skins[currentSkinIndex];
			if (std::remove(currentSkin.c_str()) == 0) {
				scanSkins();
				currentSkinIndex = 0;
			}
		}
	}
}

bool SkindexScreen::handleBackEvent(bool isDown) {
	if (isDown) return true;
	minecraft->setScreen(nullptr);
	return true;
}
