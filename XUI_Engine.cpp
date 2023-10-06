#include "XUI_Engine.h"

XUI_Engine::XUI_Engine(XUI_Display* display, XUI_Screen* homeScreen){
  xuiDisplay = display;

  xuiHome = homeScreen;
  xuiPrevScreen = homeScreen;
  xuiScreen = homeScreen;
  xuiScreen->init(this, xuiPrevScreen);
  xuiScreen->start();

  // button listeners
  bttnUp = new OneButton(BTTN_UP);
  bttnUp->attachClick([](void *scope) { ((XUI_Engine *) scope)->bttnUp_Click();}, this);
  bttnDown = new OneButton(BTTN_DOWN);
  bttnDown->attachClick([](void *scope) { ((XUI_Engine *) scope)->bttnDown_Click();}, this);
  bttnLeft = new OneButton(BTTN_LEFT);
  bttnLeft->attachClick([](void *scope) { ((XUI_Engine *) scope)->bttnLeft_Click();}, this);
  bttnRight = new OneButton(BTTN_RIGHT);
  bttnRight->attachClick([](void *scope) { ((XUI_Engine *) scope)->bttnRight_Click();}, this);
}

void XUI_Engine::run(){

//TODO Validar que se ha llamado a init ¿?

  // draw current screen
  xuiScreen->run();
  
  bttnUp->tick();
  bttnDown->tick();
  bttnLeft->tick();
  bttnRight->tick();

  // fps stats
  millis_time_last = millis_time;
  millis_time = millis();
  fps = millis_time - millis_time_last;
  fps = round(1000.0/fps*1.0);
}

void XUI_Engine::nav(XUI_Screen* toScreen){
  if (xuiScreen->end()){
    xuiPrevScreen = xuiScreen; 
    xuiScreen = toScreen;
    xuiScreen->start();
  }
}

void XUI_Engine::bttnUp_Click(){
  xuiScreen->bttn_event(BTTN_UP);
}

void XUI_Engine::bttnDown_Click(){
  xuiScreen->bttn_event(BTTN_DOWN);
}

void XUI_Engine::bttnLeft_Click(){
  xuiScreen->bttn_event(BTTN_LEFT);
}

void XUI_Engine::bttnRight_Click(){
  xuiScreen->bttn_event(BTTN_RIGHT);
}

