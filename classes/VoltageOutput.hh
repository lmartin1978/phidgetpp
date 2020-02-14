#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>

class VoltageOutput
/*! \brief Class for the Isolated Voltage Output phidget
 *
 *Class interfaces with the C API for the Isolated Voltage Output (OUT1001_0). It is recommended to define
 *all devices in a namespace above the main function. Still need to implement software voltage limits
 */
{
public:
  VoltageOutput(int hub_port = -1,int serialNumber = 0,PhidgetVoltageOutput_VoltageOutputRange outputRange = VOLTAGE_OUTPUT_RANGE_5V){
    /*!
    * Constructor sets the hub port and serial number if defined and attempts to connect to
    * the device. Serial Numbers are needed for identification when connecting
    * multiple identical devices. The output range by default used is VOLTAGE_OUTPUT_RANGE_5V.
    * The other choice for output range is VOLTAGE_OUTPUT_RANGE_10V.
    */
    status = PhidgetVoltageOutput_create(&handle);
    hubPort = hub_port;
    status = PhidgetVoltageOutput_setVoltageOutputRange(handle, outputRange);
    if(hubPort >= 0) status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
    if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);

    if(AllGood()){
        status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
    } else {
      Phidget_getErrorDescription(GetError(),&errorChar);
      std::cerr << "Voltage Ratio Sensor Constructor Error:" << errorChar << std::endl;
    }
  }

  ~VoltageOutput(){
    /*!
    * Destructor disconnects the device and deletes the handle
    */
    Phidget_close((PhidgetHandle)handle);
    PhidgetVoltageOutput_delete(&handle);
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
    status = Phidget_getDataInterval((PhidgetHandle)handle, newValue);
    dataInterval = GetDataInterval();
    return status;
  }
  double GetVoltage(){
    /*!
    * Returns the current value of voltage measured
    */
    status = PhidgetVoltageOutput_getVoltage(handle,&voltage);
    if(status == EPHIDGET_OK)
      return voltage;
    else
      return -999999.;
  }
  double SetVoltage(double newVoltage){
    /*!
    * Sets the new value of voltage between the limits of the Phidget and this class
    */
    if(bounds[0] == 1 && newVoltage < boundVoltageValues[0]){
      std::cout << "Requested new voltage too low\n";
    } else if (bounds[1] == 1 && newVoltage > boundVoltageValues[1]){
      std::cout << "Requested new voltage too high\n";
    } else {
      status = PhidgetVoltageOutput_setVoltage(handle,newVoltage);
      if(status == EPHIDGET_OK){
        voltage = GetVoltage();
      }
    }
    return status;
  }

  int setLowerVoltageBound(double lowerBound){
    /*!
    * Toggles the existence of a lower bound and defines it
    */
    bounds[0] = 1;
    boundVoltageValues[0] = lowerBound;
    return 0;
  }
  double getLowerVoltageBound(){
    /*!
    * Returns the lower bound if it exists
    */
    if(bounds[0] == 1){
      return boundVoltageValues[0];
    }

    return -99999.9;
  }
  int removeLowerVoltageBound(){
    /*!
    * Sets the existence of a lower bound to false
    */
    bounds[0] = 0;
    return 0;
  }
  int setUpperVoltageBound(double upperBound){
    /*!
    * Toggles the existence of an upperr bound and defines it
    */
    bounds[1] = 1;
    boundVoltageValues[1] = upperBound;
    return 0;
  }
  double getUpperVoltageBound(){
    /*!
    * Returns the upper bound if it exists
    */
    if(bounds[1] == 1){
      return boundVoltageValues[1];
    }

    return -99999.9;
  }
  int removeUpperVoltageBound(){
    /*!
    * Sets the existence of a lower bound to false
    */
    bounds[1] = 0;
    return 0;
  }


private:
  int bounds[2] = {0,0};
  double boundVoltageValues[2] = {0,0};
  PhidgetVoltageOutputHandle handle;
  double voltage;
  PhidgetReturnCode status;
  uint32_t dataInterval;
  int hubPort;
  const char* errorChar;
};

