#ifndef TC_HH
#define TC_HH
#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"
#include "TemperatureSensor.hh"

class Thermocouple : public TemperatureSensor
/*! \brief Class for the Isolated Thermocouple Phidget
 *
 * Class interfaces with the C API for the Isolated Thermocouple (TMP1100_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  Thermocouple(const int hub_port = -1, const int serialNumber = 0, bool netServer = false): TemperatureSensor(hub_port, serialNumber, netServer){}

  /** @brief Get type of thermocouple (J,K,E,T)
   * 
   */
  const char GetType();

  /** @brief Set type of thermocouple (J,K,E,T)
   * 
   * Set by PhidgetTemperatureSensor_ThermocoupleType
   */
  PhidgetReturnCode SetType(const PhidgetTemperatureSensor_ThermocoupleType type);

  /** @brief Set type of thermocouple (J,K,E,T)
   * 
   * Set by ID character
   * @param type J, K, E, or T
   */
  PhidgetReturnCode SetType(const char type);
private:
  PhidgetTemperatureSensor_ThermocoupleType tctype;
};
#endif

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
