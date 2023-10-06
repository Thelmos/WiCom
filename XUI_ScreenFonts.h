#pragma once

#include "XUI_Screen.h"
#include "XUI_Scroller.h"
#include "XUI_EventListener.h"
#include "SansSerif.h"

#define FONT_COUNT 5
class XUI_ScreenFonts : public XUI_Screen, public XUI_EventListener{
  public:
    XUI_ScreenFonts(string title);
    void run();
    void bttn_event(uint8_t button);
  private:
    bool _draw;
    uint8_t currentIndex = 0;
     /*
    const uint8_t* fonts[FONT_COUNT] = {Arimo_Regular_10, DejaVu_Sans_ExtraLight_10, Dialog_plain_10, Open_Sans_Regular_10, Open_Sans_Condensed_Bold_10, Roboto_10, Roboto_Condensed_10, SansSerif_plain_10};    
    const string fontNames[FONT_COUNT] = {"Arimo_Regular_10", "DejaVu_Sans_ExtraLight_10", "Dialog_plain_10", "Open_Sans_Regular_10", "Open_Sans_Condensed_Bold_10", "Roboto_10", "Roboto_Condensed_10", "SansSerif_plain_10"};    
    */
    const uint8_t* fonts[FONT_COUNT] = {SansSerif_plain_10, SansSerif_plain_11, SansSerif_plain_12, SansSerif_plain_14, SansSerif_plain_16};    
    const string fontNames[FONT_COUNT] = {"SansSerif_plain_10", "SansSerif_plain_11", "SansSerif_plain_12", "SansSerif_plain_14", "SansSerif_plain_16"};    
};
