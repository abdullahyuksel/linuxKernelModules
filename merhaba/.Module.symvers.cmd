cmd_/home/pi/linux/merhaba/Module.symvers := sed 's/ko$$/o/' /home/pi/linux/merhaba/modules.order | scripts/mod/modpost -m -a   -o /home/pi/linux/merhaba/Module.symvers -e -i Module.symvers   -T -
