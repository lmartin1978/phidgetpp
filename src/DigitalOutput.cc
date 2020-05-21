#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>
#include "Phidget.hh"
#include "DigitalOutput.hh"

DigitalOutput::DigitalOutput(const int hub_port, const int serialNumber) : PhidgetPP(hub_port, serialNumber)
{
    status = PhidgetDigitalOutput_create(&handle);
    status = Phidget_setIsHubPortDevice((PhidgetHandle)handle, int(hubPort >= 0));
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
        std::cerr << "Digital Output Constructor Error:" << GetErrorCode() << std::endl;
    }
}

DigitalOutput::~DigitalOutput()
{
    Phidget_close((PhidgetHandle)handle);
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
