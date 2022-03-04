/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:44:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 16:38:37 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

#include <termios.h>
#include <sys/ioctl.h>

#define WHITE "\033[97m"
#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

static struct winsize get_terminal_size()
{
    struct winsize w;

    if (ioctl(0, TIOCGWINSZ, &w) == -1)
        return ((struct winsize){0, 0, 0, 0});
    return (w);
}

static void display_space(size_t size)
{
    size_t i = 0;

    while (i < size)
    {
        write(1, " ", 1);
        ++i;
    }
}

static void display_hex_header(char *str, __uint64_t size)
{
    struct winsize w;

    w = get_terminal_size();
    ft_printf(WHITE);
    for (size_t i = 0; i < w.ws_col; ++i)
        ft_printf("-");
    ft_printf("\n");

    for (size_t i = 0; i < w.ws_col / 2 - ((ft_strlen(str) + ft_nbrlen(size)) / 2); ++i)
        ft_printf(" ");
    ft_printf(WHITE "%s: " RESET, str);
    ft_printf(WHITE "%zu octets\n" RESET, size);

    for (size_t i = 0; i < w.ws_col; ++i)
        ft_printf("-");
    ft_printf("\n");
    ft_printf(RESET);
}

static void display_hex_memory(t_meta_block *block)
{
    char memory[128];
    size_t i = 0, count = 0;
    int tmp = 0;
    void *ptr = (void *)block;
    __uint64_t nbr = (__uint64_t)ptr;

    ft_bzero(memory, 128);
    while (nbr != 0)
    {
        tmp = nbr % 16;
        memory[i] = tmp < 10 ? tmp + 48 : tmp + 55;
        nbr /= 16;
        i++;
        if (count % 2 == 1 && nbr != 0)
        {
            memory[i] = ' ';
            ++i;
        }
        ++count;
    }
    ft_printf("%s", memory);
}

static void display_hex_dump(t_meta_heap heap)
{
    t_meta_block *block = heap.block;
    size_t i = 0;

    while (block && block->next)
    {
        if (block->free == false)
        {
            display_space(get_terminal_size().ws_col / 2 - 128 / 2 + 6);
            ft_printf(BOLD WHITE "[%zu]", i);
            ft_printf(GREEN " [%p]: ", (block + META_BLOCK_SIZE)[0]);
            display_hex_memory(block + META_BLOCK_SIZE);
            ft_printf(" - ");
            display_hex_memory(block->next);
            ft_printf(WHITE " <==> " GREEN);
            display_hex_memory((void *)block + block->size + META_BLOCK_SIZE);
            ft_printf(" - ");
            ft_printf(WHITE "[%zu] " GREEN "Octets" GREEN, block->size);
            ft_printf(" -> ");
            ft_printf(WHITE "[%s]" RESET, (char *)((void *)block + META_BLOCK_SIZE));
            ft_printf("\n" RESET);
            ++i;
        }
        block = block->next;
    }
}

static __uint64_t get_total_size(t_meta_heap heap)
{
    t_meta_block *block = heap.block;
    __uint64_t total = 0;

    while (block && block->next)
    {
        if (block->free == false)
            total += block->size;
        block = block->next;
    }
    return (total);
}

void show_alloc_mem_ex(void)
{
    enum e_meta_memory_type heap = TINY;
    if (pthread_mutex_lock(&_g_mutex[F_SHOW_ALLOC_MEM]) != 0)
        return;
    while (heap <= LARGE)
    {
        display_hex_header((heap == TINY) ? "TINY" : (heap == SMALL) ? "SMALL"
                                                                     : "LARGE",
                           get_total_size(_g_malloc.heap[heap]));
        display_hex_dump(_g_malloc.heap[heap]);
        ++heap;
    }
    if (pthread_mutex_unlock(&_g_mutex[F_SHOW_ALLOC_MEM]) != 0)
        return;
}