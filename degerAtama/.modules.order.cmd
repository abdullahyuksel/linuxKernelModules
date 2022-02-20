cmd_/home/pi/linux/degerAtama/modules.order := {   echo /home/pi/linux/degerAtama/degerAtama.ko; :; } | awk '!x[$$0]++' - > /home/pi/linux/degerAtama/modules.order
