#include <iostream>
#include <cassert>
#include <stdio.h>
#include <vector>
#include <phidget22.h>
#include "Phidget.hh"
#include "DigitalOutput.hh"

class RelayArray
/*! \brief Class for the relay array phidgets
 *
 * Should work for all REL* Phidgets, since they are just arrays of DigitalOutputs.
 */
{
public:
   RelayArray(int nch, int hub_port, int serialNumber = 0, bool netServer = false);
   ~RelayArray();

   /*! @brief Checks status of all channels
    *
    */
   bool AllGood();

   /*! @brief Get data interval setting
    *
    * Returns the minimum time that must elapse before another data event is fired.
    * This assumes all channels have the same setting.
    */
   uint32_t GetDataInterval();

   /*! @brief Set data interval for all channels
    *
    *Sets the minimum time that must elapse before another data event is fired
    *Units of ms.
    */
   PhidgetReturnCode SetDataInterval(uint32_t newValue);

   /*! @brief Get state of one channel
    *
    */
   int GetState(int channel);

   /*! @brief Changes the state of a single channel
    *
    */
   PhidgetReturnCode SetState(int channel, int newState);

   /*! @brief Get states of all channels
    *
    */
   const std::vector<int> GetStates();

   /*! @brief Change the state of all channels
    *
    */
   PhidgetReturnCode SetStates(std::vector<int> newStates);

   const std::string GetErrorCode();

   const std::vector<std::string> GetErrorCodes();

private:
   std::vector<DigitalOutput*> channels;
   uint32_t dataInterval;
};

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
