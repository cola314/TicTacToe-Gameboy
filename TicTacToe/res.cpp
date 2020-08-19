#ifndef RESOURCE_CPP
#define RESOURCE_CPP

#include "page.cpp"

// color hex
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Page widget size
#define Main_page_size 5
#define Info_page_size 3
#define TicTacToe_page_size 20

// button - Main_page
#define PLAY_BUTTON 101
#define INFO_BUTTON 102 
#define MAIN_BUTTON 103

// button - TicTacToe
#define B1_BUTTON	201
#define B2_BUTTON	202
#define B3_BUTTON	203
#define B4_BUTTON	204
#define B5_BUTTON	205
#define B6_BUTTON	206
#define B7_BUTTON	207
#define B8_BUTTON	208
#define B9_BUTTON	209
#define HOME_BUTTON 210

//button - Info_page
#define BACK_BUTTON 104



class Main_page : public Page {
public :
	Main_page() : Page(Main_page_size) { init(); }
	void init() {
		page[0] = (Element*)new Caption(20, 20, "Tic Tac Toe", 2, GREEN);
		page[1] = (Element*)new Caption(35, 95, "Play", 2, GREEN);
		page[2] = (Element*)new Caption(30, 150, "Info", 2, GREEN);
		page[3] = (Element*)new Button(30, 90, 170, 40, PLAY_BUTTON, WHITE);
		page[4] = (Element*)new Button(30, 150, 170, 40, INFO_BUTTON, WHITE);
	}
};

class Info_page : public Page {
public :
	Info_page() : Page(Info_page_size) { init(); }
	void init() {
		page[0] = (Element*)new Caption(20, 60, "Good Good Good", 2, GREEN);
		page[1] = (Element*)new Caption(10, 10, "<", 4, BLUE);
		page[2] = (Element*)new Button(10, 10, 40, 40, MAIN_BUTTON, WHITE);
	}
};

class TicTacToe_page : public Page {
public:
	TicTacToe_page() : Page(TicTacToe_page_size) { init(); }
	void init() {
		//caption
		page[0] = (Element*)new Caption(35,	      85, "", 4, RED);
		page[1] = (Element*)new Caption(35 + 70,  85, "", 4, RED);
		page[2] = (Element*)new Caption(35 + 140, 85 , "", 4, RED);
		page[3] = (Element*)new Caption(35,       85 + 70, "", 4, RED);
		page[4] = (Element*)new Caption(35 + 70,  85 + 70, "", 4, RED);
		page[5] = (Element*)new Caption(35 + 140, 85 + 70, "", 4, RED);
		page[6] = (Element*)new Caption(35,       85 + 140, "", 4, RED);
		page[7] = (Element*)new Caption(35 + 70,  85 + 140, "", 4, RED);
		page[8] = (Element*)new Caption(35 + 140, 85 + 140, "", 4, RED);
		//button
		page[9]  = (Element*)new Button(20,       70, 60, 60, B1_BUTTON, WHITE);
		page[10] = (Element*)new Button(20 + 70,  70, 60, 60, B2_BUTTON, WHITE);
		page[11] = (Element*)new Button(20 + 140, 70, 60, 60, B3_BUTTON, WHITE);
		page[12] = (Element*)new Button(20,       70 + 70, 60, 60, B4_BUTTON, WHITE);
		page[13] = (Element*)new Button(20 + 70,  70 + 70, 60, 60, B5_BUTTON, WHITE);
		page[14] = (Element*)new Button(20 + 140, 70 + 70, 60, 60, B6_BUTTON, WHITE);
		page[15] = (Element*)new Button(20,       70 + 140, 60, 60, B7_BUTTON, WHITE);
		page[16] = (Element*)new Button(20 + 70,  70 + 140, 60, 60, B8_BUTTON, WHITE);
		page[17] = (Element*)new Button(20 + 140, 70 + 140, 60, 60, B9_BUTTON, WHITE);
		//home button
		page[18] = (Element*)new Caption(10, 10, "<", 4, BLUE);
		page[19] = (Element*)new Button(10, 10, 40, 40, MAIN_BUTTON, WHITE);
	}
};

#endif