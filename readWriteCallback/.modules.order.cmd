cmd_/home/pi/linux/readWriteCallback/modules.order := {   echo /home/pi/linux/readWriteCallback/readWriteCallback.ko; :; } | awk '!x[$$0]++' - > /home/pi/linux/readWriteCallback/modules.order
