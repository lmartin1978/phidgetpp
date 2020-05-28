#include <iostream>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"
#include "IsolatedThermocouple.hh"

IsolatedThermocouple::IsolatedThermocouple(int serialNumber) : PhidgetPP(-1, serialNumber)
{
  status = PhidgetTemperatureSensor_create(&handle);
  phandle = (PhidgetHandle)handle;
  if (serialNumber)
    status = Phidget_setDeviceSerialNumber(phandle, serialNumber);

  if (AllGood())
  {
    status = Phidget_openWaitForAttachment(phandle, 5000);
  }
  else
  {
    std::cerr << "Thermocouple Constructor Error:" << GetErrorCode() << std::endl;
  }
}
IsolatedThermocouple::~IsolatedThermocouple()
{
  /*!
    * Destructor disconnects the device and delets the handle
    */
  Phidget_close(phandle);
  PhidgetTemperatureSensor_delete(&handle);
}

double IsolatedThermocouple::GetTemp()
{
  /*!
    *Returns the current temperature measured by the phidget
    */
  status = PhidgetTemperatureSensor_getTemperature(handle, &temperature);
  if (status == EPHIDGET_OK)
    return temperature;
  else
    return -999999.;
}

double IsolatedThermocouple::GetTempChangeTrigger()
{
  /*!
    * Returns the minimum threshold to trigger a change in temperature event.
    * Default value is 0.0 units
    */
  status = PhidgetTemperatureSensor_getTemperatureChangeTrigger(handle, &tempChangeTrigger);
  return tempChangeTrigger;
}

PhidgetReturnCode IsolatedThermocouple::SetTempChangeTrigger(double newTempChangeTrigger)
{
  /*!
    * Sets the minimum threshold to trigger a change in temperature event.
    * Default value is 0.0 units
    */
  status = PhidgetTemperatureSensor_getTemperatureChangeTrigger(handle, &newTempChangeTrigger);
  return status;
}

PhidgetReturnCode IsolatedThermocouple::SetTempChangeFunc(PhidgetTemperatureSensor_OnTemperatureChangeCallback tempChangeFunc)
{
  /*!
    * Sets the function that will be called when a temperature change event occurs
    */
  status = PhidgetTemperatureSensor_setOnTemperatureChangeHandler(handle, tempChangeFunc, NULL);
  return status;
}
