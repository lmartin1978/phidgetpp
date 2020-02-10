  #include <iostream>
  #include <cassert>
  #include <stdio.h>
  #include <string>
  #include <phidget22.h>

  class DisplayLCD
  /*! \brief Class for the Graphic LCD Phidget
   *
   *Class interfaces with the C API for the Graphic LCD Phidget (LCD1100_0). It is recommended to define
   *all devices in a namespace above the main function.
   */
  {
  public:
      DisplayLCD(int hub_port = -1, int serialNumber = 0){//
          /*!
          *Constructor assigns the hubport and serial number if defined,
          *then attempts to connect to the device. Serial Numbers are needed
          *for identification when connecting multiple identical devices
          */
          status = PhidgetLCD_create(&handle);
          hubPort = hub_port;
          status = Phidget_setIsHubPortDevice((PhidgetHandle)handle, int(hubPort >= 0));
          if(hubPort >= 0) status = Phidget_setHubPort((PhidgetHandle)handle, hubPort);
          if(serialNumber) status = Phidget_setDeviceSerialNumber((PhidgetHandle)handle, serialNumber);

          //attempt to connect to device
          if(AllGood()){
              status = Phidget_openWaitForAttachment((PhidgetHandle)handle, 5000);
          } else {
              Phidget_getErrorDescription(GetError(),&errorChar);
              std::cerr << "DisplayLCD Constructor Error:" << errorChar << std::endl;
          }
      }
      ~DisplayLCD(){
        /*!
        *Destructor sets the backlight to 0, disconnects the device and deletes
        *the handle
        */
           PhidgetLCD_setBacklight(handle,0.0);
           Phidget_close((PhidgetHandle)handle);
           PhidgetLCD_delete(&handle);
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
         Phidget_getErrorDescription(GetError(),&errorChar);
         std::string errorString(errorChar);
         return errorString;
       }
       uint32_t GetDataInterval(){
         /*!
         *Returns the minimum time that must elapse before another data event is fired
         *Units of ms
         */
         status = Phidget_getDataInterval((PhidgetHandle)handle, &dataInterval);
         return dataInterval;
       }
       PhidgetReturnCode SetDataInterval(uint32_t newValue){
         /*!
         *Sets the minimum time that must elapse before another data event is fired
         *Units of ms
         */
         status = Phidget_getDataInterval((PhidgetHandle)handle, &dataInterval);
         dataInterval = GetDataInterval();
         return status;
       }

       double GetBacklight(){
          /*!
          *Returns the current backlight value between 0 and 1. By default it is
          *set to 0
          */
          status = PhidgetLCD_getBacklight(handle,&backlight);
          if (AllGood()){
            return backlight;
          }
          else{
            return 99999.9;
          }
       }
       PhidgetReturnCode SetBacklight(double newValue){
         /*!
         *Sets the backlight to a value between 0 and 1. By default it is
         *set to 0
         */
         status = PhidgetLCD_setBacklight(handle,newValue);
         if (AllGood()){
           backlight = newValue;
         }
         return status;
       }
       PhidgetReturnCode ClearScreen(){
         /*!
         *Clears all text and graphics from the screen/
         */
         status = PhidgetLCD_clear(handle);
         return status;
       }
       double GetContrast(){
         /*!
         *Returns the current contrast value between 0 and 1. By default it is
         *set to 0.25
         */
          status = PhidgetLCD_getContrast(handle,&contrast);
          if (AllGood()){
            return contrast;
          }
          else{
            return 99999.9;
          }
       }
       PhidgetReturnCode SetContrast(double newValue){
         /*!
         *Sets the contrast to a value between 0 and 1. By default it is
         *set to 0.25
         */
         status = PhidgetLCD_setContrast(handle,newValue);
         if (AllGood()){
           contrast = newValue;
         }
         return status;
       }
       PhidgetReturnCode Write(int line,std::string formatText){
         /*!
         *Write text onto the LCD screen at a specified positon with 6x10 font
         *at a specified line between 1 and 6
         */
         status = PhidgetLCD_writeText(handle,FONT_6x10,1,2+10*(line-1),"                                                       ");
         status = PhidgetLCD_flush(handle);
         status = PhidgetLCD_writeText(handle,FONT_6x10,1,2+10*(line-1),formatText.c_str());
         status = PhidgetLCD_flush(handle);
         return status;
       }

       PhidgetReturnCode DrawPixel(int x,int y,int state){
         /*!
         * Sets the state of a single pixel to off[0] or on[1] or invert[2]
         */
         if(state == 0){
           return PhidgetLCD_drawPixel(handle,x,y,PIXEL_STATE_OFF);
         }else if(state==1){
           return PhidgetLCD_drawPixel(handle,x,y,PIXEL_STATE_ON);
         }else if(state==2){
           return PhidgetLCD_drawPixel(handle,x,y,PIXEL_STATE_INVERT);
         }
       }


       private:
         PhidgetLCDHandle handle;
         PhidgetReturnCode status;
         int hubPort;
         double backlight;
         double contrast;
         uint32_t dataInterval;
         const char *errorChar;
         std::string errorString;

  };

