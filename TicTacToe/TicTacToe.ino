#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include "sd_bmp.h"
#include "res.cpp"

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:

#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

Page* screen;

namespace G {
  int turn = 1;
  char board[9];
  
  void init() {
    turn = 1;
    memset(board, 0, sizeof(board));
  }
  
  void Tgame(int x) {
    if(board[x]) return;
    board[x] = turn;
    if(turn == 1) {
      ((Caption*)(screen->page[x]))->str = "O";
      screen->page[x]->color = BLUE;
      turn = 2;
    }
    else {
      ((Caption*)(screen->page[x]))->str = "X";
      screen->page[x]->color = RED;
      turn = 1;
    }
    screen->refresh(tft);
  }
}

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("Paint!"));
  
  tft.reset();
  
  uint16_t identifier = tft.readID();
  
  tft.begin(identifier);
  
  sd_init();  
  
  tft.fillScreen(BLACK); 
  
  screen = new Main_page();
  screen->refresh(tft);
}

void new_input(int x, int y) {
  int cmd = screen->button_click(x, y);
  Serial.println(cmd);
  switch(cmd) {
    //Main_page
    case PLAY_BUTTON:
      tft.fillScreen(BLACK);
      delete screen;
      screen = (Page*)new TicTacToe_page();
      screen->refresh(tft);
      G::init();
      break;
    case INFO_BUTTON: 
      tft.fillScreen(BLACK); 
      bmpDraw(tft, "koker.bmp", 0, 0);
      delete screen;
      screen = (Page*)new Info_page();
      screen->refresh(tft);
      
      break;
      
    //goto Main_page
    case MAIN_BUTTON:
      tft.fillScreen(BLACK); 
      delete screen;
      screen = (Page*)new Main_page();
      screen->refresh(tft);
      break;
      
    //TicTacToe_page
    case B1_BUTTON: G::Tgame(0); break;
    case B2_BUTTON: G::Tgame(1); break;
    case B3_BUTTON: G::Tgame(2); break;
    case B4_BUTTON: G::Tgame(3); break;
    case B5_BUTTON: G::Tgame(4); break;
    case B6_BUTTON: G::Tgame(5); break;
    case B7_BUTTON: G::Tgame(6); break;
    case B8_BUTTON: G::Tgame(7); break;
    case B9_BUTTON: G::Tgame(8); break;
    
    default : break;
  }
}

void loop()
{ 
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
    if (p.y < (TS_MINY-5)) {
      Serial.println("erase");
      // press the bottom of the screen to erase 
      //tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
    }
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MAXY, TS_MINY, tft.height(), 0);
  
    new_input(p.x, p.y);
  }
}
