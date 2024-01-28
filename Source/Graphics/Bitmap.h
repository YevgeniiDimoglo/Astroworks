#pragma once

#include <string.h>
#include <vector>

#include <glm/glm.hpp>

enum class BitmapType
{
	BitmapType2D,
	BitmapTypeCube
};

enum class BitmapFormat
{
	BitmapFormatUnsignedByte,
	BitmapFormatFloat,
};

struct Bitmap
{
	Bitmap() = default;
	Bitmap(int w, int h, int comp, BitmapFormat fmt);
	Bitmap(int w, int h, int d, int comp, BitmapFormat fmt);
	Bitmap(int w, int h, int comp, BitmapFormat fmt, const void* ptr);

	int w = 0;
	int h = 0;
	int d = 1;
	int comp = 3;
	BitmapFormat fmt = BitmapFormat::BitmapFormatUnsignedByte;
	BitmapType type = BitmapType::BitmapType2D;
	std::vector<uint8_t> data;

	static int GetBytesPerComponent(BitmapFormat fmt);

	void SetPixel(int x, int y, const glm::vec4& c);
	glm::vec4 GetPixel(int x, int y) const;

private:

	using setPixel_t = void(Bitmap::*)(int, int, const glm::vec4&);
	using getPixel_t = glm::vec4(Bitmap::*)(int, int) const;
	setPixel_t SetPixelFunc = &Bitmap::SetPixelUnsignedByte;
	getPixel_t GetPixelFunc = &Bitmap::GetPixelUnsignedByte;

	void InitGetSetFuncs();
	void SetPixelFloat(int x, int y, const glm::vec4& c);
	glm::vec4 GetPixelFloat(int x, int y) const;

	void SetPixelUnsignedByte(int x, int y, const glm::vec4& c);
	glm::vec4 GetPixelUnsignedByte(int x, int y) const;
};