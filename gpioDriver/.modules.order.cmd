cmd_/home/pi/linux/gpioDriver/modules.order := {   echo /home/pi/linux/gpioDriver/gpioDriver.ko; :; } | awk '!x[$$0]++' - > /home/pi/linux/gpioDriver/modules.order
