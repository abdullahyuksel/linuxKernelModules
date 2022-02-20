#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x9fc357ed, "module_layout" },
	{ 0x8de527fa, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xf9116977, "class_destroy" },
	{ 0x953b01ce, "device_destroy" },
	{ 0xacb2cbc0, "gpiod_direction_input" },
	{ 0xc9349a22, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xc7684a86, "cdev_add" },
	{ 0x8e5ae04c, "cdev_init" },
	{ 0xf7f140e7, "device_create" },
	{ 0xa0058d45, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x9a0a6a2b, "gpiod_get_raw_value" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x5f754e5a, "memset" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0xf4d2c523, "gpiod_set_raw_value" },
	{ 0x198a5863, "gpio_to_desc" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0D4482BDE28AAD17B8BCAB0");
