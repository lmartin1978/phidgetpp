#include <iostream>
#include <cassert>
#include <stdio.h>
#include <string>
#include <phidget22.h>
#include "Phidget.hh"

class DisplayLCD : public PhidgetPP
/*! \brief Class for the Graphic LCD Phidget
   *
   *Class interfaces with the C API for the Graphic LCD Phidget (LCD1100_0). It is recommended to define
   *all devices in a namespace above the main function.
   */
{
public:
  DisplayLCD(int hub_port = -1, int serialNumber = 0);
  ~DisplayLCD();

  /*! @brief Get current backlight setting
   *
   *Returns the current backlight value between 0 and 1. By default it is
   *set to 0
   */
  double GetBacklight();

  /*! @brief Set backlight value
     *
     * Sets the backlight to a value between 0 and 1. By default it is
     *set to 0
     */
  PhidgetReturnCode SetBacklight(double newValue);

  /*! @brief Blank screen
     *
     *Clears all text and graphics from the screen/
     */
  PhidgetReturnCode ClearScreen();

  /*! @brief Get current contrast setting
     *
     *Returns the current contrast value between 0 and 1. By default it is
     *set to 0.25
      */
  double GetContrast();

  /*! @brief Set contarst value
     *
     *Sets the contrast to a value between 0 and 1. By default it is
     *set to 0.25
     */
  PhidgetReturnCode SetContrast(double newValue);

  /*! @brief Write text to screen
     *
     *Write text onto the LCD screen at a specified positon with 6x10 font
     *at a specified line between 1 and 6
     */
  PhidgetReturnCode Write(int line, std::string formatText);

  /*! @brief Set single pixel
     *
     * Sets the state of a single pixel to off[0] or on[1] or invert[2]
     */
  PhidgetReturnCode DrawPixel(int x, int y, int state);

private:
  PhidgetLCDHandle handle;
  double backlight;
  double contrast;
  uint32_t dataInterval;
};

/* emacs
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 3
 * indent-tabs-mode: nil
 * End:
 */
