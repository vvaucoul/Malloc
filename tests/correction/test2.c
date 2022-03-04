/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:14:43 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/03/02 17:22:39 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int main(int argc, char const *argv[])
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char *)malloc(1024);
        addr[0] = 42;
        free(addr);
        i++;
    }
    return (0);
}
