#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"
#include "DigitalOutput.hh"

DigitalOutput::DigitalOutput(const int hub_port, const int serialNumber, const int channel) : PhidgetPP(hub_port, serialNumber, channel)
{
    status = PhidgetDigitalOutput_create(&handle);
    phandle = (PhidgetHandle)handle;
    status = Phidget_setIsHubPortDevice(phandle, int(hubPort >= 0));
    if (hubPort >= 0)
        status = Phidget_setHubPort(phandle, hubPort);
    if (serialNumber)
        status = Phidget_setDeviceSerialNumber(phandle, serialNumber);
    if (channel >= 0)
        status = Phidget_setChannel(phandle, channel);
    if (AllGood())
    {
        status = Phidget_openWaitForAttachment(phandle, 5000);
    }
    else
    {
        std::cerr << "Digital Output Constructor Error:" << GetErrorCode() << std::endl;
    }
}

DigitalOutput::~DigitalOutput()
{
    Phidget_close(phandle);
    PhidgetDigitalOutput_delete(&handle);
}

double DigitalOutput::GetDutyCycle()
{
    double dutycycle;
    status = PhidgetDigitalOutput_getDutyCycle(handle, &dutycycle);
    return dutycycle;
}

PhidgetReturnCode DigitalOutput::SetDutyCycle(double newValue)
{
    status = PhidgetDigitalOutput_setDutyCycle(handle, newValue);
    return status;
}

int DigitalOutput::GetState()
{
    int state;
    status = PhidgetDigitalOutput_getState(handle, &state);
    if (status == EPHIDGET_OK)
        return state;
    else
        return -1;
}

PhidgetReturnCode DigitalOutput::SetState(int state)
{
    status = PhidgetDigitalOutput_setState(handle, state);
    return status;
}
