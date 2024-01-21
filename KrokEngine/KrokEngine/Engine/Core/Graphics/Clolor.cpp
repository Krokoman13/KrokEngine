#include "Clolor.hpp"

Color::Color(const unsigned int a_r, const unsigned int a_g, const unsigned int a_b, const unsigned int a_alpha)
{
	r = clamp(a_r);
	g = clamp(a_g);
	b = clamp(a_b);
	alpha = clamp(a_alpha);
}

Color::Color(const Color& a_other)
{
	r = a_other.r;
	g = a_other.g;
	b = a_other.b;
	alpha = a_other.alpha;
}

Color& Color::operator=(const Color a_other)
{
	r = a_other.r;
	g = a_other.g;
	b = a_other.b;
	alpha = a_other.alpha;
	return *this;
}

Color Color::operator/(const float a_value)
{
	return Color((unsigned int)(r / a_value), (unsigned int)(g / a_value), (unsigned int)(b / a_value), (unsigned int)(alpha / a_value));
}

Color& Color::operator/=(const float a_value)
{
	r = (unsigned int)(r / a_value);
	g = (unsigned int)(g / a_value);
	b = (unsigned int)(b / a_value);
	alpha = (unsigned int)(alpha / a_value);
	return *this;
}

Color Color::operator*(const float a_value)
{
	return Color((unsigned int)(r * a_value), (unsigned int)(g * a_value), (unsigned int)(b * a_value), (unsigned int)(alpha * a_value));
}

Color& Color::operator*=(const float a_value)
{
	r = (unsigned int)(r * a_value);
	g = (unsigned int)(g * a_value);
	b = (unsigned int)(b * a_value);
	alpha = (unsigned int)(alpha * a_value);
	return *this;
}

Color Color::Hex(const unsigned int hexValue)
{
	Color rgbColor;
	rgbColor.r = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
	rgbColor.g = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
	rgbColor.b = ((hexValue) & 0xFF);        // Extract the BB byte
	return rgbColor;
}

#define C_WHITE 0xFFFFFF
#define C_BLACK 0x000000
#define C_RED 0xFF0000
#define C_GREEN 0x00FF00
#define C_BLUE 0x0000FF
#define C_YELLOW 0xFFFF00
#define C_PINK 0xFFC0CB
#define C_GRAY 0x808080
#define C_ORANGE 0xFFA500
#define C_MAROON 0x800000

Color Color::White()
{
	return Color::Hex(C_WHITE);
}

Color Color::Black()
{
	return Color::Hex(C_BLACK);
}

Color Color::Red()
{
	return Color::Hex(C_RED);
}

Color Color::Green()
{
	return Color::Hex(C_GREEN);
}

Color Color::Blue()
{
	return Color::Hex(C_BLUE);
}

Color Color::Yellow()
{
	return Color::Hex(C_YELLOW);
}

Color Color::Pink()
{
	return Color::Hex(C_PINK);
}

Color Color::Gray()
{
	return Color::Hex(C_GRAY);
}

Color Color::Orange()
{
	return Color::Hex(C_ORANGE);
}

Color Color::Maroon()
{
	return Color::Hex(C_MAROON);
}