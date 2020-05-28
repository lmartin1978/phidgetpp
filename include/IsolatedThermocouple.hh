#ifndef ISOLTC_HH
#define ISOLTC_HH
#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"

class IsolatedThermocouple : public PhidgetPP
/*! \brief Class for the Isolated Thermocouple Phidget
 *
 * Class interfaces with the C API for the Isolated Thermocouple (TMP1100_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  IsolatedThermocouple(int serialNumber = 0);
  ~IsolatedThermocouple();

  /*! @brief Get the measured temperature
    *
    */
  double GetTemp();

  /*! @brief Get threshold for callback
    *
    * Returns the minimum threshold to trigger a change in temperature event.
    * Default value is 0.0 units
    */
  double GetTempChangeTrigger();

  /*! @brief Set threshold for callback
    *
    * Sets the minimum threshold to trigger a change in temperature event.
    * Default value is 0.0 units
    */
  PhidgetReturnCode SetTempChangeTrigger(double newTempChangeTrigger);

  /*! @brief Set callback function
    *
    * Sets the function that will be called when a temperature change event occurs
    */
  PhidgetReturnCode SetTempChangeFunc(PhidgetTemperatureSensor_OnTemperatureChangeCallback tempChangeFunc);

private:
  PhidgetTemperatureSensorHandle handle;
  double temperature;
  double tempChangeTrigger;
};
#endif