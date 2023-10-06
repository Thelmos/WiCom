#include "XUI_Engine.h"

XUI_Screen::XUI_Screen(string title){
  xuiTitle = title;
  childrenCount = 0;
}

void XUI_Screen::addScreen(XUI_Screen* screen){
  screen->init(xuiEngine, this);
  xuiScreens.push_back(screen);
  childrenCount++;
}

void XUI_Screen::init(XUI_Engine* xuiEngine, XUI_Screen* prevScreen){
  this->xuiEngine = xuiEngine;
  this->xuiDisplay = xuiEngine->xuiDisplay;
  this->prevScreen = prevScreen;
}

void XUI_Screen::run(){
  xuiDisplay->clear();
  xuiDisplay->drawTitle(xuiTitle);
  xuiDisplay->display();
}

void XUI_Screen::start(){
}

bool XUI_Screen::end(){
  return true;
}

void XUI_Screen::bttn_event(uint8_t button){
  switch (button){
    case BTTN_UP:
      break;
    case BTTN_DOWN:
      break;
    case BTTN_LEFT:
      xuiEngine->nav(prevScreen);
      break;
    case BTTN_RIGHT:
      break;
  }
}
