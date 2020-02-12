#!/bin/bash

#powers off and then powers on the usb ports of raspberry pi model 3b+ 
#requires installing https://github.com/mvp/uhubctl#raspberry-pi-3b

sudo uhubctl -l 1-1 -p 2 -a 0
sudo uhubctl -l 1-1 -p 2 -a 1
