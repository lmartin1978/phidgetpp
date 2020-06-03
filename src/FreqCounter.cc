#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"
#include "FreqCounter.hh"

FreqCounter::FreqCounter(int serialNumber) : PhidgetPP(-1, serialNumber)
{
  status = PhidgetFrequencyCounter_create(&handle);
  phandle = (PhidgetHandle)handle;

  if (serialNumber)
    status = Phidget_setDeviceSerialNumber(phandle, serialNumber);

  if (AllGood())
  {
    status = Phidget_openWaitForAttachment(phandle, 5000);
  }
  else
  {
    std::cerr << "Frequency Counter Constructor Error:" << GetErrorCode() << std::endl;
  }
}

FreqCounter::~FreqCounter()
{
  /*!
      * Destructor disconnects the device and deletes the handle
      *
      *
      */
  Phidget_close(phandle);
  PhidgetFrequencyCounter_delete(&handle);
}

double FreqCounter::GetFreq()
{
  /*!
      *Returns the current value of the frequency measured
      */
  status = PhidgetFrequencyCounter_getFrequency(handle, &freq);
  if (status == EPHIDGET_OK)
    return freq;
  else
    return -999999.;
  PhidgetFrequencyCounter_delete(&handle);
}

PhidgetReturnCode FreqCounter::SetFrequencyChangeFunc(PhidgetFrequencyCounter_OnFrequencyChangeCallback freqChangeFunc)
{
  /*!
      *Sets the function to be called once the frequency changes, note it is
      *ideal to define the function in the main file.
      */
  status = PhidgetFrequencyCounter_setOnFrequencyChangeHandler(handle, freqChangeFunc, NULL);
  return status;
}

PhidgetReturnCode FreqCounter::SetFreqCutoff(double newFreq)
{
  /*!
      *Sets the minimum reportable frequency. Any frequency at or below this value
      *will be reported as 0 Hz. It is set to 1 Hz by default
      */
  status = PhidgetFrequencyCounter_setFrequencyCutoff(handle, newFreq);
  freqCutoff = GetFreqCutoff();
  return status;
}
double FreqCounter::GetFreqCutoff()
{
  /*!
      *Returns the minimum reportable frequency. Any frequency at or below this value
      *will be reported as 0 Hz. It is set to 1 Hz by default
      */
  status = PhidgetFrequencyCounter_getFrequencyCutoff(handle, &freqCutoff);
  return freqCutoff;
}
/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
