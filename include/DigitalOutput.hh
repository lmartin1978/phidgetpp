#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>


class DigitalOutput
/*! \brief Class for the Digital Output Capabilities on the HUB phidget
 *
 * Class interfaces with the C API for the Digital Output on the HUB phidget(HUB0000_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
    DigitalOutput(int hub_port = -1,int serialNumber = 0){
        /*!
         * Constructor function assigns the hub port and serial number if defined
         * and attempts to connect to the device. Serial Numbers are needed for
         * identification when connecting multiple identical devices.
         */
        status = PhidgetDigitalOutput_create(&handle);
        hubPort = hub_port;
        status = Phidget_setIsHubPortDevice((PhidgetHandle)handle, int(hubPort >= 0));
        if(hubPort >= 0) status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
        if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);
        if(AllGood()){
            status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
        } else {
            std::cerr << "Digital Output Constructor Error:" << GetErrorCode() << std::endl;
        }
    }

    ~DigitalOutput(){
        Phidget_close((PhidgetHandle)handle);
        PhidgetDigitalOutput_delete(&handle);
    }

    bool AllGood(){
        /*!
         *Confirms if the phidget status is okay
         *
         */
        return status == EPHIDGET_OK;
    }

    PhidgetReturnCode GetError(){
        /*!
         *Returns the status of the phidget
         *
         */
        return status;
    }

    std::string GetErrorCode(){
        /*!
         *Returns the description of the status of the phidget
         */
        const char* errorChar;
        Phidget_getErrorDescription(GetError(),&errorChar);
        std::string errorString(errorChar);
        return errorString;
    }

    double GetDutyCycle(){
        /*!
         * Returns the duty cycle of PWM mode (0..1)
         */
        double dutycycle;
        status = PhidgetDigitalOutput_getDutyCycle(handle, &dutycycle);
        return dutycycle;
    }

    PhidgetReturnCode SetDutyCycle(double newValue){
        /*!
         * Sets the duty cycle of PWM mode (0..1)
         */
        status = PhidgetDigitalOutput_setDutyCycle(handle, newValue);
        return status;
    }

    int GetState(){
        /*!
         * Returns the current state of the output
         */
        int state;
        status = PhidgetDigitalOutput_getState(handle,&state);
        if(status == EPHIDGET_OK)
            return state;
        else
            return -1;
    }

    PhidgetReturnCode SetState(int state){
        /*!
         * Sets the state of the output
         */
        status = PhidgetDigitalOutput_setState(handle,state);
        return status;
    }

private:
    int hubPort;
    PhidgetDigitalOutputHandle handle;
    PhidgetReturnCode status;
};
