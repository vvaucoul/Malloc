/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 00:29:22 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 00:30:12 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{
    char *addr1;
    char *addr2;
    char *addr3;

    addr1 = (char *)malloc(16 * M);
    strcpy(addr1, "Bonjours\n");
    print(addr1);
    addr2 = (char *)malloc(16 * M);
    addr3 = (char *)realloc(addr1, 128 * M);
    addr3[127 * M] = 42;
    print(addr3);
    return (0);
}