#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;
#include "Arduino.h"
#include "OneButton.h"
#include "XUI_Config.h"
#include "XUI_List.h"
#include "XUI_Display.h"
#include "XUI_Screen.h"
#include "XUI_ScreenMenu.h"
#include "XUI_ScreenScan.h"
#include "XUI_ScreenFonts.h"

#define BTTN_UP D5
#define BTTN_DOWN D6
#define BTTN_LEFT D3
#define BTTN_RIGHT D7

class XUI_Engine {
  public:
    XUI_Engine(XUI_Display* xuiDisplay, XUI_Screen* homeScreen);
    void run();
    void nav(XUI_Screen* toScreen);
    XUI_Display* xuiDisplay;
    XUI_Screen* xuiScreen;
  private:
    XUI_Screen* xuiHome;
    XUI_Screen* xuiPrevScreen;

    OneButton* bttnUp;
    OneButton* bttnDown;
    OneButton* bttnLeft;
    OneButton* bttnRight;

    void bttnUp_Click();
    void bttnDown_Click();
    void bttnLeft_Click();
    void bttnRight_Click();

    float fps;
    unsigned long millis_time;
    unsigned long millis_time_last;
};
