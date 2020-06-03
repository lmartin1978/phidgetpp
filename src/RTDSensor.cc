#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"
#include "RTDSensor.hh"

const PhidgetTemperatureSensor_RTDType RTDSensor::GetType(){
  PhidgetTemperatureSensor_getRTDType(handle, &rtdtype);
  return rtdtype;
}

PhidgetReturnCode RTDSensor::SetType(const PhidgetTemperatureSensor_RTDType type){
  return PhidgetTemperatureSensor_setRTDType(handle, type);
}

const unsigned short RTDSensor::GetNWires(){
  Phidget_RTDWireSetup ws;
  PhidgetTemperatureSensor_getRTDWireSetup(handle, &ws);
  switch(ws){
    case RTD_WIRE_SETUP_2WIRE:
      return 2;
    case RTD_WIRE_SETUP_3WIRE:
      return 3;
    case RTD_WIRE_SETUP_4WIRE:
      return 4;
    default:
      return 0;
  }
}

PhidgetReturnCode RTDSensor::SetNWires(const unsigned short nw){
  switch (nw)
  {
  case 2:
    return PhidgetTemperatureSensor_setRTDWireSetup(handle, RTD_WIRE_SETUP_2WIRE);
  case 3:
    return PhidgetTemperatureSensor_setRTDWireSetup(handle, RTD_WIRE_SETUP_3WIRE);
  case 4:
    return PhidgetTemperatureSensor_setRTDWireSetup(handle, RTD_WIRE_SETUP_4WIRE);
  default:
    return EPHIDGET_UNEXPECTED;
  }
}

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
