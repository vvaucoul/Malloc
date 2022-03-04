/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 18:34:40 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 11:45:34 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_test.h"

void test_realloc_01()
{
    char *ptr = NULL;

    display_header("TEST REALLOC - 01");
    ft_printf(WHITE "- Realloc *2 size\n" RESET);
    wait_input();

    if (!(ptr = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Error: malloc failed\n" RESET);
        return;
    }
    ft_bzero(ptr, 20);
    ft_memset(ptr, 'a', 19);
    ft_printf(WHITE "- TEST 01 : PTR: [%s]\n" RESET, ptr);
    show_alloc_mem();
    ptr = realloc(ptr, sizeof(char) * 40);
    ft_bzero(ptr, 40);
    ft_memset(ptr, 'b', 39);
    ft_printf(WHITE "- TEST 01 : PTR REALLOC: [%s]\n" RESET, ptr);
    show_alloc_mem();
    ft_printf("\n");
    free(ptr);
    show_alloc_mem();
}

void test_realloc_02()
{
    char *ptr = NULL, *ptr2 = NULL, *ptr3 = NULL;

    display_header("TEST REALLOC - 02");
    ft_printf(WHITE "- Realloc multiple ptr\n" RESET);
    wait_input();

    if (!(ptr = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Error: malloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, 20);
    ft_memset(ptr, 'a', 19);
    ft_printf(WHITE "- TEST 02 : PTR: [%s]\n" RESET, ptr);
    if (!(ptr = realloc(ptr, sizeof(char) * 40)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    ft_bzero(ptr, 40);
    ft_memset(ptr, 'b', 39);
    ft_printf(WHITE "- TEST 02 : PTR: [%s]\n" RESET, ptr);
    show_alloc_mem();

    if (!(ptr2 = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Error: malloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr2, 20);
    ft_memset(ptr2, 'c', 19);
    ft_printf(WHITE "- TEST 02 : PTR: [%s]\n" RESET, ptr2);
    if (!(ptr2 = realloc(ptr2, sizeof(char) * 40)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    ft_bzero(ptr2, 40);
    ft_memset(ptr2, 'd', 39);
    ft_printf(WHITE "- TEST 02 : PTR: [%s]\n" RESET, ptr2);
    show_alloc_mem();

    if (!(ptr3 = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Error: malloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr3, 20);
    ft_memset(ptr3, 'e', 19);
    ft_printf(WHITE "- TEST 02 : PTR: [%s]\n" RESET, ptr3);
    free(ptr);
    free(ptr2);
    free(ptr3);
    show_alloc_mem();
}

void test_realloc_03()
{
    char *ptr = NULL;

    display_header("TEST REALLOC - 03");
    ft_printf(WHITE "- Realloc in each heap\n" RESET);
    wait_input();

    if (!(ptr = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Error: malloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, 20);
    ft_memset(ptr, 'a', 19);
    ft_printf(WHITE "- TEST 03 : PTR: [%s]\n" RESET, ptr);
    if (!(ptr = realloc(ptr, sizeof(char) * 20)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_printf(WHITE "- TEST 03 : PTR: [%s]\n" RESET, ptr);
    if (!(ptr = realloc(ptr, sizeof(char) * TINY_BLOCK_SIZE - 1)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, TINY_BLOCK_SIZE - 1);
    ft_memset(ptr, 'b', TINY_BLOCK_SIZE - 2);
    ft_printf(WHITE "- TEST 03 : PTR: [%s]\n" RESET, ptr);
    if (!(ptr = realloc(ptr, sizeof(char) * SMALL_BLOCK_SIZE - 1)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, SMALL_BLOCK_SIZE - 1);
    ft_memset(ptr, 'c', SMALL_BLOCK_SIZE - 2);
    ft_printf(WHITE "- TEST 03 : PTR: [%s]\n" RESET, ptr);
    if (!(ptr = realloc(ptr, sizeof(char) * SMALL_BLOCK_SIZE + 1)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, SMALL_BLOCK_SIZE + 1);
    ft_memset(ptr, 'd', SMALL_BLOCK_SIZE);
    ft_printf(WHITE "- TEST 03 : PTR: [%s]\n" RESET, ptr);
    free(ptr);
    show_alloc_mem();
}

static void test_realloc_04()
{
    display_header("TEST REALLOC - 04");
    ft_printf(WHITE "- Realloc in large heap\n" RESET);
    wait_input();

    char *ptr = NULL;

    if (!(ptr = malloc(sizeof(char) * SMALL_BLOCK_SIZE)))
    {
        ft_printf(RED "Error: malloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, SMALL_BLOCK_SIZE);
    ft_memset(ptr, 'a', SMALL_BLOCK_SIZE - 1);
    ft_printf(WHITE "- TEST 04 : PTR: [%s]\n" RESET, ptr);

    if (!(ptr = realloc(ptr, sizeof(char) * SMALL_BLOCK_SIZE + 1)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, SMALL_BLOCK_SIZE + 1);
    ft_memset(ptr, 'b', SMALL_BLOCK_SIZE);
    ft_printf(WHITE "- TEST 04 : PTR: [%s]\n" RESET, ptr);

    if (!(ptr = realloc(ptr, sizeof(char) * LARGE_BLOCK_SIZE * 2)))
    {
        ft_printf(RED "Error: realloc failed\n" RESET);
        return;
    }
    show_alloc_mem();
    ft_bzero(ptr, LARGE_BLOCK_SIZE * 2);
    ft_memset(ptr, 'c', LARGE_BLOCK_SIZE * 2 - 1);
    ft_printf(WHITE "- TEST 04 : PTR: [%s]\n" RESET, ptr);
    free(ptr);
    show_alloc_mem();
}

void test_realloc_05()
{
    display_header("TEST REALLOC - 05");
    ft_printf(WHITE "- Realloc in loop\n" RESET);

    char *ptr = NULL;
    int i = 0;
    int loops = getpagesize();

    while (i < loops)
    {
        if (!(ptr = realloc(ptr, sizeof(char) * (4097))))
        {
            ft_printf(RED "Error: realloc failed\n" RESET);
            return;
        }
        ft_printf("- Realloc [%d] : PTR: [%p] -> [%d]\n", i, ptr, (i * 100) / loops);
        ++i;
        usleep(1000);
    }
    show_alloc_mem();
    free(ptr);
    show_alloc_mem();
}

int main(int argc, char const **argv)
{
    test_realloc_01();
    test_realloc_02();
    test_realloc_03();
    test_realloc_04();
    test_realloc_05();
    return (0);
}
