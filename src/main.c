/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:25:21 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/26 17:37:05 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "meta.h"
#include <ctype.h>
#include <stdio.h>

void test_func();
void sortSprites(int* order, double* dist, int amount);

int main(int argc, char *argv[])
{
	// return (cub3d(argc, argv));
	test_func();
	sortSprites(NULL, NULL, 0);
}
