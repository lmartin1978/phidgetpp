#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>

class VoltageRatioSensor
/*! \brief Class for the VoltageRatioSensor Phidget
 *
 * Class interfaces with the C API for the Voltage Ratio Sensor on the hub (HUB1000_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
    VoltageRatioSensor(int hub_port = -1, PhidgetVoltageRatioInput_SensorType stype = SENSOR_TYPE_VOLTAGERATIO, int serialNumber = 0, bool active = false){
      /*!
      * Constructor sets the serial number and sensor type if defined and
      * attempts to connect to the device. Serial Numbers are needed for identification
      * when connecting multiple identical devices.
      */
        status = PhidgetVoltageRatioInput_create(&handle);
        hubPort = hub_port;
        sensorType = stype;
        status = Phidget_setIsHubPortDevice((PhidgetHandle)handle, int(hubPort >= 0));
        if(hubPort >= 0) status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
        if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);


        if(AllGood()){
            status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
            PhidgetVoltageRatioInput_setSensorType(handle, sensorType);
            PhidgetVoltageRatioInput_getSensorUnit(handle, &sensorUnit);
        } else {
          Phidget_getErrorDescription(GetError(),&errorChar);
          std::cerr << "Voltage Ratio Sensor Constructor Error:" << errorChar << std::endl;
        }
    }
    ~VoltageRatioSensor(){
      /*!
      * Destructor disconnects the device and deletes the handle
      */
         Phidget_close((PhidgetHandle)handle);
         PhidgetVoltageRatioInput_delete(&handle);
     }

     bool AllGood(){
       /*!
       *Confirms if the phidget status is okay
       *
       */
         return status == EPHIDGET_OK;
     }

     PhidgetReturnCode GetError(){
       /*!
       *Returns the status of the phidget
       *
       */
         return status;
     }

     double GetValue(){
       /*!
       * returns the current value measured by the sensor
       */
         status = PhidgetVoltageRatioInput_getSensorValue(handle, &sensorValue);
         if(status == EPHIDGET_OK)
             return sensorValue;
             else
                 return -999999.;
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
        */
        status = Phidget_getDataInterval((PhidgetHandle)handle, &dataInterval);
        return dataInterval;
      }

      PhidgetReturnCode SetDataInterval(uint32_t newValue){
        /*!
        *Sets the minimum time that must elapse before another data event is fired
        *Units of ms.
        */
        status = Phidget_setDataInterval((PhidgetHandle)handle, newValue);
        dataInterval = GetDataInterval();
        return status;
      }

      const char * GetUnit(){
        /*!
        * returns the unit information for the quantity being measured
        */
        return sensorUnit.symbol;
      }

      double GetSensorValueChangeTrigger(){
        /*!
        * Returns the minimum change in measurement needed to trigger a change in value event. Default is set to 0
        */
        status = PhidgetVoltageRatioInput_getSensorValueChangeTrigger(handle, &valueChangeTrigger);
        if(status == EPHIDGET_OK)
            return valueChangeTrigger;
        else
            return -999999.;
      }

      int SetSensorValueChangeTrigger(double newValueChangeTrigger){
        /*!
        * Sets the minimum change in measurement needed to trigger a change in value event.
        * Default is set to 0.0 units.
        */
        status = PhidgetVoltageRatioInput_setSensorValueChangeTrigger(handle, newValueChangeTrigger);
        if(status == EPHIDGET_OK)
            return 1;
        else
            return 0.;
      }

      PhidgetReturnCode SetSensorValueChangeFunc(PhidgetVoltageRatioInput_OnSensorChangeCallback tempChangeFunc){
        /*!
        * Sets the function to be called when a voltage ratio change event is
        * triggered. It is recommended that tempChangeFunc is defined after
        * the devices namespace in the main file.
        */
        status = PhidgetVoltageRatioInput_setOnSensorChangeHandler(handle, tempChangeFunc, NULL);
        return status;
      }


      private:
        PhidgetVoltageRatioInputHandle handle;
        PhidgetVoltageRatioInput_SensorType sensorType;
        double sensorValue;
        int hubPort;
        double valueChangeTrigger;
        Phidget_UnitInfo sensorUnit;
        PhidgetReturnCode status;
        uint32_t dataInterval;
        const char* errorChar;
};

