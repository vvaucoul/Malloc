/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:18:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 11:47:31 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_test.h"

#define USE_FREE false

static void test_malloc_01()
{
    char *ptr = NULL;

    display_header("TEST MALLOC 01 [SIMPLE]");
    ft_printf(WHITE "- Allocate 20 bytes & fill wih a\n" RESET);
    wait_input();

    if (!(ptr = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Malloc Error\n" RESET);
        ft_printf(RED "FAILED at test 01\n" RESET);
        return;
    }
    ft_bzero(ptr, 20);
    ft_memset(ptr, 'a', 19);
    ft_printf(WHITE "- TEST 01 : PTR: [%s]\n" RESET, ptr);
    add_ptr(ptr);
}

static void test_malloc_02()
{
    char *ptr = NULL, *ptr2 = NULL, *ptr3 = NULL;

    display_header("TEST MALLOC 02 [SIMPLE]");
    ft_printf(WHITE "- Allocate multiple ptr\n" RESET);
    wait_input();

    if (!(ptr = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Malloc Error\n" RESET);
        ft_printf(RED "FAILED at test 02\n" RESET);
        return;
    }
    ft_bzero(ptr, 20);
    ft_memset(ptr, 'a', 19);
    ft_printf(WHITE "- TEST 02 : PTR: [%s]\n" RESET, ptr);

    if (!(ptr2 = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Malloc Error\n" RESET);
        ft_printf(RED "FAILED at test 02\n" RESET);
        return;
    }
    ft_bzero(ptr2, 20);
    ft_memset(ptr2, 'b', 19);
    ft_printf(WHITE "- TEST 02 : PTR2: [%s]\n" RESET, ptr2);

    if (!(ptr3 = malloc(sizeof(char) * 20)))
    {
        ft_printf(RED "Malloc Error\n" RESET);
        ft_printf(RED "FAILED at test 02\n" RESET);
        return;
    }
    ft_bzero(ptr3, 20);
    ft_memset(ptr3, 'c', 19);
    ft_printf(WHITE "- TEST 02 : PTR3: [%s]\n" RESET, ptr3);
    add_ptr(ptr);
    add_ptr(ptr2);
    add_ptr(ptr3);
}

static void test_malloc_03()
{
    display_header(WHITE "TEST MALLOC 03 [SIMPLE]" RESET);
    ft_printf(WHITE "- Allocate ptr in array\n" RESET);
    wait_input();

    char *ptr[3] = {NULL};

    for (size_t i = 0; i < 3; i++)
    {
        if (!(ptr[i] = malloc(sizeof(char) * 20)))
        {
            ft_printf(RED "Malloc Error\n" RESET);
            ft_printf(RED "FAILED at test 03\n" RESET);
            return;
        }
        ft_bzero(ptr[i], 20);
        ft_memset(ptr[i], 'a' + i, 19);
        ft_printf(WHITE "- TEST 03 : PTR[%d]: [%s]\n" RESET, i, ptr[i]);
        add_ptr(ptr[i]);
    }
}

static void test_malloc_04()
{
    display_header(WHITE "TEST MALLOC 04 [SIMPLE]" RESET);
    ft_printf(WHITE "- TINY & SMALL Allocations : %d | %d\n" RESET, MALLOC_TINY, MALLOC_SMALL);
    wait_input();

    char *ptr = NULL;
    char *ptr2 = NULL;

    if (!(ptr = malloc(sizeof(char) * MALLOC_TINY)))
    {
        ft_printf(RED "Malloc Error\n" RESET);
        ft_printf(RED "FAILED at test 04\n" RESET);
        return;
    }
    ft_bzero(ptr, MALLOC_TINY);
    ft_memset(ptr, 'a', MALLOC_TINY - 1);
    ft_printf(WHITE "- TEST 04 : PTR: [%s]\n" RESET, ptr);
    wait_input();
    if (!(ptr2 = malloc(sizeof(char) * MALLOC_SMALL)))
    {
        ft_printf(RED "Malloc Error\n" RESET);
        ft_printf(RED "FAILED at test 04\n" RESET);
        return;
    }
    ft_bzero(ptr2, MALLOC_SMALL);
    ft_memset(ptr2, 'b', MALLOC_SMALL - 1);
    ft_printf(WHITE "- TEST 04 : PTR2: [%s]\n" RESET, ptr2);
    add_ptr(ptr);
    add_ptr(ptr2);
}

static void test_malloc_05()
{
    display_header(WHITE "TEST MALLOC 05 [SIMPLE]" RESET);
    ft_printf(WHITE "- Large allocations\n" RESET);
    wait_input();

    char *ptr = NULL;

    if (!(ptr = malloc(sizeof(char) * (MALLOC_LARGE))))
    {
        ft_printf(RED "Malloc Error\n" RESET);
        ft_printf(RED "FAILED at test 05\n" RESET);
        return;
    }
    ft_bzero(ptr, MALLOC_LARGE);
    ft_memset(ptr, 'a', MALLOC_LARGE - 1);
    ft_printf(WHITE "- TEST 05 : PTR: [%s]\n" RESET, ptr);
    add_ptr(ptr);
}

static void test_malloc_06()
{
    display_header(WHITE "TEST MALLOC 06 [SIMPLE]" RESET);
    ft_printf(WHITE "- 1024 allocations for TINY SMALL & LARGE\n" RESET);
    wait_input();

    char *ptr = NULL;

    size_t i = 0, j = 0, size = 0;
    while (j < 3)
    {
        i = 0;
        size = (j == 0) ? MALLOC_TINY : ((j == 1) ? MALLOC_SMALL : MALLOC_LARGE);
        while (i < 1024)
        {
            if (!(ptr = malloc(sizeof(char) * (size))))
            {
                ft_printf(RED "Malloc Error\n" RESET);
                ft_printf(RED "FAILED at test 06\n" RESET);
                return;
            }
            else
            {
                ft_printf("Malloc [%d][%d] : [%zu] | %p\n", j, i, size, ptr);
                usleep(1000);
            }
            ++i;
        }
        ++j;
    }
    ft_printf(WHITE "- TEST 06 : Done...\n" RESET);
}

static void test_malloc_07()
{
    display_header(WHITE "TEST MALLOC 07 [HUGE]" RESET);
    ft_printf(WHITE "- Fill Heap TINY [%d] + 1\n" RESET, TINY_HEAP_SIZE);
    wait_input();

    char *ptr = NULL;
    size_t i = 0;

    while (i < TINY_HEAP_SIZE + 1)
    {
        if (!(ptr = malloc(sizeof(char) * (2))))
        {
            ft_printf(RED "Malloc Error\n" RESET);
            ft_printf(RED "FAILED at test 07\n" RESET);
            return;
        }
        ++i;
    }
    // exit(0);
}

static void test_malloc_08()
{
    display_header(WHITE "TEST MALLOC 08 [HUGE - 2]" RESET);
    ft_printf(WHITE "- Fill Heap TINY & SMALL [%d] + 1\n" RESET, TINY_HEAP_SIZE + SMALL_HEAP_SIZE);
    wait_input();

    char *ptr = NULL;
    size_t i = 0;
    size_t percent = 0;

    while (i < TINY_HEAP_SIZE + SMALL_HEAP_SIZE + 1)
    {
        percent = (i * 100) / (TINY_HEAP_SIZE + SMALL_HEAP_SIZE);
        ft_printf(GREEN "Alloc: " WHITE "[%d / %d -> " BLUE "[%d]" WHITE "]\n" RESET, i, TINY_HEAP_SIZE + SMALL_HEAP_SIZE + 1, percent);
        if (!(ptr = malloc(sizeof(char) * (2))))
        {
            ft_printf(RED "Malloc Error\n" RESET);
            ft_printf(RED "FAILED at test 08\n" RESET);
            return;
        }
        ++i;
    }

    show_alloc_mem();

    ft_printf(WHITE "\n- Fill Heap LARGE with 1024 loops + 1\n" RESET);
    wait_input();

    i = 0;
    while (i < 1024)
    {
        percent = (i * 100) / (1024);
        ft_printf(GREEN "Alloc: " WHITE "[%d / %d -> " BLUE "[%d]" WHITE "]\n" RESET, i, 1024, percent);
        if (!(ptr = malloc(sizeof(char) * (MALLOC_LARGE))))
        {
            ft_printf(RED "Malloc Error\n" RESET);
            ft_printf(RED "FAILED at test 08\n" RESET);
            return;
        }
        usleep(1000);
        ++i;
    }
}

static void test_malloc_09()
{
    display_header(WHITE "TEST MALLOC 09 [LARGE HEAP]" RESET);
    ft_printf(WHITE "- Try to fill large heap [%d]\n" RESET, LARGE_HEAP_SIZE / (getpagesize() / 64));
    wait_input();

    size_t loops = LARGE_HEAP_SIZE / (getpagesize() / 64);
    char *ptr = NULL;
    size_t i = 0;

    srand(time(NULL));
    while (i < loops)
    {
        ft_printf(WHITE "- " BLUE "[%zu / %zu]" WHITE " Alloc [%zu] -> " BLUE "[%zu]\n" RESET, i, loops, SMALL_BLOCK_SIZE + 1, (i * 100) / loops);
        if (!(ptr = malloc(sizeof(char) * (SMALL_BLOCK_SIZE + 1))))
        {
            ft_printf(RED "Malloc Error\n" RESET);
            ft_printf(RED "FAILED at test 09\n" RESET);
            return;
        }
        ++i;
    }
}

static void test_malloc_10()
{
    display_header(WHITE "TEST MALLOC 10 [DESTRUCTOR]" RESET);
    ft_printf(WHITE "- Malloc Destructor\n" RESET);
    ft_printf(RED "\033[5m- BE CAREFUL ! THIS TEST COULD CRASH THE SYSTEM !\n" RESET);
    wait_input();

    struct rlimit rl;

    size_t systemlimit = sysconf(_SC_PAGESIZE) * sysconf(_SC_PHYS_PAGES);
    getrlimit(RLIMIT_AS, &rl);

    ft_printf(WHITE "- System Limit: [");
    display_unsigned_long_long(systemlimit);
    ft_printf("]\n" RESET);

    ft_printf(WHITE "- Real System Limit: Current: [");
    display_unsigned_long_long(rl.rlim_cur);
    ft_printf("]\n" RESET);

    ft_printf(WHITE "- Real System Limit: Max: [");
    display_unsigned_long_long(rl.rlim_max);
    ft_printf("]\n\n" RESET);
    wait_input();

    unsigned long long loops = rl.rlim_max > rl.rlim_cur ? rl.rlim_max : rl.rlim_cur;
    unsigned long long i = 0, j = 0;

    char *ptr = NULL;
    size_t current_heap_attack = 0;
    size_t percent = 0;
    static bool do_once = true, do_once_tiny = true;

    while (i < loops)
    {
        ft_printf(WHITE "- Alloc: [");
        display_unsigned_long_long(i);
        ft_printf("]\n" RESET, i);

        if (j == 0)
            j = 1;
        percent = (j * 100) / (current_heap_attack == 0 ? TINY_HEAP_SIZE : current_heap_attack == 1 ? SMALL_HEAP_SIZE
                                                                                                    : LARGE_HEAP_SIZE);
        ft_printf(RED "- FORCE HEAP [%s] -> " WHITE "[%d]" RED "\n" RESET, current_heap_attack == 0 ? "TINY" : (current_heap_attack == 1 ? "SMALL" : "LARGE"), percent);

        if (!(ptr = malloc(sizeof(char) * (2))))
        {
            ft_printf(RED "Malloc Error\n" RESET);
            ft_printf(RED "FAILED at test 10\n" RESET);
            break;
        }
        else
        {
            ft_bzero(ptr, 2);
            ft_memset(ptr, 'A', 1);
            ft_printf(GREEN "- PTR [%p]\n\n" RESET, ptr);
        }
        ++i;
        ++j;
        if (i > TINY_HEAP_SIZE)
        {
            if (do_once_tiny)
            {
                current_heap_attack = 1;
                do_once_tiny = false;
                j = 0;
            }
        }
        if (i > SMALL_HEAP_SIZE)
        {
            if (do_once)
            {
                current_heap_attack = 2;
                ft_printf(RED "\033[5m"
                              "TINY/SMALL Memory reached limits !!!\n" RESET);
                wait_input();
                do_once = false;
                j = 0;
            }
        }
    }
}

static void display()
{
    ft_printf("usage:\t./test_malloc [test: [BASIC: 0 | HUGE: 1 | HUGE_2: 2 | LARGE_HEAP: 3 | DESTRUCTOR: 4]]\n\n");
    ft_printf("\t- BASICS: basic malloc tests\n");
    ft_printf("\t- HUGE: Fill TINY Heap + 1 (%d) allocations\n", MALLOC_TINY + 1);
    ft_printf("\t- HUGE_2: Fill SMALL Heap + 1 (%d) allocations\n", MALLOC_TINY + MALLOC_SMALL + 1);
    ft_printf("\t- LARGE_HEAP: Try to fill large heap !");
    ft_printf("\t- DESTRUCTOR: malloc destructor [Try to crash memory system heap !]\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        display();
        return (0);
    }
    else if (argv[1][0] == '0')
    {
        test_malloc_01();
        show_alloc_mem_free(USE_FREE);
        test_malloc_02();
        show_alloc_mem_free(USE_FREE);
        test_malloc_03();
        show_alloc_mem_free(USE_FREE);
        test_malloc_04();
        show_alloc_mem_free(USE_FREE);
        test_malloc_05();
        show_alloc_mem_free(USE_FREE);
        test_malloc_06();
        show_alloc_mem_free(USE_FREE);
    }
    else if (argv[1][0] == '1')
    {
        test_malloc_07();
        show_alloc_mem_free(USE_FREE);
    }
    else if (argv[1][0] == '2')
    {
        test_malloc_08();
        show_alloc_mem_free(USE_FREE);
    }
    else if (argv[1][0] == '3')
    {
        test_malloc_09();
        show_alloc_mem_free(USE_FREE);
    }
    else if (argv[1][0] == '4')
    {
        test_malloc_10();
        show_alloc_mem_free(USE_FREE);
    }
    else
    {
        display();
        return (0);
    }
    return (0);
}