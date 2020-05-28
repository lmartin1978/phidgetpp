#ifndef PHIDGETPP_HH
#define PHIDGETPP_HH
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <phidget22.h>

class PhidgetPP
/*! \brief Class for the Digital Output Capabilities on the HUB phidget
 *
 * Class interfaces with the C API for the Digital Output on the HUB phidget(HUB0000_0). It is recommended to define
 * all devices in a namespace above the main function.
 */
{
public:
    /*!
     * \brief Constructor, has to be defined by each phidget type
     * 
     * \param hub_port Port on the phidget hub device, if applicable
     * \param SerialNumber Serial number of the phidget, or of the the Hub it is connected to.
     * Only necessary if multiple identical devices are connected.
     */
    PhidgetPP(const int hub_port = -1, const int serialNumber = 0, const int chan = -1) : hubPort(hub_port), serNo(serialNumber), channel(chan){};

    /*!
     * \brief Destructor, has to be defined by each phidget type, but base destructor is always called last
     * 
     */
    virtual ~PhidgetPP() {}

    const bool AllGood()
    {
        /*!
         *Confirms if the phidget status is okay
         *
         */
        return status == EPHIDGET_OK;
    }

    const PhidgetReturnCode GetError()
    {
        /*!
         *Returns the status of the phidget
         *
         */
        return status;
    }

    const std::string GetErrorCode()
    {
        /*!
         *Returns the description of the status of the phidget
         */
        const char *errorChar;
        Phidget_getErrorDescription(GetError(), &errorChar);
        std::string errorString(errorChar);
        return errorString;
    }

    /*! @brief Get minimum time between readouts/outputs
      *
      * Returns the minimum time that must elapse before another data event is fired
      * units of ms.
      */
    uint32_t GetDataInterval()
    {
        status = Phidget_getDataInterval(phandle, &dataInterval);
        return dataInterval;
    }

    /*! @brief Set minimum time between readouts/outputs
      *
      * Sets the minimum time that must elapse before another data event is fired
      * units of ms.
      */
    PhidgetReturnCode SetDataInterval(uint32_t newValue)
    {
        /*!
      *Sets the minimum time that must elapse before another data event is fired
      *units of ms.
      */
        status = Phidget_setDataInterval(phandle, newValue);
        dataInterval = GetDataInterval();
        return status;
    }

    /*! @brief Get channel number
      *
      */
    int GetChannel()
    {
        return channel;
    }
protected:
    const int hubPort;
    const int serNo;
    const int channel;
    PhidgetReturnCode status;
    PhidgetHandle phandle;
    uint32_t dataInterval;
};
#endif