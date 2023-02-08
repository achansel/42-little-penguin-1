/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:52:10 by achansel          #+#    #+#             */
/*   Updated: 2023/02/08 19:06:23 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "module.h"

#define LOGIN "achansel"
#define LOGIN_LEN 8

ssize_t id_read(struct file *f, char __user *out, size_t len, loff_t *offset)
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

ssize_t id_write(struct file *f, const char __user *in, size_t len, loff_t *offset)
{
        char    user_data[LOGIN_LEN];

        /* Check length first, allows for opitimization */
        if (len != LOGIN_LEN)
                return (-EINVAL);

        /* Safe copy from user */
        if (copy_from_user(user_data, in, len))
                return (-EFAULT);

        /* Compare what we received and the login string */
        if (memcmp(user_data, LOGIN, LOGIN_LEN))
                return (-EINVAL);
        return (len);
}
