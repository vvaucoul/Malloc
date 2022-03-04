/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed_test_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:47:37 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 01:17:53 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include "../../lib_test.h"

bool display_heap = false;

static void speed_test_01()
{
    ft_printf("## SPEED TEST MALLOC 01 ##\n\n");

    void *ptr;
    ptr = malloc(sizeof(char) * 32);
    if (display_heap)
        show_alloc_mem();
}

static void speed_test_02()
{
    ft_printf("## SPEED TEST MALLOC 02 ##\n\n");
    
    void *ptr;
    ptr = malloc(sizeof(char) * 1024);
    if (display_heap)
        show_alloc_mem();
}

static void speed_test_03()
{
    ft_printf("## SPEED TEST MALLOC 03 ##\n\n");
    
    void *ptr;
    for (size_t i = 0; i < 1024; i++)
    {
        ptr = malloc(sizeof(char) * 1024);
    }
    if (display_heap)
        show_alloc_mem();
}

static void speed_test_04()
{
    ft_printf("## SPEED TEST MALLOC 04 ##\n\n");
    
    void *ptr;
    for (size_t i = 0; i < 1024; i++)
    {
        ptr = malloc(sizeof(char) * 10000000);
    }
    if (display_heap)
        show_alloc_mem();
}

static void speed_test_05()
{
    ft_printf("## SPEED TEST MALLOC 05 ##\n\n");

    void *ptr, *ptr2, *ptr3;
    for (size_t i = 0; i < 128; i++)
    {
        ptr = malloc(sizeof(char) * 10000000);
        ptr2 = malloc(sizeof(char) * 10000);
        ptr3 = malloc(sizeof(char) * 100);
    }
    if (display_heap)
        show_alloc_mem();
}

static void speed_test_06()
{
    ft_printf("## SPEED TEST MALLOC 05 ##\n\n");

    void *ptr, *ptr2, *ptr3;
    for (size_t i = 0; i < getpagesize(); i++)
    {
        ptr = malloc(sizeof(char) * SMALL_BLOCK_SIZE + 1);
        ptr2 = malloc(sizeof(char) * TINY_BLOCK_SIZE + 1);
        ptr3 = malloc(sizeof(char) * 2);
    }
    if (display_heap)
        show_alloc_mem();
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        ft_printf("Usage: ./speed_test_malloc [1|2|3|4|5|6] [Display Heap | 1/0]\n");
        return (0);
    }
    if (argv[2][0] == '1')
        display_heap = true;
    else
        display_heap = false;
    if (argv[1][0] == '1')
        speed_test_01();
    else if (argv[1][0] == '2')
        speed_test_02();
    else if (argv[1][0] == '3')
        speed_test_03();
    else if (argv[1][0] == '4')
        speed_test_04();
    else if (argv[1][0] == '5')
        speed_test_05();
    else if (argv[1][0] == '6')
        speed_test_06();
    else
        ft_printf("Usage: ./speed_test_malloc [1|2|3|4|5|6]\n");
}
