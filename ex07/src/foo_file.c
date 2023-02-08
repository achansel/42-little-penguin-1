/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:22:00 by achansel          #+#    #+#             */
/*   Updated: 2023/02/08 20:04:09 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "module.h"

DEFINE_MUTEX(foo_mutex);
u8      foo_buffer[PAGE_SIZE];
static size_t  foo_buffer_len = 0;

ssize_t foo_read(struct file *f, char __user *out, size_t len, loff_t *offset)
{
        int             readlen;
        size_t          status;

        mutex_lock(&foo_mutex);

        /* Invalid call to read */
        if (!out) {
                status = -EINVAL;
                goto ret;
        }

        /* End of 'file' ? */
        if (*offset >= foo_buffer_len) {
                status = 0;
                goto ret;
        }

        /* How much is remaining to read in 'file' */
        if (len + *offset >= foo_buffer_len)
                readlen = foo_buffer_len - *offset;
        else
                readlen = len;
        /* Return it to caller */
        status = readlen - copy_to_user(out, foo_buffer + *offset, readlen);
        *offset += status;
ret:
        mutex_unlock(&foo_mutex);
        return (status);
}

ssize_t foo_write(struct file *f, const char __user *in, size_t len, loff_t *offset)
{
        int     not_copied;
        int     status;

        mutex_lock(&foo_mutex);

        /* We can only store up to a page size of data */
        if (len > PAGE_SIZE) {
                status = -EINVAL;
                goto ret;
        }

        /* Safe copy from user */
        if ((not_copied = copy_from_user(foo_buffer, in, len))) {
                foo_buffer_len = len - not_copied;
                status = -EFAULT;
                goto ret;
        }
        status = foo_buffer_len = len;
ret:
        mutex_unlock(&foo_mutex);
        return (status);
}
