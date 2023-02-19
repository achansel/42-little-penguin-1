/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:56:23 by achansel          #+#    #+#             */
/*   Updated: 2023/02/19 17:56:26 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mount.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/spinlock.h>
#include <linux/nsproxy.h>
#include <linux/ns_common.h>
#include <linux/poll.h>
#include <linux/mnt_namespace.h>
#include <../fs/mount.h>

MODULE_LICENSE("GPL2");

static struct proc_dir_entry *entry;

/* Simplied version of
 * https://elixir.bootlin.com/linux/latest/source/fs/proc_namespace.c#L101 */
static int mymounts_proc_show(struct seq_file* m, void* v)
{
    struct      mount* mnt;

    list_for_each_entry(mnt, &current->nsproxy->mnt_ns->list, mnt_list) {
       	struct path mnt_path = { .dentry = mnt->mnt.mnt_root, .mnt = &mnt->mnt };
        struct super_block *sb = mnt_path.dentry->d_sb;

        /* Skip first `mount`, that appears to be the VFS / itself */
        if (!strcmp(mnt->mnt_devname, "rootfs"))
                continue ;

        if (sb->s_op->show_devname)
                sb->s_op->show_devname(m, mnt_path.dentry);
        else
                seq_puts(m, mnt->mnt_devname ? mnt->mnt_devname : "none");
        seq_putc(m, ' ');
       	seq_path(m, &mnt_path, " \t\n\\");
        seq_putc(m, '\n');
    }
    return 0;
}

static int mymounts_proc_open(struct inode* inode, struct file* file)
{
    return single_open(file, mymounts_proc_show, NULL);
}

// Define the file operations that will be associated with the /proc/mymounts file
static const struct proc_ops mymounts_proc_fops = {
    .proc_open = mymounts_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init mymounts_init(void)
{
    entry = proc_create("mymounts", 0, NULL, &mymounts_proc_fops);
    if (entry == NULL) {
        printk(KERN_ERR "mymounts_module: failed to create /proc/mymounts file\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "mymounts_module: INSERTED\n");
    return 0;
}

static void __exit mymounts_exit(void)
{
    proc_remove(entry);
    printk(KERN_INFO "mymounts_module: REMOVED\n");
}

module_init(mymounts_init);
module_exit(mymounts_exit);

