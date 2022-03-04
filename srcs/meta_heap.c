/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:48:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 11:34:11 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

enum e_meta_memory_type find_meta_heap(void *ptr)
{
    t_meta_block *blocks = NULL;
    enum e_meta_memory_type heap = TINY;

    while (heap <= LARGE)
    {
        blocks = _g_malloc.heap[heap].block;
        while (blocks && blocks->next)
        {
            if ((void *)blocks + META_BLOCK_SIZE == ptr)
                return (heap);
            blocks = blocks->next;
        }
        ++heap;
    }
    return (-1);
}

bool search_meta_heap(void *ptr)
{
    t_meta_block *blocks = NULL;
    int heap = 0;

    while (heap < 3)
    {
        blocks = _g_malloc.heap[heap].block;
        while (blocks && blocks->next)
        {
            if ((void *)blocks + META_BLOCK_SIZE == ptr)
                return (true);
            blocks = blocks->next;
        }
        ++heap;
    }
    return (false);
}

void *request_memory_block(size_t size)
{
    static void *(*create_new_memory_block[3])(size_t, __uint64_t, short) = {
        &create_new_blocks,
        &create_new_blocks,
        &create_new_blocks_large};

    static void *(*append_new_memory_block[3])(size_t, short) = {
        &append_memory_blocks,
        &append_memory_blocks,
        &append_memory_blocks_large};

    enum e_meta_memory_type __heap = select_heap(size);
    size_t __blocks_size = (__heap == TINY)    ? TINY_BLOCK_SIZE
                           : (__heap == SMALL) ? SMALL_BLOCK_SIZE
                                               : LARGE_BLOCK_SIZE;
    void *data = NULL;

    if (_g_malloc.heap[__heap].block == NULL)
    {
        data = create_new_memory_block[__heap](size, __blocks_size, __heap);
        if (data && __heap == LARGE)
            _g_malloc.heap[__heap].block = data - META_BLOCK_SIZE;
    }
    else
        data = append_new_memory_block[__heap](size, __heap);
    if (data)
        _g_malloc.heap[__heap].size += 1;
    return (data);
}