/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:32:47 by achansel          #+#    #+#             */
/*   Updated: 2023/02/08 00:05:23 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

/* License is the only `info` flag that is mandatory */
MODULE_LICENSE("GPL2");

/* __init keyword puts the function in a specific section of the module binary.
 * This section is unloaded after module initialization, in order to not waste RAM.
 * It is not mandatory but it is a good practice for sure */
static int __init insert(void)
{
	printk(KERN_INFO "Hello world !\n");
	return (0);
}

/* Same goes for __exit keyword */
static void __exit remove(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
}

module_init(insert);
module_exit(remove);
