#ifndef MAC_H
#define MAC_H

#include "linkData.h"
#include <string>
#include <vector>

class MACAddress : public LinkData
{
  public: //constants
  static const int MACAddressSize = 6;

  public: 
    MACAddress();
    MACAddress( uint8_t mac[MACAddressSize] );
    MACAddress( std::vector< uint8_t > mac );
    MACAddress( const MACAddress& a );
    MACAddress& operator=( const MACAddress &a );
    //TODO LATER: MACAddress( std::string mac );
    virtual ~MACAddress();

    void setMACAddress( std::vector< uint8_t > mac );
    //void setMACAddress( std::string mac );
    int getSize();
    std::vector< uint8_t > makePacket();
    void getMAC( uint8_t (&mac)[MACAddressSize]);//puts the mac address in the memory mac
    //TODO LATER: std::string getMAC();

  private:
    std::vector< uint8_t > mac_;
};
#endif
