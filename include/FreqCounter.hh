#ifndef FREQCOUNTER_HH
#define FREQCOUNTER_HH
#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"

class FreqCounter: public PhidgetPP
/*! \brief Class for the Frequency Counter Phidget
 *
 * Class interfaces with the C API for the FrequencyCounter Phidget (1054_0B). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
      /*! @brief Constructor
      *
      * Constructor sets the serial number if defined and attempts to connect
      * to the device. Serial Numbers are needed for identification when
      * connecting multiple identical devices.
      */
    FreqCounter(int hub_port = -1, int serialNumber = 0, bool hubPortDevice = false);
    ~FreqCounter(); ///< Destructor

    double GetFreq(); ///< Get measured frequency

      /*! @brief Set frequency change callback
      *
      * Sets the function to be called once the frequency changes, note it is
      * ideal to define the function in the main file.
      */
    PhidgetReturnCode SetFrequencyChangeFunc(PhidgetFrequencyCounter_OnFrequencyChangeCallback freqChangeFunc, void *ctx = NULL);

      /*! @brief Set low frequency reporting threshold
      *
      * Sets the minimum reportable frequency. Any frequency at or below this value
      * will be reported as 0 Hz. It is set to 1 Hz by default
      */
    PhidgetReturnCode SetFreqCutoff(double newFreq);

      /*! @brief Get low frequency reporting threshold
      *
      * Sets the minimum reportable frequency. Any frequency at or below this value
      * will be reported as 0 Hz. It is set to 1 Hz by default
      */
    double GetFreqCutoff();

private:
    PhidgetFrequencyCounterHandle handle;
    double freq;
    double freqCutoff;
};

#endif
/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
