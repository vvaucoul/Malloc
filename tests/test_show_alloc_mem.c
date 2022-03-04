/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_show_alloc_mem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:49:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 16:22:09 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_test.h"

int main(void)
{
    size_t i = 0;
    void *ptr = NULL;

    while (i < 32 / 3)
    {
        ptr = malloc(512);
        ++i;
        ft_bzero(ptr, 512);
        ft_memset(ptr, 'a', 8);
    }
    i = 0;
    while (i < 32 / 3)
    {
        ptr = malloc(1024);

        ft_bzero(ptr, 512);
        ft_memset(ptr, 'c', 8);
        ++i;
    }
    i = 0;
    while (i < 32 / 3)
    {
        ptr = malloc(8192);

        ft_bzero(ptr, 512);
        ft_memset(ptr, 'd', 8);
        ++i;
    }
    show_alloc_mem();
    wait_input();
    show_alloc_mem_ex();
    return (0);
}