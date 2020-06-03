#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"
#include "VoltageRatioSensor.hh"

VoltageRatioSensor::VoltageRatioSensor(int hub_port, PhidgetVoltageRatioInput_SensorType stype,
                                       int serialNumber, bool hubPortDevice, bool netServer) : PhidgetPP(hub_port, serialNumber)
{
  status = PhidgetVoltageRatioInput_create(&handle);
  phandle = (PhidgetHandle)handle;
  sensorType = stype;
  status = Phidget_setIsHubPortDevice((PhidgetHandle)handle, int(hubPortDevice));
  if (hubPort >= 0)
    status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
  if (serialNumber)
    status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);

  if (AllGood())
  {
    if (netServer)
    {
      Phidget_setIsRemote(phandle, 1);
      PhidgetNet_enableServerDiscovery(PHIDGETSERVER_DEVICEREMOTE);
      status = Phidget_open(phandle);
    }
    else
    {
      status = Phidget_openWaitForAttachment(phandle, 5000);
    }
    PhidgetVoltageRatioInput_setSensorType(handle, sensorType);
    PhidgetVoltageRatioInput_getSensorUnit(handle, &sensorUnit);
  }
  else
  {
    std::cerr << "Voltage Ratio Sensor Constructor Error:" << GetErrorCode() << std::endl;
  }
}

VoltageRatioSensor::~VoltageRatioSensor()
{
  Phidget_close((PhidgetHandle)handle);
  PhidgetVoltageRatioInput_delete(&handle);
}

double VoltageRatioSensor::GetVoltageRatio()
{
  status = PhidgetVoltageRatioInput_getVoltageRatio(handle, &vRatio);
  if (status == EPHIDGET_OK)
    return vRatio;
  else
    return -999999.;
}

double VoltageRatioSensor::GetValue()
{
  status = PhidgetVoltageRatioInput_getSensorValue(handle, &sensorValue);
  if (status == EPHIDGET_OK)
    return sensorValue;
  else
    return -999999.;
}

const char *VoltageRatioSensor::GetUnit()
{
  return sensorUnit.symbol;
}

double VoltageRatioSensor::GetSensorValueChangeTrigger()
{
  status = PhidgetVoltageRatioInput_getSensorValueChangeTrigger(handle, &valueChangeTrigger);
  if (status == EPHIDGET_OK)
    return valueChangeTrigger;
  else
    return -999999.;
}

int VoltageRatioSensor::SetSensorValueChangeTrigger(double newValueChangeTrigger)
{
  status = PhidgetVoltageRatioInput_setSensorValueChangeTrigger(handle, newValueChangeTrigger);
  if (status == EPHIDGET_OK)
    return 1;
  else
    return 0.;
}

PhidgetReturnCode VoltageRatioSensor::SetSensorValueChangeFunc(PhidgetVoltageRatioInput_OnSensorChangeCallback tempChangeFunc)
{
  status = PhidgetVoltageRatioInput_setOnSensorChangeHandler(handle, tempChangeFunc, NULL);
  return status;
}

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
