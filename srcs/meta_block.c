/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:06:48 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 11:38:34 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void *create_new_blocks(size_t size, __uint64_t blocks_size, short heap)
{
    if (!(_g_malloc.heap[heap].block = ft_mmap(ALIGN_SIZE(blocks_size * _g_malloc.page_size))))
        return (NULL);
    _g_malloc.heap[heap].block->size = size;
    _g_malloc.heap[heap].block->free = 0;
    _g_malloc.heap[heap].block->prev = NULL;
    _g_malloc.heap[heap].block->next = (void *)_g_malloc.heap[heap].block + size + META_BLOCK_SIZE;
    _g_malloc.heap[heap].block->next->free = 1;
    _g_malloc.heap[heap].block->next->size = (blocks_size * _g_malloc.page_size) - size - (2 * META_BLOCK_SIZE);
    _g_malloc.heap[heap].block->next->next = NULL;
    _g_malloc.heap[heap].block->next->prev = _g_malloc.heap[heap].block;
    return ((void *)_g_malloc.heap[heap].block + META_BLOCK_SIZE);
}

void *create_new_blocks_large(size_t size, __uint64_t blocks_size, short heap)
{
    t_meta_block *new_large_block = NULL;

    (void)blocks_size;
    (void)heap;
    if (!(new_large_block = ft_mmap(ALIGN_SIZE(size + META_BLOCK_SIZE))))
        return (NULL);
    new_large_block->size = size;
    new_large_block->free = 0;
    new_large_block->next = (void *)new_large_block + META_BLOCK_SIZE + size;
    new_large_block->prev = NULL;
    new_large_block->next->free = 1;
    new_large_block->next->size = 0;
    new_large_block->next->next = NULL;
    new_large_block->next->prev = new_large_block;
    return ((void *)new_large_block + META_BLOCK_SIZE);
}

void *append_memory_blocks(size_t size, short heap)
{
    t_meta_block *blocks = _g_malloc.heap[heap].block;
    t_meta_block *new_block = NULL;
    void *prev = NULL;
    int block_size;

    while (blocks && !(blocks->free == true && blocks->size >= size))
    {
        prev = blocks;
        blocks = blocks->next;
    }
    if (blocks)
    {
        block_size = blocks->size;
        blocks->size = size;
        blocks->prev = prev;
        blocks->free = false;
        new_block = (void *)blocks + META_BLOCK_SIZE;
        if (!blocks->next)
        {
            if (block_size - size - META_BLOCK_SIZE < TINY_HEAP_SIZE && size <= TINY_HEAP_SIZE)
            {
                blocks->next = ft_mmap(ALIGN_SIZE(TINY_HEAP_SIZE * _g_malloc.page_size));
                blocks->next->prev = blocks;
                blocks->next->next = NULL;
                blocks->next->size = block_size - size - META_BLOCK_SIZE + TINY_HEAP_SIZE * _g_malloc.page_size;
                blocks->next->free = true;
            }
            else if (block_size - size - META_BLOCK_SIZE < SMALL_HEAP_SIZE && size > TINY_HEAP_SIZE)
            {
                blocks->next = ft_mmap(ALIGN_SIZE(SMALL_HEAP_SIZE * _g_malloc.page_size));
                blocks->next->prev = blocks;
                blocks->next->next = NULL;
                blocks->next->size = block_size - size - META_BLOCK_SIZE + SMALL_HEAP_SIZE * _g_malloc.page_size;
                blocks->next->free = true;
            }
            else
            {
                blocks->next = (void *)blocks + blocks->size + META_BLOCK_SIZE;
                blocks->next->prev = blocks;
                blocks->next->next = NULL;
                blocks->next->size = block_size - size - META_BLOCK_SIZE;
                blocks->next->free = true;
            }
        }
    }
    return (new_block);
}

void *append_memory_blocks_large(size_t size, short heap)
{
    t_meta_block *block = _g_malloc.heap[heap].block;
    void *new_block = NULL;
    void *save_new_block = NULL;

    if (!(new_block = create_new_blocks_large(size, 0, heap)))
        return (NULL);
    save_new_block = new_block;
    new_block = (void *)new_block - META_BLOCK_SIZE;
    while (block && block->next)
        block = block->next;
    ((t_meta_block *)new_block)->prev = block;
    block->next = (t_meta_block *)new_block;
    return (save_new_block);
}