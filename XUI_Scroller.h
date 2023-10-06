#pragma once

#include "XUI_EventListener.h"
#include "XUI_Config.h"

class XUI_Scroller {
  public:
    XUI_Scroller(int frames, XUI_EventListener* listener);
    void scrollUp();
    void scrollDown();
    sint8_t getOffset();
    bool scrolling();
  private:
    XUI_EventListener* listener;
    uint8_t frames = 0;
    uint8_t animateUp = 0;
    uint8_t animateDown = 0;
};
