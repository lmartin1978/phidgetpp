#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"
#include "VoltageOutput.hh"

VoltageOutput::VoltageOutput(int hub_port, int serialNumber,
              PhidgetVoltageOutput_VoltageOutputRange outputRange) : PhidgetPP(hub_port, serialNumber)
{
  status = PhidgetVoltageOutput_create(&handle);
  phandle = (PhidgetHandle)handle;
  status = PhidgetVoltageOutput_setVoltageOutputRange(handle, outputRange);
  PhidgetVoltageOutput_getMinVoltage(handle, &hwbounds[0]);
  PhidgetVoltageOutput_getMaxVoltage(handle, &hwbounds[1]);
  if (hubPort >= 0)
    status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
  if (serialNumber)
    status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);

  if (AllGood())
  {
    status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
  }
  else
  {
    std::cerr << "Voltage Output Constructor Error:" << GetErrorCode() << std::endl;
  }
}

VoltageOutput::~VoltageOutput()
{
  Phidget_close((PhidgetHandle)handle);
  PhidgetVoltageOutput_delete(&handle);
}

double VoltageOutput::GetVoltage()
{
  status = PhidgetVoltageOutput_getVoltage(handle, &voltage);
  if (status == EPHIDGET_OK)
    return voltage;
  else
    return -999999.;
}

double VoltageOutput::SetVoltage(double newVoltage)
{
  if (newVoltage < bounds[0])
  {
    std::cerr << "Requested new voltage too low\n";
  }
  else if (newVoltage > bounds[1])
  {
    std::cerr << "Requested new voltage too high\n";
  }
  else
  {
    status = PhidgetVoltageOutput_setVoltage(handle, newVoltage);
    if (status == EPHIDGET_OK)
    {
      voltage = GetVoltage();
    }
  }
  return status;
}

int VoltageOutput::setLowerVoltageBound(double lowerBound)
{
  bounds[0] = lowerBound;
  if (bounds[0] < hwbounds[0])
  {
    std::cerr << "Requested boundary outside hardware limits. Will not affect operation." << std::endl;
  }
  return 0;
}

double VoltageOutput::getLowerVoltageBound()
{
  return bounds[0];
}

int VoltageOutput::removeLowerVoltageBound()
{
  bounds[0] = -9999.;
  return 0;
}

int VoltageOutput::setUpperVoltageBound(double upperBound)
{
  bounds[1] = upperBound;
  if (bounds[1] > hwbounds[1])
  {
    std::cerr << "Requested boundary outside hardware limits. Will not affect operation." << std::endl;
  }
  return 0;
}

double VoltageOutput::getUpperVoltageBound()
{
  return bounds[1];
}

int VoltageOutput::removeUpperVoltageBound()
{
  bounds[1] = 9999.;
  return 0;
}
