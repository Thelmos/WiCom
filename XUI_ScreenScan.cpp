#include "XUI_Engine.h"
#include "XUI_ScreenScan.h"
#include "WifiScanner.h"
#include "ESP8266WiFi.h"

XUI_ScreenScan::XUI_ScreenScan(string title, uint8_t scanMode, WifiScanner wifiScanner)
  : XUI_Screen(title)
{
  this->scanMode = scanMode;
  this->wifiScanner = wifiScanner;
  _draw = true;
  xuiScroller = new XUI_Scroller(4, dynamic_cast<XUI_EventListener*> (this));
}

#define SCAN_TIME 15000
#define STA_SCAN_OUTPUT_TIME 3000
#define STA_SCAN_CHANNEL_TIME 500

void XUI_ScreenScan::start(){
  uint32_t startTime = millis();
  
  selectedAPs.clear();
  selectedStations.clear();
  packets.clear();

  // scan APS
  this->wifiScanner.startScan(true, true);
  do{
    this->wifiScanner.runScan();
    this->showScanInfo(wifiScanner.APCount, STACount, (millis()-startTime)*100/SCAN_TIME);
  } while (this->wifiScanner.APCount < 0);


  if (this->wifiScanner.APCount == 0){
    // no APs foun

  }else{
    // scan stations
    uint32_t currentTime, outputTime, channelTime = millis();
    uint8_t currentAP = 0;

    this->wifiScanner.setChannel(WiFi.channel(currentAP));
    this->wifiScanner.startSniff();
    
    while (currentTime - startTime < SCAN_TIME){

      STACount = this->wifiScanner.runSniff();

      // print status every 3s
      if (currentTime - outputTime > STA_SCAN_OUTPUT_TIME) {
          outputTime = currentTime;
          this->showScanInfo(wifiScanner.APCount, STACount, (millis()-startTime)*100/SCAN_TIME);
      }

      // channel hopping
      if (currentTime - channelTime > STA_SCAN_CHANNEL_TIME) {
          channelTime = currentTime;
          // go to next AP channel
          if (++currentAP == wifiScanner.APCount) currentAP = 0;
          this->wifiScanner.setChannel(WiFi.channel(currentAP));
      }

      currentTime = millis();
    }

    // end scan
    this->wifiScanner.stopSniff();
  }
}

void XUI_ScreenScan::run(){


    if (scanMode == SCAN_MODE_STATIONS) {
        stations.sort();
        stations.printAll();
    }
    start(SCAN_MODE_OFF);

  }

  do{
    xuiDisplay->clear();
    xuiDisplay->drawTextCenter("Scanning", 1, DISPLAY_LINES_5);
    xuiDisplay->drawUnknowProgress(3, DISPLAY_LINES_5);
    xuiDisplay->display();
    networkCount = WiFi.scanComplete();
  } while (networkCount < 0);

  size_t networkCount = getSize();
  
  if (networkCount == 0 && _draw){ // avoid drawing when we have no items to draw
    xuiDisplay->clear();
  } else if (_draw){ // avoid drawing when nothing has changed

    _draw = xuiScroller->scrolling();

    xuiDisplay->clear();
    xuiDisplay->drawList(dynamic_cast<XUI_List*> (this), DISPLAY_LINES_5, currentIndex, xuiScroller->getOffset());
    xuiDisplay->drawLineItemSelector(DISPLAY_LINES_5);
    xuiDisplay->drawScrollIndicator(currentIndex, networkCount);
    xuiDisplay->display();
  }

}

size_t XUI_ScreenScan::showScanInfo(uint8_t APCount, uint8_t STACount, uint8_t progress){
    xuiDisplay->clear();
    xuiDisplay->drawText("Scanning...", 1, DISPLAY_LINES_4);
    xuiDisplay->drawProgress(progress, 2, DISPLAY_LINES_4);
    xuiDisplay->drawText("APs: " + APCount, 3, DISPLAY_LINES_4);
    xuiDisplay->drawText("Stations: " + STACount, 3, DISPLAY_LINES_4);
    xuiDisplay->display();
}

string XUI_ScreenScan::getElement(uint8_t index){
  WiFi.getNetworkInfo(index, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
  string power = "     ";
  if (RSSI >= -30){
    power = "IIII ";
  }else if (RSSI >= -65){
    power = " III ";
  }else if (RSSI >= -75){
    power = "  II ";
  }else if (RSSI >= -90){
    power = "   I ";
  }

  return string(power).append(ssid.c_str()); //.append(encryptionType == ENC_TYPE_NONE ? "open " : " ").append(isHidden ? "hidden" : "");
};

size_t XUI_ScreenScan::getSize(){
  return networkCount;
}

void XUI_ScreenScan::event(uint8_t event){
  switch (event) {
    case EVT_SCROLL_UP_END:
      currentIndex++;
      if (currentIndex == networkCount) currentIndex = 0;        
      break;
    case EVT_SCROLL_DOWN_END:
      if (currentIndex == 0) {
        currentIndex = networkCount-1;
      }else{
        currentIndex--;
      }  
      break;
  }
};

void XUI_ScreenScan::bttn_event(uint8_t button){
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
      // TODO ir al detalle de la entrada seleccionada
      break;
  }
}



