/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_device.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:32:47 by achansel          #+#    #+#             */
/*   Updated: 2023/02/08 15:27:37 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL2");

#define LOGIN "achansel"
#define LOGIN_LEN 8

ssize_t ft_read(struct file *f, char __user *out, size_t len, loff_t *offset)
{
        int             readlen;
        size_t          bytes_copied;

        /* Invalid call to read */
        if (!out)
                return (-EINVAL);
        /* End of 'file' ? */
        if (*offset >= LOGIN_LEN)
                return (0);
        /* How much is remaining to read in 'file' */
        if (len + *offset >= LOGIN_LEN)
                readlen = LOGIN_LEN - *offset;
        else
                readlen = len;
        /* Return it to caller */
        bytes_copied = readlen - copy_to_user(out, LOGIN + *offset, readlen);
        *offset += bytes_copied;
        return (bytes_copied);

}

ssize_t ft_write(struct file *f, const char __user *in, size_t len, loff_t *offset)
{
        char    user_data[LOGIN_LEN];
        int     data_off = 0;

        /* Check length first, allows for opitimization */
        if (len != LOGIN_LEN)
                return (-EINVAL);
        /* Ensure we copy all of it even if it doesn't copy all at once */
        do {
                int l = copy_from_user(user_data + data_off, in + data_off, len - data_off);
                data_off += (len - data_off) - l;
        } while (data_off < len);
        /* Compare what we received and the login string */
        if (memcmp(user_data, LOGIN, LOGIN_LEN))
                return (-EINVAL);
        return (len);
}

static struct file_operations fops = {
    .write          = ft_write,
    .read           = ft_read,
};

static struct miscdevice ft_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "fortytwo",
    .fops = &fops
};

static int __init insert(void)
{
        int status = misc_register(&ft_device);
        if (status)
                pr_err("fortytwo device creation failed\n");
        else
                pr_info("fortytwo device creation succeeded\n");
	return (status);
}
module_init(insert);

static void __exit remove(void)
{
        misc_deregister(&ft_device);
        pr_info("fortytwo device was removed\n");
}
module_exit(remove);
