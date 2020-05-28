#ifndef DIGIOUT_HH
#define DIGIOUT_HH
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"

class DigitalOutput: public PhidgetPP
/*! \brief Class for the Digital Output Capabilities on the HUB phidget
 *
 * Class interfaces with the C API for the Digital Output on the HUB phidget(HUB0000_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
    /** \brief Constructor
     * 
     * Parameters are passed on to Base class constructor
     */
    DigitalOutput(const int hub_port = -1,const int serialNumber = 0, const int channel = -1);

    /** \brief Destructor
     * 
     */
    ~DigitalOutput();

    /** \brief Returns the duty cycle of PWM mode (0..1)
     * 
     */
    double GetDutyCycle();

    /** \brief Sets the duty cycle of PWM mode (0..1)
     * 
     */
    PhidgetReturnCode SetDutyCycle(double newValue);

    /** \brief Returns the current state of the output
     * 
     */
    int GetState();

    /** \brief Sets the state of the output
     * 
     */
    PhidgetReturnCode SetState(int state);

private:
    PhidgetDigitalOutputHandle handle;
};
#endif