#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "HumiditySensor.hh"

HumiditySensor::HumiditySensor(int hub_port, int serialNumber, bool netServer) : PhidgetPP(hub_port, serialNumber)
{
  /*!
      * Constructor sets the serial number and sensor type if defined and
      *attempts to connect to the device.
      */
  status = PhidgetHumiditySensor_create(&handle);
  phandle = (PhidgetHandle)handle;

  status = Phidget_setIsHubPortDevice(phandle, 0);
  if (hubPort >= 0)
    status = Phidget_setHubPort(phandle, hubPort);
  if (serialNumber)
    status = Phidget_setDeviceSerialNumber(phandle, serialNumber);

  if (AllGood())
  {
    if (netServer)
    {
      Phidget_setIsRemote(phandle, 1);
      PhidgetNet_addServer("ServerName", "localhost", 5661, "", 0);
    }
    status = Phidget_openWaitForAttachment(phandle, 5000);
  }
  else
  {
    std::cerr << "Hmm. " << GetError() << std::endl;
  }
}

HumiditySensor::~HumiditySensor()
{
  /*!
      * Destructor disconnects the device and deletes the handle
      */
  Phidget_close(phandle);
  PhidgetHumiditySensor_delete(&handle);
}

double HumiditySensor::GetHumidity()
{
  /*!
       * returns the current humidity percentage measured by the sensor
       */
  status = PhidgetHumiditySensor_getHumidity(handle, &humidityValue);
  if (status == EPHIDGET_OK)
    return humidityValue;
  else
    return -999999.;
}

double HumiditySensor::GetHumidityChangeTrigger()
{
  /*!
        * Returns the minimum change in humidity needed to trigger a change in value event. Default is set to 0
        */
  status = PhidgetHumiditySensor_getHumidityChangeTrigger(handle, &valueChangeTrigger);
  if (status == EPHIDGET_OK)
    return valueChangeTrigger;
  else
    return -999999.;
}

int HumiditySensor::SetHumidityChangeTrigger(double newValueChangeTrigger)
{
  /*!
        * Sets the minimum change in measurement needed to trigger a change in value event.
        * Default is set to 0.0 units.
        */
  status = PhidgetHumiditySensor_setHumidityChangeTrigger(handle, newValueChangeTrigger);
  if (status == EPHIDGET_OK)
    return 1;
  else
    return 0.;
}

PhidgetReturnCode HumiditySensor::SetHumidityChangeFunc(PhidgetHumiditySensor_OnHumidityChangeCallback tempChangeFunc)
{
  /*!
        * Sets the function to be called when a humdity change event is
        * triggered. It is recommended that tempChangeFunc is defined after
        * the devices namespace in the main file.
        */
  status = PhidgetHumiditySensor_setOnHumidityChangeHandler(handle, tempChangeFunc, NULL);
  return status;
}

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
