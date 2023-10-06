#include "WifiScanner.h"
#include "ESP8266WiFi.h"

 WifiScanner::WifiScanner(){
  //  WiFi.mode(WIFI_OFF);
  //  wifi_set_opmode(STATION_MODE);

 }
 
  void WifiScanner::startScan(bool async, bool show_hidden){
    wifi_promiscuous_enable(false);
    WiFi.scanNetworks(async, show_hidden);
  }

  void WifiScanner::runScan(){
    this->APCount = WiFi.scanComplete();
  }

 void WifiScanner::startSniff(){
  wifi_promiscuous_enable(true);
 }

 uint8_t WifiScanner::runSniff(){
   return stations.size();
 }

 void WifiScanner::setChannel(uint8_t channel){
    wifi_set_channel(channel);
 }

 void WifiScanner::stopSniff(){
   wifi_promiscuous_enable(false);
 }

 void WifiScanner::sniffer(uint8_t* buf, uint16_t len) {

    packetCount++;

    if (len < 28) return;  // drop frames that are too short to have a valid MAC header

    if ((buf[12] == 0xc0) || (buf[12] == 0xa0)) {
        deauths++;
        return;
    }

    // drop beacon frames, probe requests/responses and deauth/disassociation frames
    if ((buf[12] == 0x80) || (buf[12] == 0x40) || (buf[12] == 0x50) /* || buf[12] == 0xc0 || buf[12] == 0xa0*/) return;

    // only allow data frames
    // if(buf[12] != 0x08 && buf[12] != 0x88) return;

    uint8_t* macTo   = &buf[16];
    uint8_t* macFrom = &buf[22];

    if (macBroadcast(macTo) || macBroadcast(macFrom) || !macValid(macTo) || !macValid(macFrom) || macMulticast(macTo) ||
        macMulticast(macFrom)) return;

    int accesspointIndex = findAccesspoint(macFrom);

    if (accesspointIndex >= 0) {
        addStation(macTo, accesspointIndex);
    } else {
        accesspointIndex = findAccesspoint(macTo);

        if (accesspointIndex >= 0) {
            addStation(macFrom, accesspointIndex);
        }
    }
}

void WifiScanner::addStation(uint8_t* mac, int accesspointNum) {

    Station newStation;

    newStation.ap       = accesspointNum;
    newStation.ch       = wifi_get_channel();
    newStation.mac      = (uint8_t*)malloc(6);

    memcpy(newStation.mac, mac, 6);

    stations.push_back(&newStation);
}

int WifiScanner::findAccesspoint(uint8_t* mac) {
    for (int i = 0; i < this->APCount; i++) {
        if (memcmp(WiFi.BSSID(i), mac, 6) == 0) return i;
    }
    return -1;
}

bool WifiScanner::macBroadcast(uint8_t* mac) {
    for (uint8_t i = 0; i < 6; i++)
        if (mac[i] != broadcast[i]) return false;

    return true;
}

bool WifiScanner::macValid(uint8_t* mac) {
    for (uint8_t i = 0; i < 6; i++)
        if (mac[i] != 0x00) return true;

    return false;
}

bool WifiScanner::macMulticast(uint8_t* mac) {
    // see https://en.wikipedia.org/wiki/Multicast_address
    if ((mac[0] == 0x33) && (mac[1] == 0x33)) return true;

    if ((mac[0] == 0x01) && (mac[1] == 0x80) && (mac[2] == 0xC2)) return true;

    if ((mac[0] == 0x01) && (mac[1] == 0x00) && ((mac[2] == 0x5E) || (mac[2] == 0x0C))) return true;

    if ((mac[0] == 0x01) && (mac[1] == 0x0C) && (mac[2] == 0xCD) &&
        ((mac[3] == 0x01) || (mac[3] == 0x02) || (mac[3] == 0x04)) &&
        ((mac[4] == 0x00) || (mac[4] == 0x01))) return true;

    if ((mac[0] == 0x01) && (mac[1] == 0x00) && (mac[2] == 0x0C) && (mac[3] == 0xCC) && (mac[4] == 0xCC) &&
        ((mac[5] == 0xCC) || (mac[5] == 0xCD))) return true;

    if ((mac[0] == 0x01) && (mac[1] == 0x1B) && (mac[2] == 0x19) && (mac[3] == 0x00) && (mac[4] == 0x00) &&
        (mac[5] == 0x00)) return true;

    return false;
}