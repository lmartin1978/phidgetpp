#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>

class RelayFour
/*! \brief Class for the 4x Relay Phidget
 *
 *Class interfaces with the C API for the 4x Relay (REL1000_0). It is recommended to define
 *all devices in a namespace above the main function.
 */
{
public:
  RelayFour(int hub_port,int serialNumber = 0){
    /*!
    * Constructor assigns the hub port and serial number if defined. Initializes
    * values for all 4 ports and attempts to open a connection for each port.
    * Serial Numbers are needed for identification when connecting multiple
    * identical devices.
    */
    hubPort = hub_port;
    for (int i = 0; i < 4;i++){
      if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle[i], serialNumber);
      status = PhidgetDigitalOutput_create(&(handle[i]));
      //status = Phidget_setIsHubPortDevice((PhidgetHandle)handle[i], int(hubPort >= 0));
      status = Phidget_setHubPort((PhidgetHandle)handle[i], hubPort);
      status = Phidget_setChannel((PhidgetHandle) handle[i],i);
    }

    if(AllGood()){
      for (int j = 0; j < 4;j++){
        status = Phidget_openWaitForAttachment((PhidgetHandle)handle[j], 5000);
      }
    } else {
      Phidget_getErrorDescription(GetError(),&errorChar);
      std::cerr << "Relay Constructor Error:" << errorChar << std::endl;
    }
  }

  ~RelayFour(){
    /*!
    * close the connections and deletes the handles for all ports
    */
    for (int k = 0; k < 4;k++){
      Phidget_close((PhidgetHandle)handle[k]);
      PhidgetDigitalOutput_delete(&(handle[k]));
    }
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
    for (int k = 0; k < 4;k++){
      status = Phidget_getDataInterval((PhidgetHandle)handle[k], &dataInterval);
    }
    return dataInterval;
  }

  PhidgetReturnCode SetDataInterval(uint32_t newValue){
    /*!
    *Sets the minimum time that must elapse before another data event is fired
    *Units of ms.
    */
    for (int k = 0; k < 4;k++){
      status = Phidget_setDataInterval((PhidgetHandle)handle[k], newValue);
    }
    dataInterval = GetDataInterval();
    return status;
  }

  double GetState(int channel){
    /*!
    * Returns the current state of one channel
    */
    status = PhidgetDigitalOutput_getState(handle[channel],&stateReport);
    if(status == EPHIDGET_OK)
      return stateReport;
    else
      return -999999.;
  }

  double SetState(int channel,int newState){
  /*!
  * Changes the state of a single channel
  */
    status = PhidgetDigitalOutput_setState(handle[channel],newState);
    return status;
  }
private:
  int hubPort;
  PhidgetDigitalOutputHandle handle[4];
  int stateReport;
  PhidgetReturnCode status;
  uint32_t dataInterval;
  const char* errorChar;
};

