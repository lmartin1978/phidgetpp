#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>

class HumiditySensor
/*! \brief Class for the Humidity Sensor Phidget
 *
 *Class interfaces with the C API for the Humidity Sensor Phidget (HUM1000_0). It is recommended to define
 *all devices in a namespace above the main function.
 */
{
public:
    HumiditySensor(int hub_port = -1, int serialNumber = 0){
      /*!
      * Constructor sets the serial number and sensor type if defined and
      *attempts to connect to the device.
      */
        status = PhidgetHumiditySensor_create(&handle);
        hubPort = hub_port;
        status = Phidget_setIsHubPortDevice((PhidgetHandle)handle, int(hubPort >= 0));
        if(hubPort >= 0) status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
        if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);


        if(AllGood()){
            status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
        } else {
            std::cerr << "Hmm. " << GetError() << std::endl;
        }
    }
    ~HumiditySensor(){
      /*!
      * Destructor disconnects the device and deletes the handle
      */
         Phidget_close((PhidgetHandle)handle);
         PhidgetHumiditySensor_delete(&handle);
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

     double GetHumidity(){
       /*!
       * returns the current humidity percentage measured by the sensor
       */
         status = PhidgetHumiditySensor_getHumidity(handle, &humidityValue);
         if(status == EPHIDGET_OK)
             return humidityValue;
         else
             return -999999.;
      }

      double GetHumidityChangeTrigger(){
        /*!
        * Returns the minimum change in humidity needed to trigger a change in value event. Default is set to 0
        */
        status = PhidgetHumiditySensor_getHumidityChangeTrigger(handle, &valueChangeTrigger);
        if(status == EPHIDGET_OK)
            return valueChangeTrigger;
        else
            return -999999.;
      }

      int SetHumidityChangeTrigger(double newValueChangeTrigger){
        /*!
        * Sets the minimum change in measurement needed to trigger a change in value event.
        * Default is set to 0.0 units.
        */
        status = PhidgetHumiditySensor_setHumidityChangeTrigger(handle, newValueChangeTrigger);
        if(status == EPHIDGET_OK)
            return 1;
        else
            return 0.;
      }

      PhidgetReturnCode SetHumidityChangeFunc(PhidgetHumiditySensor_OnHumidityChangeCallback tempChangeFunc){
        /*!
        * Sets the function to be called when a humdity change event is
        * triggered. It is recommended that tempChangeFunc is defined after
        * the devices namespace in the main file.
        */
        status = PhidgetHumiditySensor_setOnHumidityChangeHandler(handle, tempChangeFunc, NULL);
        return status;
      }

       uint32_t GetDataInterval(){
    /*!
    *Returns the minimum time that must elapse before another data event is fired
    */
    status = Phidget_getDataInterval((PhidgetHandle)handle, &dataInterval);
    return dataInterval;
  }

  PhidgetReturnCode SetDataInterval(uint32_t newValue){
    /*!
    *Sets the minimum time that must elapse before another data event is fired
    *Units of ms.
    */
    status = Phidget_getDataInterval((PhidgetHandle)handle, newValue);                                                                               dataInterval = GetDataInterval();
    return status;
  }
     private:
         PhidgetHumiditySensorHandle handle;
         int hubPort;
         double valueChangeTrigger;
         double humidityValue;
         PhidgetReturnCode status;
         uint32_t newValue;
};

