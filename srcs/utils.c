/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:27:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 11:02:01 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void *ft_mmap(size_t size)
{
    void *ptr;

    ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED)
        return (NULL);
    ++_g_malloc.nb_pages;
    return (ptr);
}

void *pthread_mutex_unlock_return(pthread_mutex_t *mutex, void *ptr)
{
    if (pthread_mutex_unlock(mutex) != 0)
        return (NULL);
    return (ptr);
}

bool init_malloc(void)
{
    struct rlimit rl;

    if (getrlimit(RLIMIT_DATA, &rl) == -1)
        return (false);
    if (rl.rlim_cur == RLIM_INFINITY)
        rl.rlim_cur = rl.rlim_max;
    _g_malloc.page_size = getpagesize();
    _g_malloc.system_limit = rl.rlim_cur;
    _g_malloc.nb_pages = 0;

    for (enum e_meta_memory_type __heap = TINY; __heap <= LARGE; ++__heap)
    {
        _g_malloc.heap[__heap].size = 0;
        _g_malloc.heap[__heap].block = NULL;
        _g_malloc.heap[__heap].capacity = __heap == TINY ? TINY_HEAP_SIZE : __heap == SMALL ? SMALL_HEAP_SIZE
                                                                                            : 0;
    }
    return (true);
}

static bool heap_as_enough_space(enum e_meta_memory_type heap)
{
    if (_g_malloc.heap[heap].size >= _g_malloc.heap[heap].capacity)
        return (false);
    return (true);
}

short select_heap(size_t size)
{
    if (size <= TINY_BLOCK_SIZE)
    {
        if (heap_as_enough_space(TINY))
            return (TINY);
        else
            return (select_heap(SMALL_BLOCK_SIZE));
    }
    else if (size <= SMALL_BLOCK_SIZE)
    {
        if (heap_as_enough_space(SMALL))
            return (SMALL);
        else
            return (select_heap(SMALL_BLOCK_SIZE + 1));
    }
    return (LARGE);
}

void print_meta_block_list(t_meta_block *block)
{
    size_t __index = 0;

    while (block && block->next)
    {
        ft_printf("[%zu] Meta Block: [%p]\n", __index, block);
        ft_printf("\tSize: %zu\n", block->size);
        ft_printf("\tFree: %d\n", block->free);
        ft_printf("\tNext: %p\n", block->next);
        ft_printf("\tPrev: %p\n", block->prev);
        block = block->next;
        __index++;
    }
}