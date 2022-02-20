cmd_/home/pi/linux/merhaba/modules.order := {   echo /home/pi/linux/merhaba/merhaba.ko; :; } | awk '!x[$$0]++' - > /home/pi/linux/merhaba/modules.order
