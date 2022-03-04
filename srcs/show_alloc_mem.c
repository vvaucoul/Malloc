/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:35:58 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 11:10:02 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static __uint64_t display_heap(t_meta_heap heap)
{
    t_meta_block *block = heap.block;
    size_t current_size;
    __uint64_t total_size = 0;

    while (block && block->next)
    {
        if (block->free == false)
        {
            current_size = block->size;
            total_size += current_size;
            ft_printf("%p - %p : %zu octets\n", block + META_BLOCK_SIZE, block->next, current_size);
        }
        block = block->next;
    }
    return (total_size);
}

void show_alloc_mem(void)
{
    enum e_meta_memory_type heap = TINY;
    __uint64_t total = 0;

    if (pthread_mutex_lock(&_g_mutex[F_SHOW_ALLOC_MEM]) != 0)
        return;
    while (heap <= LARGE)
    {
        ft_printf("%s : %p\n", (heap == TINY) ? "TINY" : (heap == SMALL) ? "SMALL"
                                                                         : "LARGE",
                  _g_malloc.heap[heap].block);
        total += display_heap(_g_malloc.heap[heap]);
        ++heap;
    }
    ft_printf("Total : %llu octets\n", total);
    if (pthread_mutex_unlock(&_g_mutex[F_SHOW_ALLOC_MEM]) != 0)
        return;
}