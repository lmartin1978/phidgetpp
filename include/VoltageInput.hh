#ifndef VOLTINP_HH
#define VOLTINP_HH
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"

class VoltageInput: public PhidgetPP
/*! \brief Class for the Voltage Input Capabilities on the HUB phidget
 *
 * Class interfaces with the C API for the Voltage Input on the HUB phidget(HUB0000_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  VoltageInput(int hub_port = -1,int serialNumber = 0, bool hubPortDevice = false);

  ~VoltageInput();

  /*! @brief Get measured voltage
  *
  */
  double GetVoltage();

    /*! @brief Get threshold for callback
    *
    *Gets the current threshold of change required to trigger an on voltage change
    *event. Default value is 0.0 V
    */
  double GetVoltageValueChangeTrigger();

    /*! @brief Set threshold for callback
    *
    *Sets the current threshold of change required to trigger an on voltage change
    *event. Default value is 0.0 V
    */
  int SetVoltageValueChangeTrigger(double newValueChangeTrigger);

    /*! @brief Set callback function
    *
    * Sets the function to be called when a voltage change event occurs. Recommended that this function
    * is defined in the main c++ file.
    */
  PhidgetReturnCode setVoltageValueChangeFunc(PhidgetVoltageInput_OnVoltageChangeCallback tempChangeFunc);

private:
  double valueChangeTrigger;
  PhidgetVoltageInputHandle handle;
  double voltage;
};
#endif
/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
