#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abdullahYuksel");
MODULE_DESCRIPTION("gpioDriver");

static dev_t my_device_number;
static struct class *my_class;
static struct cdev my_device;

static char buffer[255];
static int buffer_pointer = 0;

#define DRIVER_NAME "gpioDriver-abdullahYuksel"
#define DRIVER_CLASS "driver-abdullahYuksel"


static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs)
{
	int to_copy, not_copy, returnVal;
	int gpiValue;
	printk("Read Callback!\n");
	
	gpiValue = gpio_get_value(27);

	if(gpiValue == 1)
	{
		printk("input HIGH\n");
		gpio_set_value(4, 1);
		printk("LED ON\n");
	}
	else if(gpiValue == 0)
	{
		printk("input LOW");
		gpio_set_value(4, 0);
		printk("LED OFF");
	}

	//printk("Read Callback!\n");
	//to_copy = min(count, buffer_pointer);
	//not_copy = copy_to_user(user_buffer, buffer, to_copy);
	//returnVal = to_copy - not_copy;
	//printk("Driver read: %d \n", returnVal);

	
	return returnVal;
}

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
	int to_copy, not_copy, returnVal;
	char gpoValue;

	printk("Write Callback!\n");

	to_copy = min(count, sizeof(gpoValue));
	not_copy = copy_from_user(&gpoValue, user_buffer, to_copy);
	
	if(gpoValue == '1')
	{
		gpio_set_value(4, 1);
		//printk("LED ON\n");
	}
	else if(gpoValue == '0')
	{
		gpio_set_value(4, 0);
		//printk("LED OFF\n");
	}

	returnVal = to_copy - not_copy;
	return returnVal;
}

static int driver_open(struct inode *device_file, struct file *instance)
{
	printk("readWriteCallback - open was called!\n");
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance)
{
	printk("readWriteCallback - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner		= THIS_MODULE,
	.open 		= driver_open,
	.read 		= driver_read,
	.write		= driver_write,
	.release 	= driver_close
};

static int __init ModuleInit(void)
{
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

	if(gpio_request(4, "gpio-4"))
	{
		goto GpioErr;
	}

	if(gpio_direction_output(4, 0))
	{
		goto GpioErr;
	}
	if(gpio_request(27, "gpio-27"))
	{
		goto GpioErr;
	}

	if(gpio_direction_input(27))
	{
		goto GpioErr;
	}

	return 0;

GpioErr:
	gpio_free(4);
	gpio_free(27);
AddErr:
	device_destroy(my_class, my_device_number);
FileErr:
	class_destroy(my_class);
ClassErr:
	unregister_chrdev_region(my_device_number, 1);
	return -1;
}

static void __exit ModuleExit(void)
{
	printk("Exit Kernel\n");
	gpio_free(4);
	gpio_free(27);
	cdev_del(&my_device);
	device_destroy(my_class, my_device_number);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_number, 1);
}

module_init(ModuleInit);
module_exit(ModuleExit);
