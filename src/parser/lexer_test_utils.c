/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_test_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 17:42:37 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "parser.h"

void	print_lexer_map(t_map *map)
{
	printf("MAP:\n%s\n\n", map->map_element);
}

void	print_lexer_elements(t_flag *elements)
{
	uint32_t	counter;

	counter = 0;
	while (elements != NULL)
	{
		printf("KEY_%d %s\n", counter, elements->flag);
		printf("VALUE_%d %s\n", counter, elements->content);
		elements = elements->next;
		counter++;
	}
}
