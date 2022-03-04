/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:53:34 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 00:38:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void free(void *ptr)
{
    t_meta_block *block = NULL;
    enum e_meta_memory_type heap;

    if (pthread_mutex_lock(&_g_mutex[F_FREE]) != 0)
        return;
    if (ptr && search_meta_heap(ptr))
    {
        block = ptr - META_BLOCK_SIZE;
        heap = find_meta_heap(ptr);
        if (block->size > SMALL_HEAP_SIZE)
        {
            free_large_heap(block);
            if ((munmap(block, block->size + META_BLOCK_SIZE)) == -1)
            {
                if (pthread_mutex_unlock(&_g_mutex[F_FREE]) != 0)
                    return;
                return;
            }
            ptr = NULL;
        }
        else if (block->free == false)
        {
            block->free = true;
            defragmentation(block);
        }
        if (_g_malloc.heap[heap].size > 0)
            _g_malloc.heap[heap].size -= 1;
    }
    if (pthread_mutex_unlock(&_g_mutex[F_FREE]) != 0)
        return;
}