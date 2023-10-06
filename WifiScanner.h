#pragma once

#include "Arduino.h"
#include <vector>
using std::vector;


class WifiScanner{
  public:
    WifiScanner();
    void start();
    uint8_t run();
    void setChannel(uint8_t channel);
    void stop();
    void startScan(bool async, bool show_hidden);
    void runScan();
    void startSniff();
    uint8_t runSniff();
    void stopSniff();
    void sniffer(uint8_t* buf, uint16_t len);
    uint8_t APCount = 0;
  private:
    void addStation(uint8_t* mac, int accesspointNum);
    int findAccesspoint(uint8_t* mac);
    bool macBroadcast(uint8_t* mac);
    bool macValid(uint8_t* mac);
    bool macMulticast(uint8_t* mac);
    
    uint8_t broadcast[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

    struct Station {
        uint8_t   ap;
        uint8_t   ch;
        uint8_t * mac;
    };
    vector<Station*> stations;
    vector<uint16_t*> packets;
    uint16_t deauths = 0;
    uint16_t packetCount = 0;

    int STACount = 0;

};