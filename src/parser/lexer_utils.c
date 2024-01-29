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

void print_lexer_mandatory(t_lex *lexer)
{
	printf("NO: %s\n", lexer->n.content);
	printf("SO: %s\n", lexer->s.content);
	printf("EA: %s\n", lexer->e.content);
	printf("WE: %s\n", lexer->w.content);
	printf("F: %s\n", lexer->c.content);
	printf("C: %s\n", lexer->f.content);
}

void	print_lexer_map(t_map *map)
{
	printf("MAP: %s\n", map->map_element);
}

void print_lexer_extras(t_flag *extras)
{
	while (extras)
	{
		printf("SP: %s\n", extras->content);
		extras = extras->next;
	}
}