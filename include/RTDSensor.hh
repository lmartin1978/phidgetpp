#ifndef RTD_HH
#define RTD_HH
#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"
#include "TemperatureSensor.hh"

class RTDSensor : public TemperatureSensor
/*! \brief Class for the Isolated RTDSensor Phidget
 *
 * Class interfaces with the C API for the RTDSensor (TMP1200_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  /** @brief Get type of RTD
   * 
   * Types:
   * 0x1 RTD_TYPE_PT100_3850
   * 0x2 RTD_TYPE_PT1000_3850
   * 0x3 RTD_TYPE_PT100_3920
   * 0x4 RTD_TYPE_PT1000_3920
   */
  const PhidgetTemperatureSensor_RTDType GetType();

  /** @brief Set type of RTD
   * 
   * Types:
   * 0x1 RTD_TYPE_PT100_3850
   * 0x2 RTD_TYPE_PT1000_3850
   * 0x3 RTD_TYPE_PT100_3920
   * 0x4 RTD_TYPE_PT1000_3920
   */
  PhidgetReturnCode SetType(const PhidgetTemperatureSensor_RTDType type);

  /** @brief Get RTD wire mode
   * 
   * RTDs can operate in 2, 3, or 4 wire mode.
   */
  const unsigned short GetNWires();

  /** @brief Set RTD wire mode
   * 
   * RTDs can operate in 2, 3, or 4 wire mode.
   * @param wires Number of wires (2, 3, or 4)
   */
  PhidgetReturnCode SetNWires(const unsigned short nw);

private:
  PhidgetTemperatureSensor_RTDType rtdtype;
};
#endif
