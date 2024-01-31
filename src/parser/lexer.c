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

char *extract_file(char *map_file)
{
	int	fd;
	char *file = NULL;
	if (map_extension(map_file)) // check map ext
		return(pr_err(INV_EXT), NULL);
	fd = open(map_file, O_RDONLY); // open file
	if (fd == -1)
		return (pr_err(INV_FILE), NULL);
	file = file_to_string(fd);
	close(fd);
	if (!file)
		return(pr_err(MALL_ERR), NULL);
	return (file);
}

bool	mandatory_elements(t_lex *lex)
{
	int	i;	
	char*	flags[6] = {lex->n.content, lex->s.content, lex->w.content, lex->e.content, lex->c.content, lex->f.content};

	i = 0;
	while (i < 6)
	{
		if (flags[i] == NULL)
			return (false);
		i++;
	}
	return (true);
}

int	lex(char *file, t_lex *lexer, t_map *map, t_flag **extras)
{
	int	exit_code;
	int	skip;

	while (*file)
	{
		exit_code = 0;
		skip = 1;
		skip_spaces(&file);
		if (is_valid_element(file))
		{
			exit_code = input_lexer(lexer, file, &skip);
		}
		else if (is_map_element(file) && !only_spaces(file))
		{
			exit_code = map_lex(&file, map, lexer, &skip);
		}
		else if (is_valid_extra(file) && !save_extra_title(extras, &file))
		{
			exit_code = lexer_input_extra(extras, file, &skip);
		}
		else if (!only_spaces(file))
		{
			exit_code = pr_err(INV_ELE);
		}
		if (exit_code)
			return (EXIT_FAILURE);
		if (skip)
			skip_line(&file);
	}
	return (EXIT_SUCCESS);
}

// read the file into one string and lexes the extras into a linked list
int	lexer(t_meta *meta, char *map_file)
{
	char	*file = NULL;
	
	meta->scene_name = map_file;
	file = extract_file(map_file);
	if (!file)
		return(EXIT_FAILURE);
	if (lex(file, &meta->lexer, &meta->map, &meta->extras))
		return (EXIT_FAILURE); //also free everything in case of error!
	return (EXIT_SUCCESS);
}
