cmd_/home/pi/linux/cihazNumara/modules.order := {   echo /home/pi/linux/cihazNumara/cihazNumara.ko; :; } | awk '!x[$$0]++' - > /home/pi/linux/cihazNumara/modules.order
