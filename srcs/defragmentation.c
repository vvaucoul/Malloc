/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragmentation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:55:47 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 00:27:58 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

// DEFRAGMENTATION

static void merge_meta_blocks(t_meta_block *current, t_meta_block *next)
{
    current->size += next->size + META_BLOCK_SIZE;
    if (next->next)
    {
        current->next = next->next;
        next->next->prev = current;
    }
    else
        current->next = NULL;
}

void defragmentation(t_meta_block *ptr)
{
    t_meta_block *block = ptr;

    if (block->next && block->next->free == true)
        merge_meta_blocks(block, block->next);
    if (block->prev && block->prev->free == true)
        merge_meta_blocks(block->prev, block);
}

// FREE LARGE HEAP

void free_large_heap(t_meta_block *block)
{
    if (!block->prev)
    {
        if (!block->next->next)
            _g_malloc.heap[LARGE].block = NULL;
        else
        {
            block->next->next->prev = NULL;
            _g_malloc.heap[LARGE].block = block->next->next;
        }
    }
    else if (!block->next->next)
        block->prev->next = NULL;
    else
    {
        block->prev->next = block->next->next;
        block->next->next->prev = block->prev;
    }
}