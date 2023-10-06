#pragma once

#include "XUI_Screen.h"
#include "XUI_Scroller.h"
#include "XUI_List.h"
#include "XUI_EventListener.h"

class XUI_ScreenMenu : public XUI_Screen, public XUI_EventListener, public XUI_List {
  public:
    XUI_ScreenMenu(string title, uint8_t visibleOptions);
    void run();
    void bttn_event(uint8_t button);
    string getElement(uint8_t index);
    size_t getSize();
    void event(uint8_t event);
  private:
    bool _draw;
    uint8_t _animateUp = 0;
    uint8_t _animateDown = 0;
    uint8_t displayLines;
    uint8_t menuIndex;
    XUI_Scroller* xuiScroller;
    void drawMenu(sint8_t offset);
};
