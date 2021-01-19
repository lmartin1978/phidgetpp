#ifndef TEMPSENS_HH
#define TEMPSENS_HH
#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"

class TemperatureSensor : public PhidgetPP
/*! \brief Class for the Isolated Thermocouple Phidget
 *
 * Class interfaces with the C API for the Isolated Thermocouple (TMP1100_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  TemperatureSensor(int hub_port = -1, int serialNumber = 0, bool netServer = false);
  ~TemperatureSensor();

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
  PhidgetReturnCode SetTempChangeFunc(PhidgetTemperatureSensor_OnTemperatureChangeCallback tempChangeFunc, void *ctx = NULL);

  /** @brief Get minimum measurable temperature
   * 
   * Changes dependent on sensor type.
   */
  double GetMinTemp();

  /** @brief Get maximum measurable temperature
   * 
   * Changes dependent on sensor type.
   */
  double GetMaxTemp();
protected:
  PhidgetTemperatureSensorHandle handle;
private:
  double temperature;
  double tempChangeTrigger;
};
#endif
/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
