#include <iostream>
#include <phidget22.h>
#include <string>

class FreqCounter
/*! \brief Class for the Frequency Counter Phidget
 *
 * Class interfaces with the C API for the FrequencyCounter Phidget (1054_0B). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
    FreqCounter(int serialNumber = 0){
      /*!
      * Constructor sets the serial number if defined and attempts to connect
      * to the device.Serial Numbers are needed for identification when
      * connecting multiple identical devices
      */
        status = PhidgetFrequencyCounter_create(&handle);
        if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);

        if(AllGood()){
            status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
        } else {
          Phidget_getErrorDescription(GetError(),&errorChar);
          std::cerr << "Frequency Counter Constructor Error:" << errorChar << std::endl;
        }
    }

    ~FreqCounter(){
      /*!
      * Destructor disconnects the device and deletes the handle
      *
      *
      */
        Phidget_close((PhidgetHandle)handle);
        PhidgetFrequencyCounter_delete(&handle);
    }

    bool AllGood(){
      /*!
      *Confirms if the phidget status is okay
      */
        return status == EPHIDGET_OK;
    }

    PhidgetReturnCode GetError(){
      /*!
      *Returns the status of the phidget
      */
        return status;
    }
    std::string GetErrorCode(){
      /*!
      *Returns the description of the status of the phidget
      */
      Phidget_getErrorDescription(GetError(),&errorChar);
      std::string errorString(errorChar);
      return errorString;
    }

    uint32_t GetDataInterval(){
      /*!
      *Returns the minimum time that must elapse before another data event is fired
      *units of ms.
      */
      status = Phidget_getDataInterval((PhidgetHandle)handle, &dataInterval);
      return dataInterval;
    }

    PhidgetReturnCode SetDataInterval(uint32_t newValue){
      /*!
      *Sets the minimum time that must elapse before another data event is fired
      *units of ms.
      */
      status = Phidget_getDataInterval((PhidgetHandle)handle, &dataInterval);
      dataInterval = GetDataInterval();
      return status;
    }

    double GetFreq(){
      /*!
      *Returns the current value of the frequency measured
      */
        status = PhidgetFrequencyCounter_getFrequency(handle, &freq);
        if(status == EPHIDGET_OK)
            return freq;
        else
            return -999999.;
                                                                                                                                                                                    PhidgetFrequencyCounter_delete(&handle);
    }

    PhidgetReturnCode SetFrequencyChangeFunc(PhidgetFrequencyCounter_OnFrequencyChangeCallback freqChangeFunc){
      /*!
      *Sets the function to be called once the frequency changes, note it is
      *ideal to define the function in the main file.
      */
      status = PhidgetFrequencyCounter_setOnFrequencyChangeHandler(handle,freqChangeFunc,NULL);
      return status;
    }

    PhidgetReturnCode SetFreqCutoff(double newFreq){
      /*!
      *Sets the minimum reportable frequency. Any frequency at or below this value
      *will be reported as 0 Hz. It is set to 1 Hz by default
      */
      status = PhidgetFrequencyCounter_setFrequencyCutoff(handle, newFreq);
      freqCutoff = GetFreqCutoff();
      return status;
    }
    double GetFreqCutoff(){
      /*!
      *Returns the minimum reportable frequency. Any frequency at or below this value
      *will be reported as 0 Hz. It is set to 1 Hz by default
      */
      status = PhidgetFrequencyCounter_getFrequencyCutoff(handle, &freqCutoff);
      return freqCutoff;
    }




private:
    PhidgetFrequencyCounterHandle handle;
    double freq;
    PhidgetReturnCode status;
    uint32_t dataInterval;
    const char* errorChar;
    double freqCutoff;
};

