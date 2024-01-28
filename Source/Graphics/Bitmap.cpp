#include "Bitmap.h"

Bitmap::Bitmap(int w, int h, int comp, BitmapFormat fmt)
	: w(w),
	h(h),
	comp(comp),
	fmt(fmt),
	data(w* h* comp* GetBytesPerComponent(fmt))
{
	InitGetSetFuncs();
}

Bitmap::Bitmap(int w, int h, int d, int comp, BitmapFormat fmt)
	: w(w),
	h(h),
	d(d),
	comp(comp),
	fmt(fmt),
	data(w* h* d* comp* GetBytesPerComponent(fmt))
{
	InitGetSetFuncs();
}

Bitmap::Bitmap(int w, int h, int comp, BitmapFormat fmt, const void* ptr)
	: w(w),
	h(h),
	comp(comp),
	fmt(fmt),
	data(w* h* comp* GetBytesPerComponent(fmt))
{
	InitGetSetFuncs();
	memcpy(data.data(), ptr, data.size());
}

int Bitmap::GetBytesPerComponent(BitmapFormat fmt)
{
	if (fmt == BitmapFormat::BitmapFormatUnsignedByte) return 1;
	if (fmt == BitmapFormat::BitmapFormatFloat) return 4;
	return 0;
}

void Bitmap::SetPixel(int x, int y, const glm::vec4& c)
{
	(*this.*SetPixelFunc)(x, y, c);
}

glm::vec4 Bitmap::GetPixel(int x, int y) const
{
	return ((*this.*GetPixelFunc)(x, y));
}

void Bitmap::InitGetSetFuncs()
{
	switch (fmt)
	{
	case BitmapFormat::BitmapFormatUnsignedByte:
		SetPixelFunc = &Bitmap::SetPixelUnsignedByte;
		GetPixelFunc = &Bitmap::GetPixelUnsignedByte;
		break;
	case BitmapFormat::BitmapFormatFloat:
		SetPixelFunc = &Bitmap::SetPixelFloat;
		GetPixelFunc = &Bitmap::GetPixelFloat;
		break;
	}
}

void Bitmap::SetPixelFloat(int x, int y, const glm::vec4& c)
{
	const int ofs = comp * (y * w + x);
	float* fdata = reinterpret_cast<float*>(data.data());
	if (comp > 0) fdata[ofs + 0] = c.x;
	if (comp > 1) fdata[ofs + 1] = c.y;
	if (comp > 2) fdata[ofs + 2] = c.z;
	if (comp > 3) fdata[ofs + 3] = c.w;
}

glm::vec4 Bitmap::GetPixelFloat(int x, int y) const
{
	const int ofs = comp * (y * w + x);
	const float* fdata = reinterpret_cast<const float*>(data.data());
	return glm::vec4(
		comp > 0 ? fdata[ofs + 0] : 0.0f,
		comp > 1 ? fdata[ofs + 1] : 0.0f,
		comp > 2 ? fdata[ofs + 2] : 0.0f,
		comp > 3 ? fdata[ofs + 3] : 0.0f);
}

void Bitmap::SetPixelUnsignedByte(int x, int y, const glm::vec4& c)
{
	const int ofs = comp * (y * w + x);
	if (comp > 0) data[ofs + 0] = uint8_t(c.x * 255.0f);
	if (comp > 1) data[ofs + 1] = uint8_t(c.y * 255.0f);
	if (comp > 2) data[ofs + 2] = uint8_t(c.z * 255.0f);
	if (comp > 3) data[ofs + 3] = uint8_t(c.w * 255.0f);
}

glm::vec4 Bitmap::GetPixelUnsignedByte(int x, int y) const
{
	const int ofs = comp * (y * w + x);
	return glm::vec4(
		comp > 0 ? float(data[ofs + 0]) / 255.0f : 0.0f,
		comp > 1 ? float(data[ofs + 1]) / 255.0f : 0.0f,
		comp > 2 ? float(data[ofs + 2]) / 255.0f : 0.0f,
		comp > 3 ? float(data[ofs + 3]) / 255.0f : 0.0f);
}