#include <iostream>
#include <cassert>
#include <stdio.h>
#include <vector>
#include <phidget22.h>
#include "Phidget.hh"
#include "DigitalOutput.hh"
#include "RelayArray.hh"

RelayArray::RelayArray(int nch, int hub_port, int serialNumber, bool netServer)
{
  for (int i = 0; i < nch; i++)
  {
     channels.push_back(new DigitalOutput(hub_port, serialNumber, i, false, netServer));
  }

  if (!AllGood())
  {
    std::cerr << "Relay Constructor Errors:" << std::endl;
    for (DigitalOutput *ch : channels)
    {
      std::cerr << ch->GetChannel() << ":\t" << ch->GetErrorCode() << std::endl;
    }
  }
}

RelayArray::~RelayArray(){
   for (DigitalOutput *ch : channels){
      delete ch;
   }
}

/*! @brief Checks status of all channels
  *
  */
bool RelayArray::AllGood()
{
  bool status = true;
  for (DigitalOutput *ch : channels)
  {
    status &= ch->AllGood();
  }
  return status;
}

/*! @brief Get data interval setting
  *
  * Returns the minimum time that must elapse before another data event is fired.
  * This assumes all channels have the same setting.
  */
uint32_t RelayArray::GetDataInterval()
{
  for (DigitalOutput *ch : channels)
  {
    dataInterval = ch->GetDataInterval();
  }
  return dataInterval;
}

/*! @brief Set data interval for all channels
    *
    *Sets the minimum time that must elapse before another data event is fired
    *Units of ms.
    */
PhidgetReturnCode RelayArray::SetDataInterval(uint32_t newValue)
{
  PhidgetReturnCode status = EPHIDGET_OK;
  for (DigitalOutput *ch : channels)
  {
    PhidgetReturnCode stat = ch->SetDataInterval(newValue);
    if (stat != EPHIDGET_OK)
      status = stat;
  }
  dataInterval = GetDataInterval();
  return status;
}

/*! @brief Get state of one channel
    *
    */
int RelayArray::GetState(int channel)
{
  return channels[channel]->GetState();
}

/*! @brief Changes the state of a single channel
  *
  */
PhidgetReturnCode RelayArray::SetState(int channel, int newState)
{
  return channels[channel]->SetState(newState);
}

const std::string RelayArray::GetErrorCode()
{
  std::string errorString = "No Error";
  for(DigitalOutput *ch : channels){
    if(!ch->AllGood()){
      errorString = ch->GetErrorCode();
      break;
    }
  }
  return errorString;
}

const std::vector<std::string> RelayArray::GetErrorCodes()
{
   std::vector<std::string> out;
  for(DigitalOutput *ch : channels){
     out.push_back(ch->GetErrorCode());
  }
  return out;
}
/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
