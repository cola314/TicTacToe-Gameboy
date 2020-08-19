#ifndef PAGE_CPP
#define PAGE_CPP

#include "form.cpp";

class Page {
public: 
	Page() : Page(0) {}
	Page(int n) : size(n) {
		page = new Element*[size];
		for (int i = 0; i < size; i++) {
			page[i] = nullptr;
		}
	}
	~Page() { 
		for (int i = 0; i < size; i++) {
			if (page[i] != nullptr) {
				delete page[i];
			}
		}
		delete[] page; 
	}
	virtual void init() {};
	virtual void refresh(const Adafruit_TFTLCD& tft) {
		for (int i = size - 1; i >= 0; i--) {
			if (page[i] != nullptr && page[i]->visible) {
				page[i]->print(tft);
			}
		}
	}
	virtual int button_click(int x, int y) {
		int cmd = 0;
		for (int i = 0; i < size; i++) {
			if (page[i] != nullptr && page[i]->type == BUTTON) {
				cmd = ((Button*)page[i])->click(x, y);
				if (cmd) return cmd;
			}
		}
		return cmd;
	}
	Element** page;
	int size = 0;
};

#endif