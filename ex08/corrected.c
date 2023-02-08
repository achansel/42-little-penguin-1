#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>

// Dont have a license, LOL
MODULE_LICENSE("LICENSE");
MODULE_AUTHOR("Louis Solofrizzo <louis@ne02ptzero.me>");
MODULE_DESCRIPTION("Useless module");

static ssize_t myfd_read(struct file *fp, char __user *user, size_t size, loff_t *offs);
static ssize_t myfd_write(struct file *fp, const char __user *user, size_t size, loff_t *offs);

static struct file_operations myfd_fops = {
        .owner = THIS_MODULE,
        .read = &myfd_read,
        .write = &myfd_write
};

static struct miscdevice myfd_device = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = "reverse",
        .fops = &myfd_fops
};

static char str[PAGE_SIZE * 2];

static int __init myfd_init(void)
{
        misc_register(&myfd_device);
        memset(str, 0, sizeof(str));
        return 0;
}

static void __exit myfd_cleanup(void)
{
        misc_deregister(&myfd_device);
}

ssize_t myfd_read(struct file *fp, char __user *user, size_t size, loff_t *offs)
{
        int     t, i;
        char    *tmp;

        tmp = kmalloc(sizeof(char) * PAGE_SIZE * 2, GFP_KERNEL);
        for (t = strlen(str) - 1, i = 0; t >= 0; t--, i++)
                tmp[i] = str[t];
        tmp[i] = 0x0;
        return simple_read_from_buffer(user, size, offs, tmp, i);
}

// 0x0 = '\0'
ssize_t myfd_write(struct file *fp, const char __user *user, size_t size, loff_t *offs)
{
        ssize_t res;

        res = simple_write_to_buffer(str, ARRAY_SIZE(str) - 1, offs, user, size);
        if (res >= 0)
                str[res] = 0x0;
        return res;
}

module_init(myfd_init);
module_exit(myfd_cleanup);
