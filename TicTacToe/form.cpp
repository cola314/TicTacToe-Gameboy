#ifndef FORM_CPP
#define FORM_CPP

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#define BLACK 0

#define ELEMENT 0
#define CAPTION 1
#define RECT 	2
#define BUTTON  3

class Element {
public:
	int type = ELEMENT;
	Element() : Element(0, 0, false) {}
	Element(int x, int y, uint16_t color) : x(x), y(y), color(color), visible(true) {}
	virtual void print(const Adafruit_TFTLCD& tft) {}
	bool visible;
	int x, y;
	uint16_t color;
};

class Caption : public Element {
public :
	Caption() : Caption(0, 0, "", 2, 0) {}
	Caption(int x, int y, const char* str, int font_size, uint16_t color) : Element(x, y, color), str(str), font_size(font_size) { type = CAPTION; }
	virtual void print(const Adafruit_TFTLCD& tft) {
		tft.setCursor(x, y);
		tft.setTextColor(color);
		tft.setTextSize(font_size);
		tft.print(str);
	}
	int font_size;
	const char* str;
};

class Rect : public Element {
public :
	Rect() : Rect(0, 0, 0, 0, 0) {}
	Rect(int x, int y, int width, int height, uint16_t color) : Element(x, y, color), width(width), height(height), filled(true) { type = RECT; }
	virtual void print(const Adafruit_TFTLCD& tft) {
		if(filled) tft.fillRect(x, y, width, height, color);
		else tft.drawRect(x, y, width, height, color);
	}
	int width, height;
	bool filled;
};

class Button : public Rect {
public:
	Button() : Button(0, 0, 0, 0, 0, 0) {}
	Button(int x, int y, int width, int height, int task, uint16_t color) : Rect(x, y, width, height, color), task(task), enable(true) { type = BUTTON; }
	int click(int _x, int _y) {
		if (x <= _x && _x < x + width && y <= _y && _y < y + height) return task;
		return 0;
	}
	int task;
	bool enable;
};

#endif