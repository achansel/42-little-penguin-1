/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:53:02 by achansel          #+#    #+#             */
/*   Updated: 2023/02/08 18:34:05 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/jiffies.h>
#include <linux/err.h>
#include <linux/types.h>
#include <linux/mutex.h>

/* Helper struct to use loop instead of copy pasted code to generate files */
struct s_debugfs_file {
        const char                      *name;
        umode_t                         mode;
        void                            *data;
        struct file_operations          fops;
};

/* id_file.c */
ssize_t id_read(struct file *f, char __user *out, size_t len, loff_t *offset);
ssize_t id_write(struct file *f, const char __user *in, size_t len, loff_t *offset);

/* foo_file.c */
extern  u8 foo_buffer[PAGE_SIZE];
ssize_t foo_read(struct file *f, char __user *out, size_t len, loff_t *offset);
ssize_t foo_write(struct file *f, const char __user *in, size_t len, loff_t *offset);
