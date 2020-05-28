#include <iostream>
#include <cassert>
#include <stdio.h>
#include <vector>
#include <phidget22.h>
#include "Phidget.hh"
#include "DigitalOutput.hh"

// FIXME: This is really 4 phidgets, so should probably be defined as a vector of single relays...
class RelayArray
{
public:
  RelayArray(int nch, int hub_port,int serialNumber = 0){
    for (int i = 0; i < nch;i++){
      channels.emplace_back(hub_port, serialNumber, i);
    }

    if(!AllGood()){
      std::cerr << "Relay Constructor Errors:" << std::endl;
      for(DigitalOutput &ch: channels){
        std::cerr << ch.GetChannel() << ":\t" << ch.GetErrorCode() << std::endl;
      }
    }
  }

  bool AllGood(){
    /*!
    *Confirms if the phidget status is okay
    *
    */
    bool status = true;
    for(DigitalOutput &ch: channels){
      status &= ch.AllGood();
    }
    return status;
  }

  uint32_t GetDataInterval(){
    /*!
    *Returns the minimum time that must elapse before another data event is fired
    */
    for(DigitalOutput &ch: channels){
      dataInterval = ch.GetDataInterval();
    }
    return dataInterval;
  }

  PhidgetReturnCode SetDataInterval(uint32_t newValue){
    /*!
    *Sets the minimum time that must elapse before another data event is fired
    *Units of ms.
    */
    PhidgetReturnCode status = EPHIDGET_OK;
    for(DigitalOutput &ch: channels){
      PhidgetReturnCode stat = ch.SetDataInterval(newValue);
      if(stat != EPHIDGET_OK) status = stat;
    }
    dataInterval = GetDataInterval();
    return status;
  }

  int GetState(int channel){
    /*!
    * Returns the current state of one channel
    */
   return channels[channel].GetState();
  }

  PhidgetReturnCode SetState(int channel,int newState){
  /*!
  * Changes the state of a single channel
  */
    return channels[channel].SetState(newState);
  }
private:
  std::vector<DigitalOutput> channels;
  uint32_t dataInterval;
};

