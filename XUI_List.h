#pragma once

#include "Arduino.h"

class XUI_List {
  public:
    virtual string getElement(uint8_t index){return "";};
    virtual size_t getSize(){return 0;};
  private:

};
