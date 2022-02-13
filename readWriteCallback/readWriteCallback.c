#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abdullahYuksel");
MODULE_DESCRIPTION("readWriteCallback");

static dev_t my_device_number;
static struct class *my_class;
static struct cdev my_device;

static char buffer[255];
static int buffer_pointer = 0;

#define DRIVER_NAME "device-abdullahYuksel"
#define DRIVER_CLASS "class-abdullahYuksel"

static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs)
{
	int to_copy, not_copy, returnVal;
	printk("Read Callback!\n");
	to_copy = min(count, buffer_pointer);
	not_copy = copy_to_user(user_buffer, buffer, to_copy);
	returnVal = to_copy - not_copy;
	printk("Driver read: %d \n", returnVal);
	return returnVal;
}

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
	int to_copy, not_copy, returnVal;
	printk("Write Callback!\n");
	to_copy = min(count, sizeof(buffer));
	not_copy = copy_from_user(buffer, user_buffer, to_copy);
	buffer_pointer = to_copy;
	returnVal = to_copy - not_copy;
        printk("Driver write %d values %s \n", returnVal, (char*) buffer);
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
