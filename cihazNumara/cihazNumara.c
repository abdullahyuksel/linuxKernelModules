#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DRIVER_NAME "device-abdullahYuksel"
#define DRIVER_CLASS "class-abdullahYuksel"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abdullahYuksel");
MODULE_DESCRIPTION("Cihaz Kayıt Numarasi");

static dev_t my_device_number;
static struct class *my_class;
static struct cdev my_device;

static int driver_open(struct inode *defice_file, struct file *instance)
{
	printk("char_dev1 - open was called!\n");
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance)
{
	printk("char_dev1 - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};

static int __init ModuleInit(void)
{
	int retVal;
	printk("init kernel\n");

	if(alloc_chrdev_region(&my_device_number, 0, 1, DRIVER_NAME)<0 )
	{
		printk("Allocation error");
		return -1;
	}
	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL)
	{
		goto ClassErr;
	}
	if(device_create(my_class, NULL, my_device_number, NULL, DRIVER_NAME)== NULL)
	{
		goto FileErr;
	}
	
	cdev_init(&my_device, &fops);

	if(cdev_add(&my_device, my_device_number, 1) == -1)
	{
		goto AddErr;
	}

	return 0;

AddErr:
	device_destroy(my_class, my_device_number);
FileErr:
	class_destroy(my_class);
ClassErr:
	unregister_chrdev_region(my_device_number, 1);
	return 1;
}

static void __exit ModuleExit(void)
{
	printk("Exit kernel\n");

	cdev_del(&my_device);
	device_destroy(my_class, my_device_number);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_number, 1);
}

module_init(ModuleInit);
module_exit(ModuleExit);
