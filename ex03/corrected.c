#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

/* Tell userspace about the sleeps */
int do_work(int *my_int)
{
        int i;
        int y = *my_int;

        for (i = 0; i < my_int; ++i)
                udelay(10);
        if (y < 10)
                pr_info("We slept a long time!");
        return x * y;
}

int my_init(void)
{
        int x = 10;

        return (do_work(&x));
}

void my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
