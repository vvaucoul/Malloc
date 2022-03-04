/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:19:50 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 01:10:25 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"
#include "lib_test.h"

static void test_free_01()
{
    ft_printf(WHITE "## TEST 01 ##\n\n" RESET);
    wait_input();

    void *ptr = malloc((sizeof(char) * 20));
    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr);
    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    wait_input();
}

static void test_free_02()
{
    ft_printf(WHITE "## TEST 02 ##\n\n" RESET);
    wait_input();

    void *ptr = malloc((sizeof(char) * 64));
    void *ptr2 = malloc((sizeof(char) * 1024));
    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr);
    ft_free(ptr2);
    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    wait_input();
}

static void test_free_03()
{
    ft_printf(WHITE "## TEST 03 ##\n\n" RESET);
    wait_input();

    void *ptr = malloc(sizeof(char) * 32);
    void *ptr2 = malloc(sizeof(char) * 64);
    void *ptr3 = malloc(sizeof(char) * 1024);
    void *ptr4 = malloc(sizeof(char) * 4096);

    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr);
    show_alloc_mem();

    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr2);
    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr3);
    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr4);
    ft_printf("\n--------------------------\n\n");
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    wait_input();
}

static void test_free_04()
{
    ft_printf(WHITE "## TEST 04 ##\n\n" RESET);
    wait_input();

    void *ptr = malloc(sizeof(char) * 32);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr);
    void *ptr2 = malloc(sizeof(char) * 64);
    void *ptr3 = malloc(sizeof(char) * 1024);
    ptr = malloc(sizeof(char) * 32);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr3);
    ft_free(ptr2);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");

    void *ptr4 = malloc(sizeof(char) * 4096);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr4);
    ft_free(ptr);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ptr = malloc(sizeof(char) * 4096);
    ptr2 = malloc(sizeof(char) * 4096);
    ptr3 = malloc(sizeof(char) * 4096);
    ptr4 = malloc(sizeof(char) * 4096);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr4);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr2);
    ft_free(ptr3);
    ptr3 = malloc(sizeof(char) * 4096);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr3);
    ft_free(ptr);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    wait_input();
}

static void test_free_05()
{
    ft_printf(WHITE "## TEST 05 ##\n\n" RESET);
    wait_input();
    void *ptr = NULL;
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    ft_free(ptr);
    show_alloc_mem();
    ft_printf("\n--------------------------\n\n");
    wait_input();
}

int main(int argc, char const *argv[])
{

    test_free_01();
    test_free_02();
    test_free_03();
    test_free_04();
    test_free_05();
    return (0);
}
