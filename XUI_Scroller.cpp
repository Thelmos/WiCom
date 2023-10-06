#include "XUI_Scroller.h"

XUI_Scroller::XUI_Scroller(int frames, XUI_EventListener* listener){
  this->frames = frames;
  this->listener = listener;
}

void XUI_Scroller::scrollUp(){
  if (animateDown == 0) animateUp = frames;
}

void XUI_Scroller::scrollDown(){
  if (animateUp == 0) animateDown = frames;
}

sint8_t XUI_Scroller::getOffset(){
  sint8_t offset = 0;
  // scroll-up scroll-down animations
  if (animateUp > 0){
    offset = -2*(frames - animateUp + 1);
    animateUp--;
    if (animateUp == 0) listener->event(EVT_SCROLL_UP_END);
  }else if (animateDown > 0){
    offset = 2*(frames - animateDown + 1);
    animateDown--;
    if (animateDown == 0) listener->event(EVT_SCROLL_DOWN_END);     
  }
  return offset;
}

bool XUI_Scroller::scrolling(){
  return (animateUp != 0 || animateDown != 0);
}
