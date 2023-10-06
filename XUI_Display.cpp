//#include <Wire.h>
//#include "SH1106Wire.h"
//SH1106Wire display(0x3c, SDA, SCL);  // ADDRESS, SDA, SCL
//#include "SSD1306Wire.h"
//SSD1306Wire _display(0x3c, SDA, SCL);  // ADDRESS, SDA, SCL

// Graphic display help
// https://github.com/ThingPulse/esp8266-oled-ssd1306/issues/53
// https://javl.github.io/image2cpp/

#include "XUI_Display.h"
#include "SansSerif.h"

#include "brzo_i2c.h"
#include "SH1106Brzo.h"
SH1106Brzo _display(0x3c, SDA, SCL);  // ADDRESS, SDA, SCL

XUI_Display::XUI_Display(){
  _display.init();
  _display.flipScreenVertically();
  _display.setContrast(255);
  _display.setTextAlignment(TEXT_ALIGN_LEFT);
  
  unsigned long millis_time = millis() + 4000;
  while (millis_time > millis()){
    _display.clear();
    _display.setFont(ArialMT_Plain_24);
    _display.drawString((SCREEN_WIDTH - LOGO_LENGTH)/2, (SCREEN_HEIGHT/2)-25, F("WiGo"));
    _display.setFont(ArialMT_Plain_10);
    _display.drawString(((SCREEN_WIDTH + LOGO_LENGTH)/2)-_display.getStringWidth(F("v0.1")), (SCREEN_HEIGHT/2)-5, F("v0.1"));
    drawUnknowProgress((SCREEN_HEIGHT/2)+20);
    _display.display();
  }

}

void XUI_Display::drawTitle(string title){
  drawTextCenter(title, 0, 3, true);
}

void XUI_Display::display(){
  _display.display();
}

void XUI_Display::clear(){
  _display.clear();
}

#define BATTERY_LENGTH 7
#define BATTERY_HEIGHT 3

void XUI_Display::drawBattery(){
  _display.drawRect(SCREEN_WIDTH-BATTERY_LENGTH-1, 0, BATTERY_LENGTH, BATTERY_HEIGHT);
  //display.drawRect(SCREEN_WIDTH-1, BATTERY_HEIGHT/3, 1, BATTERY_HEIGHT/3);
  //display.fillRect(SCREEN_WIDTH-BATTERY_LENGTH, 1, (BATTERY_LENGTH-2)*0.5, BATTERY_HEIGHT-1);
  _display.setPixel(SCREEN_WIDTH-1, BATTERY_HEIGHT/3);
  _display.drawHorizontalLine(SCREEN_WIDTH-BATTERY_LENGTH, 1, (BATTERY_LENGTH-2)*0.5);
}

void XUI_Display::drawFPS(){
  _display.setFont(ArialMT_Plain_10);
  //_display.drawString(SCREEN_WIDTH - _display.getStringWidth(string(fps)), SCREEN_HEIGHT-10, string(fps));
}

void XUI_Display::drawTextCenter(string text, uint8_t line, int displayLines, bool bold){

  drawText(text, line, displayLines, bold, (SCREEN_WIDTH - _display.getStringWidth(text.c_str()))/2);

}

void XUI_Display::drawText(string text, uint8_t line, int displayLines, bool bold, sint8_t offsetX, sint8_t offsetY){

  const uint8_t* font;

  if (displayLines == DISPLAY_LINES_3){
    font = SansSerif_plain_16;
  }else if (displayLines == DISPLAY_LINES_4){
    font = SansSerif_plain_12;
  }else{
    font = SansSerif_plain_11;
  }

  drawText(text, line, displayLines, font, bold, offsetX, offsetY);

}

void XUI_Display::drawText(string text, uint8_t line, int displayLines, const uint8_t* font, bool bold, sint8_t offsetX, sint8_t offsetY){

  uint8_t itemHeight = ((SCREEN_HEIGHT+5)/displayLines);
  
  _display.setFont(font);

  _display.drawString(MENU_MARGIN + offsetX, MENU_TOP + (itemHeight * line) + offsetY, text.c_str());

  if (bold){
    _display.drawString(MENU_MARGIN + offsetX + 1, MENU_TOP + (itemHeight * line) + offsetY, text.c_str());
  }

}

void XUI_Display::drawBoxItemSelector(int displayLines){
  uint8_t itemHeight = (SCREEN_HEIGHT + 5)/displayLines; 
  uint8_t selectionTopY = ((SCREEN_HEIGHT - itemHeight)/2);
  _display.drawHorizontalLine(SELECTION_L_X + 2, selectionTopY, SELECTION_WIDTH - 2);
  _display.drawHorizontalLine(SELECTION_L_X + 1, selectionTopY + itemHeight, SELECTION_WIDTH - 1);
  _display.drawHorizontalLine(SELECTION_L_X + 2, selectionTopY + itemHeight + 1, SELECTION_WIDTH - 3);
  _display.setPixel(SELECTION_L_X + 1, selectionTopY + 1);
  _display.drawVerticalLine(SELECTION_L_X, selectionTopY + 2, itemHeight - 2);
  _display.drawVerticalLine(SELECTION_R_X, selectionTopY + 1, itemHeight - 1);
  _display.drawVerticalLine(SELECTION_R_X + 1, selectionTopY + 2, itemHeight - 3);  
}

