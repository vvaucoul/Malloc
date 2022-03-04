/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_thread_safe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:09:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 01:13:34 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <pthread.h>
#include "lib_test.h"

#define NB_THREADS 10
#define LOOPS 500

static void *routine(void *ptr)
{
    void *ptr2 = NULL;
    size_t n_thread = *(size_t *)ptr;
    size_t i = 0;
    usleep(2000000);
    while (i < LOOPS)
    {
        printf(LIGHT_RED "[%zu]"WHITE" MALLOC"GREEN" [%zu]" RESET, n_thread, i);
        if (!(ptr2 = malloc(sizeof(char) * 64)))
        {
            printf(RED "MALLOC FAILED\n" RESET);
            return (NULL);
        }
        printf(WHITE "  ->  REALLOC" GREEN " [%zu]"CYAN" [%zu]" RESET, i, (size_t)128);

        if (!(ptr2 = realloc(ptr2, sizeof(char) * 128)))
        {
            printf(RED "REALLOC FAILED\n" RESET);
            return (NULL);
        }
        printf(WHITE "  ->  FREE"GREEN" [%zu]\n" RESET, i);
        free(ptr2);
        ++i;
    }
    return (NULL);
}

int main(int argc, char const *argv[])
{
    printf("## TEST MALLOC THREAD SAFE ##\n\n");

    pthread_t thread[NB_THREADS] = {0};
    size_t i = 0;

    while (i < NB_THREADS)
    {
        if ((pthread_create(&thread[i], NULL, &routine, &i)))
        {
            printf(RED "Error: pthread_create() failed\n" RESET);
            return (1);
        }
        else
        {
            printf(GREEN "Success: "WHITE"pthread_create() "GREEN"success : Process "LIGHT_RED"[%lu]\n" RESET, thread[i]);
        }
        usleep(50000);
        ++i;
    }
    ft_printf("\n");
    i = 0;
    while (i < NB_THREADS)
    {
        if ((pthread_join(thread[i], NULL)))
        {
            printf(RED "Error: pthread_join() failed\n" RESET);
            return (1);
        }
        i++;
    }
    return (0);
}
