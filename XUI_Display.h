#pragma once

#include "Arduino.h"
#include "XUI_Engine.h"

class XUI_Display {
  public:
    XUI_Display();
    void drawTitle(string title);
    void drawBattery();
    void drawFPS();
    void drawBoxItemSelector(int displayLines);
    void drawLineItemSelector(int displayLines);
    void drawTextCenter(string text, uint8_t line, int displayLines, bool bold = false);
    void drawText(string text, uint8_t line, int displayLines, bool bold = false, sint8_t offsetX = 0, sint8_t offsetY = 0);
    void drawText(string text, uint8_t line, int displayLines, const uint8_t* font, bool bold = false, sint8_t offsetX = 0, sint8_t offsetY = 0);
    void drawList(XUI_List* xuiList, int displayLines, uint8_t index, sint8_t offsetY = 0);
    void drawScrollIndicator(uint8_t index, int size);
    void drawProgress(uint8_t progress,uint8_t line, uint8_t displayLines, sint8_t offsetY = 0);
    void drawUnknowProgress(uint8_t line, uint8_t displayLines, sint8_t offsetY = 0);
    void drawUnknowProgress(uint8_t y);
    void display();
    void clear();
  private:
    uint8_t progressLine[5] = {3, 2, 1, 0, 0};
    uint8_t progressIndex = 1;
    sint8_t progressIndexMov = 1;
    ulong progressNextUpdate = 0;

};
