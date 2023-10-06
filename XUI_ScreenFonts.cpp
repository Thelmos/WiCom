#include "XUI_Engine.h"
#include "XUI_ScreenFonts.h"

XUI_ScreenFonts::XUI_ScreenFonts(string title)
  : XUI_Screen(title)
{
    _draw = true;
}

void XUI_ScreenFonts::run(){

  if (_draw){ // avoid drawing when nothing has changed
  
    xuiDisplay->clear();
    xuiDisplay->drawText(fontNames[currentIndex], 0, 5, fonts[currentIndex]);
    xuiDisplay->drawText("Un anillo para gobernarlos a todos", 1, 5, fonts[currentIndex]);
    xuiDisplay->drawText("un anillo para encontrarlos. 123456789", 2, 5, fonts[currentIndex]);
    xuiDisplay->drawText("un anillo para traerlos a todos", 3, 5, fonts[currentIndex]);
    xuiDisplay->drawText("y atarlos en la oscuridad. 123456789", 4, 5, fonts[currentIndex]);

    xuiDisplay->display();

    _draw = false;
  }

}

void XUI_ScreenFonts::bttn_event(uint8_t button){
  _draw = true;
  switch (button){
    case BTTN_UP:
      if (currentIndex == 0){
        currentIndex = FONT_COUNT-1;
      }else{
        currentIndex--;
      }
      _draw = true;
      break;
    case BTTN_DOWN:
      currentIndex++;
      if (currentIndex > FONT_COUNT-1) currentIndex = 0;
      _draw = true;
      break;
    case BTTN_LEFT:
      xuiEngine->nav(prevScreen);
      break;
    case BTTN_RIGHT:
      break;
  }
}


