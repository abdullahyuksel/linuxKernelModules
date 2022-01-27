#include <linux/module.h>
#include <linux/init.h>


static int __init ModuleInit(void)
{
	printk("merhaba Linux \n");
	return 0;
}

static void __exit ModuleExit(void)
{
	printk("hoscakal Linux \n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abdullahYuksel");
MODULE_DESCRIPTION("merhaba Linux");

module_init(ModuleInit);
module_exit(ModuleExit);
