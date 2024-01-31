/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:18:50 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "parser.h"


void	print_lexer_map(t_map *map)
{
	printf("MAP: %s\n", map->map_element);
}

void print_lexer_elements(t_flag *elements)
{
	while (elements != NULL)
	{
		printf("%s: ", elements->flag);
		printf("%s\n", elements->content);
		elements = elements->next;
	}
}