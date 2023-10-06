#include "ESP8266WiFi.h"
extern "C" {
  #include "ets_sys.h"
  #include "osapi.h"
  #include "gpio.h"
  #include "os_type.h"
  #include "user_config.h"
  #include "user_interface.h"
}

#include "Arduino.h"
#include "XUI_Engine.h"
#include "WifiScanner.h"

// User Interface Engine
XUI_Engine* xuiEng;
WifiScanner wifiScanner;
  
void promisc_cb(uint8 *buf, uint16 len){
  wifiScanner.sniffer(buf, len);
}

// Aplication screens
void setup() {

  Serial.begin(115200);
  
  wifi_set_promiscuous_rx_cb(promisc_cb);

  // init display engine
  XUI_Display* xuiDisplay = new XUI_Display();

  XUI_Screen* home = new XUI_ScreenMenu("Home", DISPLAY_LINES_3);

  xuiEng = new XUI_Engine(xuiDisplay, home);
  
  //Home options
  XUI_Screen* wifiAnalisis = new XUI_ScreenScan("Analysis", SCAN_MODE_AP, wifiScanner);
  home->addScreen(wifiAnalisis);
  XUI_Screen* wifiAtacks = new XUI_ScreenMenu("Atack", DISPLAY_LINES_3);
  home->addScreen(wifiAtacks);
    XUI_Screen* Scan = new XUI_ScreenScan("Scan", SCAN_MODE_ALL, wifiScanner);
    wifiAtacks->addScreen(Scan);
  XUI_Screen* nearDetection = new XUI_ScreenMenu("Radar", DISPLAY_LINES_3);
  home->addScreen(nearDetection);
  XUI_Screen* pwdVault = new XUI_ScreenMenu("PWD Vault", DISPLAY_LINES_3);
  home->addScreen(pwdVault);

/*
  XUI_Screen* options = new XUI_ScreenMenu("Options", DISPLAY_LINES_5);
  home->addScreen(options);
    options->addScreen(new XUI_ScreenFonts("Fonts"));
    options->addScreen(new XUI_Screen("Option1"));
    options->addScreen(new XUI_Screen("Option2"));
    options->addScreen(new XUI_Screen("Option3"));
    options->addScreen(new XUI_Screen("Option4"));
    options->addScreen(new XUI_Screen("Option5"));
    options->addScreen(new XUI_Screen("Option6"));
*/

}

void loop() {
    xuiEng->run();
}