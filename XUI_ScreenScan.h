#pragma once

#include "XUI_Screen.h"
#include "XUI_Scroller.h"
#include "XUI_EventListener.h"
#include "WifiScanner.h"

class XUI_ScreenScan : public XUI_Screen, public XUI_EventListener, public XUI_List {
  public:
    XUI_ScreenScan(string title, uint8_t scanMode, WifiScanner wifiScanner);
    void start();
    void run();
    void bttn_event(uint8_t button);
    string getElement(uint8_t index);
    size_t getSize();
    void event(uint8_t event);
  private:
    size_t showScanInfo(uint8_t APCount, uint8_t STACount, uint8_t progress);
    WifiScanner wifiScanner;
    bool _draw;
    uint8_t _animateUp = 0;
    uint8_t _animateDown = 0;
    uint8_t currentIndex = 0;
    XUI_Scroller* xuiScroller;
    // wifi scan variables
    uint8_t scanMode;
    
    vector<uint8_t*> selectedAPs;
    vector<uint8_t*> selectedStations;
    vector<uint16_t*> packets;

    String ssid;
    uint8_t STACount = 0;
    uint8_t currentAP = 0;

    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t* BSSID;
    int32_t channel;
    bool isHidden;

    struct Station {
        uint8_t   ap;
        uint8_t   ch;
        uint8_t * mac;
    };
};
