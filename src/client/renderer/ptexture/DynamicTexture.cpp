#include "DynamicTexture.h"

#include <cstring>
#include "../Textures.h"
#include "../TextureData.h"
#include "../../../world/level/tile/Tile.h"
#include "../../../util/Mth.h"
#include "../../../AppPlatform.h"

DynamicTexture::DynamicTexture(int tex_)
:   tex(tex_),
	replicate(1)
{
	memset(pixels, 0, 16*16*4);
}

void DynamicTexture::bindTexture(Textures* tex) {
	tex->loadAndBindTexture("terrain.png");
}

WaterTexture::WaterTexture()
:   super(Tile::water->tex),
	_tick(0),
	_frame(0)
{
	current = new float[16*16];
	next = new float[16*16];
	heat = new float[16*16];
	heata = new float[16*16];

	for (int i = 0; i < 256; ++i) {
		current[i] = 0;
		next[i] = 0;
		heat[i] = 0;
		heata[i] = 0;
	}
}

WaterTexture::~WaterTexture() {
	delete[] current;
	delete[] next;
	delete[] heat;
	delete[] heata;
}

void WaterTexture::tick()
{
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 16; y++) {
			float pow = 0;
			for (int xx = x - 1; xx <= x + 1; xx++) {
				int xi = (xx) & 15;
				int yi = (y) & 15;
				pow += current[xi + yi * 16];
			}
			next[x + y * 16] = pow / 3.3f + heat[x + y * 16] * 0.8f;
		}

	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 16; y++) {
			heat[x + y * 16] += heata[x + y * 16] * 0.05f;

			if (heat[x + y * 16] < 0) heat[x + y * 16] = 0;
			heata[x + y * 16] -= 0.1f;
			if (Mth::random() < 0.05f) {
				heata[x + y * 16] = 0.5f;
			}
		}

	float* tmp = next;
	next = current;
	current = tmp;

	for (int i = 0; i < 256; i++) {
		float pow = current[i];
		if (pow > 1) pow = 1;
		if (pow < 0) pow = 0;

		float pp = pow * pow;

		int r = (int) (32 + pp * 32);
		int g = (int) (50 + pp * 64);
		int b = (int) (255);
		int a = (int) (146 + pp * 50);

		pixels[i * 4 + 0] = r;
		pixels[i * 4 + 1] = g;
		pixels[i * 4 + 2] = b;
		pixels[i * 4 + 3] = a;
	}
}

WaterSideTexture::WaterSideTexture()
:   super(Tile::water->tex + 1),
	_tick(0),
	_frame(0),
	_tickCount(0)
{
	replicate = 2;

	current = new float[16*16];
	next = new float[16*16];
	heat = new float[16*16];
	heata = new float[16*16];

	for (int i = 0; i < 256; ++i) {
		current[i] = 0;
		next[i] = 0;
		heat[i] = 0;
		heata[i] = 0;
	}
}

WaterSideTexture::~WaterSideTexture() {
	delete[] current;
	delete[] next;
	delete[] heat;
	delete[] heata;
}

void WaterSideTexture::tick() {
	++_tickCount;
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 16; y++) {
			float pow = 0;
			for (int xx = y - 2; xx <= y; xx++) {
				int xi = (x) & 15;
				int yi = (xx) & 15;
				pow += current[xi + yi * 16];
			}
			next[x + y * 16] = pow / 3.2f + heat[x + y * 16] * 0.8f;
		}

	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 16; y++) {
			heat[x + y * 16] += heata[x + y * 16] * 0.05f;

			if (heat[x + y * 16] < 0) heat[x + y * 16] = 0;
			heata[x + y * 16] -= 0.3f;
			if (Mth::random() < 0.2) {
				heata[x + y * 16] = 0.5f;
			}
		}
	float* tmp = next;
	next = current;
	current = tmp;

	for (int i = 0; i < 256; i++) {
		float pow = current[(i - _tickCount * 16) & 255];
		if (pow > 1) pow = 1;
		if (pow < 0) pow = 0;

		float pp = pow * pow;

		int r = (int) (32 + pp * 32);
		int g = (int) (50 + pp * 64);
		int b = (int) (255);
		int a = (int) (146 + pp * 50);

		pixels[i * 4 + 0] = r;
		pixels[i * 4 + 1] = g;
		pixels[i * 4 + 2] = b;
		pixels[i * 4 + 3] = a;
	}
}

LavaTexture::LavaTexture()
:	super(Tile::calmLava->tex),
	_frame(0),
	_frameCount(20),
	_sheetData(nullptr)
{}

LavaTexture::~LavaTexture() {
	delete[] _sheetData;
}

