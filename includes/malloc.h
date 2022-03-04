/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 15:49:00 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "../libft/includes/libft.h"

#define META_BLOCK_SIZE (size_t)(sizeof(t_meta_block))
#define META_HEAP_SIZE (size_t)(sizeof(t_meta_heap))
#define ALIGN_BLOCK_SIZE 0x10
#define ALIGN_SIZE(size) ((size)) % ALIGN_BLOCK_SIZE == 0 ? (size) : ((size) + ALIGN_BLOCK_SIZE - ((size)) % ALIGN_BLOCK_SIZE)

#define MIN_META_BLOCK_SIZE (size_t)0x20
#define DEFAULT_OVERHEAD (size_t)(getpagesize() / ALIGN_BLOCK_SIZE)

#define TINY_HEAP_SIZE (size_t)(getpagesize() * 4)
#define TINY_BLOCK_SIZE (size_t)(TINY_HEAP_SIZE / 32)
#define SMALL_HEAP_SIZE (size_t)(getpagesize() * 32)
#define SMALL_BLOCK_SIZE (size_t)(SMALL_HEAP_SIZE / 32)
#define LARGE_HEAP_SIZE (size_t)(getpagesize() * 256)
#define LARGE_BLOCK_SIZE (size_t)((SMALL_BLOCK_SIZE) + 1)

enum e_function
{
    F_MALLOC,
    F_REALLOC,
    F_FREE,
    F_SHOW_ALLOC_MEM
};

enum e_state
{
    FREE,
    ALLOCATED
};

enum e_meta_memory_type
{
    TINY,
    SMALL,
    LARGE
};

typedef struct s_meta_block
{
    size_t size;
    bool free;
    struct s_meta_block *next;
    struct s_meta_block *prev;
} t_meta_block;

typedef struct s_meta_heap
{
    enum e_meta_memory_type type;
    __uint64_t size;
    __uint64_t capacity;
    t_meta_block *block;
} t_meta_heap;

typedef struct s_malloc
{
    t_meta_heap heap[3];
    rlim_t system_limit;
    rlim_t nb_pages;
    size_t page_size;
} t_malloc;

extern t_malloc _g_malloc;
extern pthread_mutex_t _g_mutex[4];

void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void show_alloc_mem(void);
void show_alloc_mem_ex(void);

// META HEAP

void *request_memory_block(size_t size);
bool search_meta_heap(void *ptr);
enum e_meta_memory_type find_meta_heap(void *ptr);

// META BLOCK

void *create_new_blocks(size_t size, __uint64_t blocks_size, short heap);
void *create_new_blocks_large(size_t size, __uint64_t blocks_size, short heap);
void *append_memory_blocks(size_t size, short heap);
void *append_memory_blocks_large(size_t size, short heap);

// UTILS

bool init_malloc(void);
short select_heap(size_t size);
void *ft_mmap(size_t size);
void *pthread_mutex_unlock_return(pthread_mutex_t *mutex, void *ptr);
void print_meta_block_list(t_meta_block *block);

// DEFRAGMENTATION

void defragmentation(t_meta_block *ptr);
void free_large_heap(t_meta_block *block);

#endif