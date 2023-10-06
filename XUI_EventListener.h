#ifndef XUIEventListener
#define XUIEventListener

#include "Arduino.h"

class XUI_EventListener {
  public:
    virtual void event(uint8_t event){};
  private:

};

#endif