void LavaTexture::loadSheet(AppPlatform* platform) {
	TextureData td = platform->loadTexture("environment/lava.png", true);
	if (td.data && td.format == TEXF_UNCOMPRESSED_8888
		&& td.w == 16 && td.h == 16 * _frameCount)
	{
		const int totalBytes = 16 * 16 * _frameCount * 4;
		_sheetData = new unsigned char[totalBytes];
		memcpy(_sheetData, td.data, totalBytes);
	} else if (td.data) {
		_frameCount = td.h / 16;
		if (_frameCount < 1) _frameCount = 1;
		const int totalBytes = 16 * _frameCount * 16 * 4;
		_sheetData = new unsigned char[totalBytes];
		memcpy(_sheetData, td.data, totalBytes);
	}
	if (td.data && !td.memoryHandledExternally)
		delete[] td.data;
	if (_sheetData) {
		const int totalPixels = 16 * 16 * _frameCount;
		for (int i = 0; i < totalPixels; ++i)
			_sheetData[i * 4 + 3] = 255;
	}

	if (_sheetData)
		memcpy(pixels, _sheetData, 16 * 16 * 4);
}

void LavaTexture::tick() {
	if (!_sheetData) return;

	int cycle = (_frameCount > 1) ? (_frameCount - 1) * 2 : 1;
	int step = (_frame / 2) % cycle;
	int currentFrame = (step < _frameCount) ? step : (cycle - step);

	const int frameOffset = currentFrame * 16 * 16 * 4;
	memcpy(pixels, _sheetData + frameOffset, 16 * 16 * 4);

	_frame++;
}

LavaSideTexture::LavaSideTexture()
:	super(Tile::calmLava->tex + 1),
	_frame(0),
	_frameCount(32),
	_sheetData(nullptr)
{
	replicate = 2;
}

LavaSideTexture::~LavaSideTexture() {
	delete[] _sheetData;
}

void LavaSideTexture::loadSheet(AppPlatform* platform) {
	TextureData td = platform->loadTexture("environment/flow_lava.png", true);
	if (td.data && td.format == TEXF_UNCOMPRESSED_8888
		&& td.w == 16 && td.h == 16 * _frameCount)
	{
		const int totalBytes = 16 * 16 * _frameCount * 4;
		_sheetData = new unsigned char[totalBytes];
		memcpy(_sheetData, td.data, totalBytes);
	} else if (td.data) {
		_frameCount = td.h / 16;
		if (_frameCount < 1) _frameCount = 1;
		const int totalBytes = 16 * _frameCount * 16 * 4;
		_sheetData = new unsigned char[totalBytes];
		memcpy(_sheetData, td.data, totalBytes);
	}
	if (td.data && !td.memoryHandledExternally)
		delete[] td.data;
	if (_sheetData) {
		const int totalPixels = 16 * 16 * _frameCount;
		for (int i = 0; i < totalPixels; ++i)
			_sheetData[i * 4 + 3] = 255;
	}

	if (_sheetData)
		memcpy(pixels, _sheetData, 16 * 16 * 4);
}

void LavaSideTexture::tick() {
	if (!_sheetData) return;

	int currentFrame = (_frame / 2) % _frameCount;

	const int frameOffset = currentFrame * 16 * 16 * 4;
	memcpy(pixels, _sheetData + frameOffset, 16 * 16 * 4);

	_frame++;
}

// ──────────────────────────────────────────────────────────────────────────────
// PortalTexture – animated Nether Portal tile (environment/portal.png, 32 frames)
// ──────────────────────────────────────────────────────────────────────────────
PortalTexture::PortalTexture()
:	super(Tile::netherPortal->tex),   // writes into the terrain atlas slot of the portal
	_frame(0),
	_frameCount(32),
	_sheetData(nullptr)
{}

PortalTexture::~PortalTexture() {
	delete[] _sheetData;
}

void PortalTexture::loadSheet(AppPlatform* platform) {
	TextureData td = platform->loadTexture("environment/portal.png", true);
	if (td.data && td.format == TEXF_UNCOMPRESSED_8888
		&& td.w == 16 && td.h == 16 * _frameCount)
	{
		const int totalBytes = 16 * 16 * _frameCount * 4;
		_sheetData = new unsigned char[totalBytes];
		memcpy(_sheetData, td.data, totalBytes);
	} else if (td.data) {
		_frameCount = td.h / 16;
		if (_frameCount < 1) _frameCount = 1;
		const int totalBytes = 16 * _frameCount * 16 * 4;
		_sheetData = new unsigned char[totalBytes];
		memcpy(_sheetData, td.data, totalBytes);
	}
	if (td.data && !td.memoryHandledExternally)
		delete[] td.data;

	// Preserve the original alpha channel from the PNG (don't force alpha=255)
	if (_sheetData)
		memcpy(pixels, _sheetData, 16 * 16 * 4);
}

void PortalTexture::tick() {
	if (!_sheetData) return;

	// 1 frame per tick (no /2 divider – maximum animation speed)
	int currentFrame = _frame % _frameCount;

	const int frameOffset = currentFrame * 16 * 16 * 4;
	memcpy(pixels, _sheetData + frameOffset, 16 * 16 * 4);

	_frame++;
}
