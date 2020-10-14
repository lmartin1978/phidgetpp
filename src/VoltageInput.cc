#include <iostream>
#include <cassert>
#include <stdio.h>
#include <limits>
#include <phidget22.h>
#include "Phidget.hh"
#include "VoltageInput.hh"

VoltageInput::VoltageInput(int hub_port, int serialNumber, bool hubPortDevice, bool netServer) : PhidgetPP(hub_port, serialNumber)
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
        if (netServer)
        {
            Phidget_setIsRemote(phandle, 1);
            PhidgetNet_addServer("ServerName", "localhost", 5661, "", 0);
        }
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
        return std::numeric_limits<double>::quiet_NaN();
}

double VoltageInput::GetVoltageValueChangeTrigger()
{
    status = PhidgetVoltageInput_getVoltageChangeTrigger(handle, &valueChangeTrigger);
    if (status == EPHIDGET_OK)
        return valueChangeTrigger;
    else
        return std::numeric_limits<double>::quiet_NaN();
}

int VoltageInput::SetVoltageValueChangeTrigger(double newValueChangeTrigger)
{
    status = PhidgetVoltageInput_setVoltageChangeTrigger(handle, newValueChangeTrigger);
    if (status == EPHIDGET_OK)
        return 1;
    else
        return 0;
}

PhidgetReturnCode VoltageInput::setVoltageValueChangeFunc(PhidgetVoltageInput_OnVoltageChangeCallback tempChangeFunc)
{
    status = PhidgetVoltageInput_setOnVoltageChangeHandler(handle, tempChangeFunc, NULL);
    return status;
}

bool VoltageInput::SetVoltageRange(PhidgetVoltageInput_VoltageRange vrange)
{
   PhidgetReturnCode err = PhidgetVoltageInput_setVoltageRange(handle, vrange);
   if(err != EPHIDGET_OK){
      std::cerr << GetErrorCode() << std::endl;
      return false;
   }
   return true;
}

double VoltageInput::GetVmin()
{
   double v;
   PhidgetVoltageInput_getMinVoltage(handle, &v);
   return v;
}

double VoltageInput::GetVmax()
{
   double v;
   PhidgetVoltageInput_getMaxVoltage(handle, &v);
   return v;
}

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