void XUI_Display::drawLineItemSelector(int displayLines){
  uint8_t itemHeight = (SCREEN_HEIGHT + 5)/displayLines; 
  uint8_t selectionTopY = ((SCREEN_HEIGHT - itemHeight)/2) + 1;
  _display.drawVerticalLine(SELECTION_L_X, selectionTopY, itemHeight);
  _display.drawHorizontalLine(SELECTION_L_X, selectionTopY, 4);
  _display.drawHorizontalLine(SELECTION_L_X, selectionTopY + itemHeight, 4);
}

void XUI_Display::drawList(XUI_List* xuiList, int displayLines, uint8_t index, sint8_t offsetY){
    
  size_t totalItems = xuiList->getSize();
  // locate first item to drawn from current index
  int start = 0;

  start = (index - displayLines/2) ;
  if (start < 0) start = totalItems + start;
  
  // draw menu items1
  uint8_t midIndex = displayLines/2;

  for (int i = 0; i < displayLines; i++){
      // draw item
      drawText(xuiList->getElement(start++), i, displayLines, false /*((i==midIndex) && displayLines == DISPLAY_LINES_3) */, 0, offsetY);
      if (start == totalItems) start = 0;
  }

}

void XUI_Display::drawProgress(uint8_t progress,uint8_t line, uint8_t displayLines, sint8_t offsetY){
  
  uint8_t height = (SCREEN_HEIGHT+5)/displayLines;
  uint8_t y = (height * line) + offsetY;
  _display.drawProgressBar(2, y, SCREEN_WIDTH - 4, height, progress);
}

#define UNKNOW_PROGRESS_LENGTH 5

void XUI_Display::drawUnknowProgress(uint8_t line, uint8_t displayLines, sint8_t offsetY){
  
  uint8_t y = (((SCREEN_HEIGHT+5)/displayLines) * line) + offsetY;
  drawUnknowProgress(y);

}

#define PROGRESS_UPDATE_INTERVAL 200

void XUI_Display::drawUnknowProgress(uint8_t y){

    bool update = (millis() > progressNextUpdate);
    uint8_t spacing = SCREEN_WIDTH/12;
    uint8_t start = (SCREEN_WIDTH/2) - 2*spacing;

    if (update){
      // update and draw
      for (int i = 0; i < UNKNOW_PROGRESS_LENGTH; i++){
        if (i == progressIndex){
          progressLine[i] = 3;
        } else if (progressLine[i] > 0){
          progressLine[i]--;
        }
        if (progressLine[i] == 0){
          _display.setPixel(start + spacing * i, y);
        }else{
          _display.drawCircle(start + spacing * i, y, progressLine[i]);
        }
      }
      if (progressIndex == 4){
        progressIndexMov = -1;
      } else if (progressIndex == 0) {
        progressIndexMov = 1;
      }
      progressIndex += progressIndexMov;
      progressNextUpdate = millis() + PROGRESS_UPDATE_INTERVAL;
    } else { 
      // just draw
      for (int i = 0; i < UNKNOW_PROGRESS_LENGTH; i++){
        if (progressLine[i] == 0){
          _display.setPixel(start + spacing * i, y);
        }else{
          _display.drawCircle(start + spacing * i, y, progressLine[i]);
        }
      }      
    }

}

/*
void XUI_Display::drawScrollIndicator(float percent){
  
  // dotted scroll line
  for (int y = 6; y < SCREEN_HEIGHT-1; y+=6){
    _display.setPixel(SCREEN_WIDTH-2, y);
  }

  // draw relative positon
  int16_t y =  (SCREEN_HEIGHT-7) * percent + 2;
  _display.drawVerticalLine(SCREEN_WIDTH-3, y, 5);
  _display.drawVerticalLine(SCREEN_WIDTH-2, y-1, 7);
  _display.drawVerticalLine(SCREEN_WIDTH-1, y, 5);

}

void XUI_Display::drawScrollIndicator(uint8_t index, int size){
  
  uint8_t lineSize = ((SCREEN_HEIGHT+5)/size) - 4;

  for (int i = 0; i < size; i++){
    _display.drawVerticalLine(SCREEN_WIDTH-2, i * (lineSize + 4), lineSize);
  }

  // draw relative positon
  _display.drawVerticalLine(SCREEN_WIDTH-3, index * (lineSize + 4), lineSize);
  _display.drawVerticalLine(SCREEN_WIDTH-1, index * (lineSize + 4), lineSize);

}
*/

void XUI_Display::drawScrollIndicator(uint8_t index, int size){
  
  uint8_t itemSize = (SCREEN_HEIGHT+5)/size;

  uint8_t halfItemSize = itemSize / 2;

  for (int i = 0; i < size; i++){
    _display.setPixel(SCREEN_WIDTH-2, halfItemSize + (i * itemSize));
  }

  // draw relative positon
  //_display.fillCircle(SCREEN_WIDTH-2, halfItemSize + (index * itemSize), 2);
  //_display.fillRect(SCREEN_WIDTH-3, halfItemSize + (index * itemSize)-1, 3, 4);  
  _display.fillRect(SCREEN_WIDTH-3, (index * itemSize)-1, 3, itemSize);  
}


