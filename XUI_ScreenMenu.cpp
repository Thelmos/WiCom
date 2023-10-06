#include <sys/types.h>
#include "XUI_Engine.h"

XUI_ScreenMenu::XUI_ScreenMenu(string title, uint8_t displayLines)
  : XUI_Screen(title)
{
    this->displayLines = displayLines;
    _draw = true;
    uint8_t animationFrames = (displayLines == 3) ? 8 : 4;
    xuiScroller = new XUI_Scroller(animationFrames, dynamic_cast<XUI_EventListener*> (this));
}

void XUI_ScreenMenu::bttn_event(uint8_t button){
  _draw = true;
  switch (button){
    case BTTN_UP:
      xuiScroller->scrollDown();
      _draw = true;
      break;
    case BTTN_DOWN:
      xuiScroller->scrollUp();
      _draw = true;
      break;
    case BTTN_LEFT:
      xuiEngine->nav(prevScreen);
      break;
    case BTTN_RIGHT:
      if (xuiScreens.size() > menuIndex) xuiEngine->nav(xuiScreens[menuIndex]);
      break;
  }
}

void XUI_ScreenMenu::run(){
  
  if (childrenCount == 0 && _draw){ // avoid drawing when we have no items to draw
    xuiDisplay->clear();
  } else if (_draw){ // avoid drawing when nothing has changed

    _draw = xuiScroller->scrolling();

    xuiDisplay->clear();
    xuiDisplay->drawList(dynamic_cast<XUI_List*> (this), displayLines, menuIndex, xuiScroller->getOffset());
    if (displayLines == DISPLAY_LINES_3){
      xuiDisplay->drawBoxItemSelector(displayLines);
    }else{
      xuiDisplay->drawLineItemSelector(displayLines);      
    }
    xuiDisplay->drawScrollIndicator(menuIndex, childrenCount);
    xuiDisplay->display();

  }

}

string XUI_ScreenMenu::getElement(uint8_t index){
  return xuiScreens[index]->xuiTitle;
};

size_t XUI_ScreenMenu::getSize(){
  return childrenCount;
}

void XUI_ScreenMenu::event(uint8_t event){
  switch (event) {
    case EVT_SCROLL_UP_END:
      menuIndex++;
      if (menuIndex == childrenCount) menuIndex = 0;        
      break;
    case EVT_SCROLL_DOWN_END:
      if (menuIndex == 0) {
        menuIndex = childrenCount-1;
      }else{
        menuIndex--;
      }  
      break;
  }
};




