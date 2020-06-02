#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"
#include "Thermocouple.hh"

const char Thermocouple::GetType(){
  PhidgetTemperatureSensor_getThermocoupleType(handle, &tctype);
  switch (tctype)
  {
  case THERMOCOUPLE_TYPE_J:
    return 'J';  
  case THERMOCOUPLE_TYPE_K:
    return 'K';  
  case THERMOCOUPLE_TYPE_E:
    return 'E';  
  case THERMOCOUPLE_TYPE_T:
    return 'T';  
  default:
    return 'X';
  }
}

PhidgetReturnCode Thermocouple::SetType(const PhidgetTemperatureSensor_ThermocoupleType type){
  return PhidgetTemperatureSensor_setThermocoupleType(handle, type);
}

PhidgetReturnCode Thermocouple::SetType(const char type){
  switch (type)
  {
  case 'J':
    return SetType(THERMOCOUPLE_TYPE_J);  
  case 'K':
    return SetType(THERMOCOUPLE_TYPE_K);  
  case 'E':
    return SetType(THERMOCOUPLE_TYPE_E);  
  case 'T':
    return SetType(THERMOCOUPLE_TYPE_T);  
  default:
    return EPHIDGET_UNEXPECTED;
  }
}
