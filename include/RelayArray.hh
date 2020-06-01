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
  RelayArray(int nch, int hub_port, int serialNumber = 0);

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

private:
  std::vector<DigitalOutput> channels;
  uint32_t dataInterval;
};
