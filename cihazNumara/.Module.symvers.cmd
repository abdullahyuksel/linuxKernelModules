cmd_/home/pi/linux/cihazNumara/Module.symvers := sed 's/ko$$/o/' /home/pi/linux/cihazNumara/modules.order | scripts/mod/modpost -m -a   -o /home/pi/linux/cihazNumara/Module.symvers -e -i Module.symvers   -T -
