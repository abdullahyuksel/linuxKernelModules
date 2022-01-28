#include <linux/module.h>
#include <linux/init.h>

static int deger=1;

module param(deger, int, S_IRUGO);

static int __init ModuleInit(void)
{
	int i= 1;
	for(i; i<deger; i++)
		printk("sayac: %d \n", i);
	return 0;
}

static void __exit ModuleExit(void)
{
	printk("hoscakal Linux \n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abdullahYuksel");
MODULE_DESCRIPTION("Module Deger Atama");

module_init(ModuleInit);
module_exit(ModuleExit);
