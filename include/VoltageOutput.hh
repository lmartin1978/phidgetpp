#ifndef VOUT_HH
#define VOUT_HH
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"

class VoltageOutput : public PhidgetPP
/*! \brief Class for the Isolated Voltage Output phidget
 *
 *Class interfaces with the C API for the Isolated Voltage Output (OUT1001_0). It is recommended to define
 *all devices in a namespace above the main function. Still need to implement software voltage limits
 */
{
public:
  /*! @brief Constructor
   * Constructor sets the hub port and serial number if defined and attempts to connect to
   * the device. Serial Numbers are needed for identification when connecting
   * multiple identical devices.
   * 
   * The output range by default used is VOLTAGE_OUTPUT_RANGE_5V.
   * The other choice for output range is VOLTAGE_OUTPUT_RANGE_10V.
   */
  VoltageOutput(int hub_port = -1, int serialNumber = 0,
                PhidgetVoltageOutput_VoltageOutputRange outputRange = VOLTAGE_OUTPUT_RANGE_5V);

  ~VoltageOutput();

  /*! @brief Returns the currently set voltage value
   *
   */
  double GetVoltage();

  /*! @brief Set new output voltage
   *
   * Sets the new value of voltage between the limits of the Phidget and this class
   */
  double SetVoltage(double newVoltage);

  /** @brief Set software lower limit on output voltage
   * 
   */
  int setLowerVoltageBound(double lowerBound);

  /** @brief Get software lower limit on voltage
   * 
   */
  double getLowerVoltageBound();

  /** @brief Deactivates software lower limit
   * 
   */
  int removeLowerVoltageBound();

  /** @brief Set software upper limit on output voltage
   * 
   */
  int setUpperVoltageBound(double upperBound);

  /** @brief Get software upper limit on voltage
   * 
   */
  double getUpperVoltageBound();

  /** @brief Deactivates software lower limit
   * 
   */
  int removeUpperVoltageBound();

private:
  double bounds[2] = {-9999., 9999.};
  double hwbounds[2];
  PhidgetVoltageOutputHandle handle;
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
