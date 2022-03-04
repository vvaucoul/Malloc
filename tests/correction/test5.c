/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:29:03 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/03 00:32:18 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "malloc.h"

int main()
{
    void *adr;

    adr = malloc(1024);
    adr = malloc(1024 * 32);
    adr = malloc(1024 * 1024);
    adr = malloc(1024 * 1024 * 16);
    adr = malloc(1024 * 1024 * 128);
    show_alloc_mem();
    return (0);
}