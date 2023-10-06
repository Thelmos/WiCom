#pragma once

#include "Arduino.h"

class XUI_Engine;
class XUI_Display;

class XUI_Screen {
  public:
    string xuiTitle;

    XUI_Screen(string title);
    void addScreen(XUI_Screen* child);
    void init(XUI_Engine* xuiEngine, XUI_Screen* prevScreen);
    virtual void start();
    virtual void run();
    virtual bool end();
    virtual void bttn_event(uint8_t button);
    vector<XUI_Screen*> xuiScreens;
  protected:
    XUI_Engine* xuiEngine;
    XUI_Display* xuiDisplay;
    XUI_Screen* prevScreen;
    
    uint8_t childrenCount;
};
