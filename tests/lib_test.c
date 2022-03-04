/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:12:37 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/02 16:54:14 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_test.h"

void *_g_current_ptr[] = {NULL};

static void free_current_ptr()
{
    if (_g_current_ptr[0])
    {
        for (int i = 0; _g_current_ptr[i]; i++)
            free(_g_current_ptr[i]);
    }
}

void add_ptr(void *ptr)
{
    if (ptr)
    {
        int i = 0;
        for (; _g_current_ptr[i]; i++)
            ;
        _g_current_ptr[i] = ptr;
        _g_current_ptr[i + 1] = NULL;
    }
}

void show_alloc_mem_free(bool free_ptr)
{
    show_alloc_mem();
    if (free_ptr == true)
        free_current_ptr();
}

void wait_input()
{
    char c;

    while (read(0, &c, 1))
    {
        if (c == '\n')
            break;
    };
}

static struct winsize get_terminal_size()
{
    struct winsize w;

    if (ioctl(0, TIOCGWINSZ, &w) == -1)
        return ((struct winsize){0, 0, 0, 0});
    return (w);
}

void display_header(const char *str)
{
    struct winsize w;

    w = get_terminal_size();

    ft_printf(WHITE);
    for (size_t i = 0; i < w.ws_col; ++i)
        ft_printf("-");
    ft_printf("\n");

    for (size_t i = 0; i < w.ws_col / 2 - ft_strlen(str) / 2; ++i)
        ft_printf(" ");
    ft_printf(WHITE "%s\n" RESET, str);

    for (size_t i = 0; i < w.ws_col; ++i)
        ft_printf("-");
    ft_printf("\n");
    ft_printf(RESET);
}

void display_unsigned_long_long(unsigned long long nbr)
{
    if (nbr >= 10)
        display_unsigned_long_long(nbr / 10);
    ft_putchar(nbr % 10 + '0');
}