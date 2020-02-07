#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>


class VoltageInput
/*! \brief Class for the Voltage Input Capabilities on the HUB phidget
 *
 * Class interfaces with the C API for the Voltage Input on the HUB phidget(HUB0000_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
  VoltageInput(int hub_port = -1,int serialNumber = 0){
    /*!
    * Constructor function assigns the hub port and serial number if defined
    * and attempts to connect to the device. Serial Numbers are needed for
    * identification when connecting multiple identical devices.
    */
    status = PhidgetVoltageInput_create(&handle);
    hubPort = hub_port;
    status = Phidget_setIsHubPortDevice((PhidgetHandle)handle, int(hubPort >= 0));
    if(hubPort >= 0) status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
    if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);
    if(AllGood()){
        status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
    } else {
      Phidget_getErrorDescription(GetError(),&errorChar);
      std::cerr << "Voltage Input Constructor Error:" << errorChar << std::endl;
    }
  }

  ~VoltageInput(){
    Phidget_close((PhidgetHandle)handle);
    PhidgetVoltageInput_delete(&handle);
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
    status = Phidget_getDataInterval((PhidgetHandle)handle, &dataInterval);
    dataInterval = GetDataInterval();
    return status;
  }

  double GetVoltage(){
    /*!
    *Returns the current voltage value being measured
    */
    status = PhidgetVoltageInput_getVoltage(handle,&voltage);
    if(status == EPHIDGET_OK)
      return voltage;
    else
      return -999999.;


  }

  double GetVoltageValueChangeTrigger(){
    /*!
    *Gets the current threshold of change required to trigger an on voltage change
    *event. Default value is 0.0 V
    */
    status = PhidgetVoltageInput_getVoltageChangeTrigger(handle, &valueChangeTrigger);
    if(status == EPHIDGET_OK)
        return valueChangeTrigger;
    else
        return -999999.;
  }

  int SetVoltageValueChangeTrigger(double newValueChangeTrigger){
    /*!
    *Sets the current threshold of change required to trigger an on voltage change
    *event. Default value is 0.0 V
    */
    status = PhidgetVoltageInput_setVoltageChangeTrigger(handle, newValueChangeTrigger);
    if(status == EPHIDGET_OK)
        return 1;
    else
        return 0.;
  }

  PhidgetReturnCode setVoltageValueChangeFunc(PhidgetVoltageInput_OnVoltageChangeCallback tempChangeFunc){
    /*!
    * Sets the function to be called when a voltage change event occurs. Recommended that this function
    * is defined in the main c++ file.
    */
    status = PhidgetVoltageInput_setOnVoltageChangeHandler(handle, tempChangeFunc, NULL);
    return status;
  }

private:


  double valueChangeTrigger;
  int hubPort;
  PhidgetVoltageInputHandle handle;
  double voltage;
  PhidgetReturnCode status;
  uint32_t dataInterval;
  const char* errorChar;
};

