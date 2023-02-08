/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugfs_module.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:32:47 by achansel          #+#    #+#             */
/*   Updated: 2023/02/08 19:07:28 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "module.h"

/* Maybe debugfs_create_file_size could've been used for foo ? */
static struct s_debugfs_file   files[] = {
        {"id",      0666,       NULL, {.read = id_read,      .write = id_write}},
        {"foo",     0644,       NULL, {.read = foo_read,     .write = foo_write}} //ensure root is the default owner
};
static struct dentry            *dir = NULL;

static void debugfs_module_cleanup(void)
{
        debugfs_remove_recursive(dir);
}
static int __init insert(void)
{
        int             status;
        struct  dentry  *file;

        /* Create directory fortytwo containing all the files */
        dir = debugfs_create_dir("fortytwo", NULL);
        if (IS_ERR_OR_NULL(dir)) {
                status = (dir ? PTR_ERR(dir) : -ENOMEM);
                goto ret;
        }

        /* Create jiffies file (ifdef so it compiles everywhere) */
#if BITS_PER_LONG == 64
        debugfs_create_u64("jiffies", 0444, dir, (u64*) &jiffies);
#else
        debugfs_create_u32("jiffies", 0444, dir, (u32*) &jiffies);
#endif

        /* Create the files id and foo */
        for (int i = 0; i < ARRAY_SIZE(files); i++) {
                file = debugfs_create_file(files[i].name, files[i].mode, dir, NULL, &(files[i].fops));    
                if (IS_ERR_OR_NULL(file)) {
                        status = (file ? PTR_ERR(file) : -ENOMEM);
                        goto cleanup;
                }
        }

        pr_info("debugfs_module: Initialized successfully.\n");
        return (0);
cleanup:
        debugfs_module_cleanup();
ret:
        pr_err("debugfs_module: Error initializing this module.\n");
	return (status);
}

static void __exit remove(void)
{
        debugfs_module_cleanup();
        pr_info("debugfs_module: Removed successfully.\n");
}

module_init(insert);
module_exit(remove);
MODULE_LICENSE("GPL");

