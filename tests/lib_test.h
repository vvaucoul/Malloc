/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:54:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/02 14:35:33 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_TEST_H
#define LIB_TEST_H

#include "../includes/malloc.h"
#include <termios.h>
#include <sys/ioctl.h>

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define LIGHT_GRAY "\033[37m"
#define DARK_GRAY "\033[90m"
#define LIGHT_RED "\033[91m"
#define LIGHT_GREEN "\033[92m"
#define LIGHT_YELLOW "\033[93m"
#define LIGHT_BLUE "\033[94m"
#define LIGHT_MAGENTA "\033[95m"
#define LIGHT_CYAN "\033[96m"
#define WHITE "\033[97m"
#define RESET "\033[0m"

#define MALLOC_TINY TINY_BLOCK_SIZE
#define MALLOC_SMALL SMALL_BLOCK_SIZE
#define MALLOC_LARGE MALLOC_SMALL + 1

void wait_input();
void display_header(const char *str);
void display_unsigned_long_long(unsigned long long nbr);
void show_alloc_mem_free(bool free_ptr);

void show_alloc_mem();

void show_alloc_mem_free(bool free_ptr);
void add_ptr(void *ptr);

extern void *_g_current_ptr[];

#endif