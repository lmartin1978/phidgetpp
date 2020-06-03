#ifndef VRATIOS_HH
#define VRATIOS_HH
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"

class VoltageRatioSensor : public PhidgetPP
/*! \brief Class for the VoltageRatioSensor Phidget
 *
 * Class interfaces with the C API for the Voltage Ratio Sensor on the hub (HUB1000_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  /*! @brief Constructor
   *
   * Constructor sets the sensor type, which is used for readout conversion
   */
  VoltageRatioSensor(int hub_port = -1, PhidgetVoltageRatioInput_SensorType stype = SENSOR_TYPE_VOLTAGERATIO,
                     int serialNumber = 0, bool hubPortDevice = true);

  ~VoltageRatioSensor();

  /*! @brief Get voltage ratio
   *
   * Direct voltage ratio, 0 to 1.
   */
  double GetVoltageRatio();
  
  /*! @brief Get sensor value
   *
   * Voltage ratio is converted to sensor value for sensor type.
   * Use GetUnit() to read back sensor unit.
   */
  double GetValue();

  /*! @brief Returns the unit information for the quantity being measured
   *
   */
  const char *GetUnit();

  /*! @brief Get callback trigger threshold
   *
   * Returns the minimum change in measurement needed to trigger a change in value event. Default is set to 0 sensor units.
   */
  double GetSensorValueChangeTrigger();

  /*! @brief Set callback trigger threshold
   *
   * Sets the minimum change in measurement needed to trigger a change in value event. Default is set to 0 sensor units.
   */
  int SetSensorValueChangeTrigger(double newValueChangeTrigger);

  /*! @brief Set callback function
   *
   * Sets the function to be called when a voltage ratio change event is
   * triggered. It is recommended that tempChangeFunc is defined after
   * the devices namespace in the main file.
   */
  PhidgetReturnCode SetSensorValueChangeFunc(PhidgetVoltageRatioInput_OnSensorChangeCallback tempChangeFunc);

private:
  PhidgetVoltageRatioInputHandle handle;
  PhidgetVoltageRatioInput_SensorType sensorType;
  double sensorValue, vRatio;
  double valueChangeTrigger;
  Phidget_UnitInfo sensorUnit;
};

#endif
/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
