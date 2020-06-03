#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"
#include "VoltageInput.hh"

VoltageInput::VoltageInput(int hub_port, int serialNumber, bool hubPortDevice) : PhidgetPP(hub_port, serialNumber)
{
  status = PhidgetVoltageInput_create(&handle);
  phandle = (PhidgetHandle)handle;
  status = Phidget_setIsHubPortDevice(phandle, int(hubPortDevice));
  if (hubPort >= 0)
    status = Phidget_setHubPort(phandle, hubPort);
  if (serialNumber)
    status = Phidget_setDeviceSerialNumber(phandle, serialNumber);
  if (AllGood())
  {
    status = Phidget_openWaitForAttachment(phandle, 5000);
  }
  else
  {
    std::cerr << "Voltage Input Constructor Error:" << GetErrorCode() << std::endl;
  }
}

VoltageInput::~VoltageInput()
{
  Phidget_close(phandle);
  PhidgetVoltageInput_delete(&handle);
}

double VoltageInput::GetVoltage()
{
  status = PhidgetVoltageInput_getVoltage(handle, &voltage);
  if (status == EPHIDGET_OK)
    return voltage;
  else
    return -999999.;
}

double VoltageInput::GetVoltageValueChangeTrigger()
{
  status = PhidgetVoltageInput_getVoltageChangeTrigger(handle, &valueChangeTrigger);
  if (status == EPHIDGET_OK)
    return valueChangeTrigger;
  else
    return -999999.;
}

int VoltageInput::SetVoltageValueChangeTrigger(double newValueChangeTrigger)
{
  status = PhidgetVoltageInput_setVoltageChangeTrigger(handle, newValueChangeTrigger);
  if (status == EPHIDGET_OK)
    return 1;
  else
    return 0.;
}

PhidgetReturnCode VoltageInput::setVoltageValueChangeFunc(PhidgetVoltageInput_OnVoltageChangeCallback tempChangeFunc)
{
  status = PhidgetVoltageInput_setOnVoltageChangeHandler(handle, tempChangeFunc, NULL);
  return status;
}
