#include <iostream>
#include <limits>
#include <phidget22.h>
#include <string>
#include "Phidget.hh"
#include "TemperatureSensor.hh"

TemperatureSensor::TemperatureSensor(int hub_port, int serialNumber) : PhidgetPP(hub_port, serialNumber)
{
    status = PhidgetTemperatureSensor_create(&handle);
    phandle = (PhidgetHandle)handle;

    status = Phidget_setIsHubPortDevice(phandle, 0);
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
            std::cerr << "Temperature Sensor Constructor Error:" << GetErrorCode() << std::endl;
        }
}

TemperatureSensor::~TemperatureSensor()
{
    /*!
     * Destructor disconnects the device and delets the handle
     */
    Phidget_close(phandle);
    PhidgetTemperatureSensor_delete(&handle);
}

double TemperatureSensor::GetTemp()
{
    /*!
     *Returns the current temperature measured by the phidget
     */
    status = PhidgetTemperatureSensor_getTemperature(handle, &temperature);
    if (status == EPHIDGET_OK)
        return temperature;
    else
        return std::numeric_limits<double>::quiet_NaN();
}

double TemperatureSensor::GetTempChangeTrigger()
{
    /*!
     * Returns the minimum threshold to trigger a change in temperature event.
     * Default value is 0.0 units
     */
    status = PhidgetTemperatureSensor_getTemperatureChangeTrigger(handle, &tempChangeTrigger);
    return tempChangeTrigger;
}

PhidgetReturnCode TemperatureSensor::SetTempChangeTrigger(double newTempChangeTrigger)
{
    /*!
     * Sets the minimum threshold to trigger a change in temperature event.
     * Default value is 0.0 units
     */
    status = PhidgetTemperatureSensor_getTemperatureChangeTrigger(handle, &newTempChangeTrigger);
    return status;
}

PhidgetReturnCode TemperatureSensor::SetTempChangeFunc(PhidgetTemperatureSensor_OnTemperatureChangeCallback tempChangeFunc)
{
    /*!
     * Sets the function that will be called when a temperature change event occurs
     */
    status = PhidgetTemperatureSensor_setOnTemperatureChangeHandler(handle, tempChangeFunc, NULL);
    return status;
}

double TemperatureSensor::GetMinTemp(){
    double temp;
    PhidgetTemperatureSensor_getMinTemperature(handle, &temp);
    return temp;
}

double TemperatureSensor::GetMaxTemp(){
    double temp;
    PhidgetTemperatureSensor_getMaxTemperature(handle, &temp);
    return temp;
}

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
