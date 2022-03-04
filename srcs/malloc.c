/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:47:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 00:39:25 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_malloc _g_malloc;
pthread_mutex_t _g_mutex[4] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};

void *malloc(size_t size)
{
    static bool init = false;
    void *ptr = NULL;

    if (pthread_mutex_lock(&_g_mutex[F_MALLOC]) != 0)
        return (NULL);
    if (!init)
    {
        if (!(init_malloc()))
            return (pthread_mutex_unlock_return(&_g_mutex[F_MALLOC], NULL));
        init = true;
    }
    if (!(ptr = request_memory_block(size)))
        return (pthread_mutex_unlock_return(&_g_mutex[F_MALLOC], NULL));
    return (pthread_mutex_unlock_return(&_g_mutex[F_MALLOC], ptr));
}