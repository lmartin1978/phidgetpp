#ifndef HUMIDITY_HH
#define HUMIDITY_HH
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"

class HumiditySensor : public PhidgetPP
/*! \brief Class for the Humidity Sensor Phidget
 *
 *Class interfaces with the C API for the Humidity Sensor Phidget (HUM1000_0). It is recommended to define
 *all devices in a namespace above the main function.
 */
{
public:
  HumiditySensor(int hub_port = -1, int serialNumber = 0);
  ~HumiditySensor();

  /*! @brief Get humidity measurement
   *
   * returns the current humidity percentage measured by the sensor
   */
  double GetHumidity();

  /*! @brief Get threshold for callback
   *
   * Returns the minimum change in humidity needed to trigger a change in value event. Default is set to 0
   */
  double GetHumidityChangeTrigger();

  /*! @brief Set threshold for callback
   *
   * Sets the minimum change in measurement needed to trigger a change in value event.
   * Default is set to 0.0 units.
   */
  int SetHumidityChangeTrigger(double newValueChangeTrigger);

  /*! @brief Set humidity change callback
   *
   * Sets the function to be called when a humdity change event is
   * triggered. It is recommended that tempChangeFunc is defined after
   * the devices namespace in the main file.
   */
  PhidgetReturnCode SetHumidityChangeFunc(PhidgetHumiditySensor_OnHumidityChangeCallback tempChangeFunc);

private:
  PhidgetHumiditySensorHandle handle;
  double valueChangeTrigger;
  double humidityValue;
  uint32_t newValue;
};
#endif

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
