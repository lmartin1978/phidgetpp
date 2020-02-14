#include <iostream>
#include <phidget22.h>
#include <string>

class IsolatedThermocouple
/*! \brief Class for the Isolated Thermocouple Phidget
 *
 * Class interfaces with the C API for the Isolated Thermocouple (TMP1100_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  IsolatedThermocouple(int serialNumber = 0){
    /*!
    * Constructor sets the serial number if defined and attempts to connect to
    * the device. Serial Numbers are needed for identification when connecting 
    * multiple identical devices.
    */
    status = PhidgetTemperatureSensor_create(&handle);
    if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);

    if(AllGood()){
        status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
    } else {
      Phidget_getErrorDescription(GetError(),&errorChar);
      std::cerr << "Thermocouple Constructor Error:" << errorChar << std::endl;
    }
  }
  ~IsolatedThermocouple(){
    /*!
    * Destructor disconnects the device and delets the handle
    */
    Phidget_close((PhidgetHandle)handle);
    PhidgetTemperatureSensor_delete(&handle);
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
    status = Phidget_setDataInterval((PhidgetHandle)handle,newValue);
    dataInterval = GetDataInterval();
    return status;
  }

  double GetTemp(){
    /*!
    *Returns the current temperature measured by the phidget
    */
    status = PhidgetTemperatureSensor_getTemperature(handle, &temperature);
    if(status == EPHIDGET_OK)
      return temperature;
    else
      return -999999.;
  }

  double GetTempChangeTrigger(){
    /*!
    * Returns the minimum threshold to trigger a change in temperature event.
    * Default value is 0.0 units
    */
    status = PhidgetTemperatureSensor_getTemperatureChangeTrigger(handle,&tempChangeTrigger);
    return tempChangeTrigger;
  }

  PhidgetReturnCode SetTempChangeTrigger(double newTempChangeTrigger){
    /*!
    * Sets the minimum threshold to trigger a change in temperature event.
    * Default value is 0.0 units
    */
    status = PhidgetTemperatureSensor_getTemperatureChangeTrigger(handle,&newTempChangeTrigger);
    return status;
    }

  PhidgetReturnCode SetTempChangeFunc(PhidgetTemperatureSensor_OnTemperatureChangeCallback tempChangeFunc){
    /*!
    * Sets the function that will be called when a temperature change event occurs
    */
    status = PhidgetTemperatureSensor_setOnTemperatureChangeHandler(handle, tempChangeFunc, NULL);
    return status;
  }

private:
  PhidgetTemperatureSensorHandle handle;
  double temperature;
  double tempChangeTrigger;
  PhidgetReturnCode status;
  uint32_t dataInterval;
  const char* errorChar;
};

