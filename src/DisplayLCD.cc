#include <iostream>
#include <cassert>
#include <stdio.h>
#include <string>
#include <phidget22.h>
#include "Phidget.hh"
#include "DisplayLCD.hh"

DisplayLCD::DisplayLCD(int hub_port, int serialNumber) : PhidgetPP(hub_port, serialNumber)
{ //
  /*!
          *Constructor assigns the hubport and serial number if defined,
          *then attempts to connect to the device. Serial Numbers are needed
          *for identification when connecting multiple identical devices
          */
  status = PhidgetLCD_create(&handle);
  phandle = (PhidgetHandle)handle;

  status = Phidget_setIsHubPortDevice(phandle, int(hubPort >= 0));
  if (hubPort >= 0)
    status = Phidget_setHubPort(phandle, hubPort);
  if (serialNumber)
    status = Phidget_setDeviceSerialNumber(phandle, serialNumber);

  //attempt to connect to device
  if (AllGood())
  {
    status = Phidget_openWaitForAttachment(phandle, 5000);
  }
  else
  {
    std::cerr << "DisplayLCD Constructor Error:" << GetErrorCode() << std::endl;
  }
}
DisplayLCD::~DisplayLCD()
{
  /*!
        *Destructor sets the backlight to 0, disconnects the device and deletes
        *the handle
        */
  PhidgetLCD_setBacklight(handle, 0.0);
  Phidget_close(phandle);
  PhidgetLCD_delete(&handle);
}

double DisplayLCD::GetBacklight()
{
  /*!
          *Returns the current backlight value between 0 and 1. By default it is
          *set to 0
          */
  status = PhidgetLCD_getBacklight(handle, &backlight);
  if (AllGood())
  {
    return backlight;
  }
  else
  {
    return 99999.9;
  }
}
PhidgetReturnCode DisplayLCD::SetBacklight(double newValue)
{
  /*!
         *Sets the backlight to a value between 0 and 1. By default it is
         *set to 0
         */
  status = PhidgetLCD_setBacklight(handle, newValue);
  if (AllGood())
  {
    backlight = newValue;
  }
  return status;
}
PhidgetReturnCode DisplayLCD::ClearScreen()
{
  /*!
         *Clears all text and graphics from the screen/
         */
  status = PhidgetLCD_clear(handle);
  return status;
}
double DisplayLCD::GetContrast()
{
  /*!
         *Returns the current contrast value between 0 and 1. By default it is
         *set to 0.25
         */
  status = PhidgetLCD_getContrast(handle, &contrast);
  if (AllGood())
  {
    return contrast;
  }
  else
  {
    return 99999.9;
  }
}
PhidgetReturnCode DisplayLCD::SetContrast(double newValue)
{
  /*!
         *Sets the contrast to a value between 0 and 1. By default it is
         *set to 0.25
         */
  status = PhidgetLCD_setContrast(handle, newValue);
  if (AllGood())
  {
    contrast = newValue;
  }
  return status;
}
PhidgetReturnCode DisplayLCD::Write(int line, std::string formatText)
{
  /*!
         *Write text onto the LCD screen at a specified positon with 6x10 font
         *at a specified line between 1 and 6
         */
  status = PhidgetLCD_writeText(handle, FONT_6x10, 1, 2 + 10 * (line - 1), "                                                       ");
  status = PhidgetLCD_flush(handle);
  status = PhidgetLCD_writeText(handle, FONT_6x10, 1, 2 + 10 * (line - 1), formatText.c_str());
  status = PhidgetLCD_flush(handle);
  return status;
}

PhidgetReturnCode DisplayLCD::DrawPixel(int x, int y, int state)
{
  /*!
         * Sets the state of a single pixel to off[0] or on[1] or invert[2]
         */
  if (state == 0)
  {
    return PhidgetLCD_drawPixel(handle, x, y, PIXEL_STATE_OFF);
  }
  else if (state == 1)
  {
    return PhidgetLCD_drawPixel(handle, x, y, PIXEL_STATE_ON);
  }
  else if (state == 2)
  {
    return PhidgetLCD_drawPixel(handle, x, y, PIXEL_STATE_INVERT);
  }
}
