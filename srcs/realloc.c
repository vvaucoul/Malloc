/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:48:58 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 11:19:58 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *new_ptr = NULL;

    if (pthread_mutex_lock(&_g_mutex[F_REALLOC]) != 0)
        return (NULL);
    if (!size)
    {
        if (ptr)
        {
            free(ptr);
            return (pthread_mutex_unlock_return(&_g_mutex[F_REALLOC], NULL));
        }
    }
    if (!ptr)
        return (pthread_mutex_unlock_return(&_g_mutex[F_REALLOC], malloc(size)));
    else if (!search_meta_heap(ptr))
        return (pthread_mutex_unlock_return(&_g_mutex[F_REALLOC], NULL));
    else
    {
        if (!(new_ptr = malloc(size)))
            return (pthread_mutex_unlock_return(&_g_mutex[F_REALLOC], NULL));
        ft_memcpy(new_ptr, ptr, ((t_meta_block *)ptr - 1)->size > size ? size : ((t_meta_block *)ptr - 1)->size);
        free(ptr);
    }
    return (pthread_mutex_unlock_return(&_g_mutex[F_REALLOC], new_ptr));
}