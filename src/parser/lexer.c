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

// mallocs the paths to NO, SO, WE, EA elements
char	*get_val(char *file)
{
	int		i;
	char	*val;

	i = 0;
	skip_spaces(&file);
	while (file[i] && file[i] != '\n')
		i++;
	if (i)
	{
		val = ft_substr(file, 0, i);
		if (!val)
			return (NULL);
		return (val);
	}
	return (ft_strdup(""));
}

int	input_lexer(t_lex *lex, char *file, int *skip)
{
	char	element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
	char**	content[6] = {&lex->n.content, &lex->s.content, &lex->w.content, &lex->e.content, &lex->c.content, &lex->f.content};
	int i;

	i = 0;
	*skip = 1;
	skip_spaces(&file);
	while (i < 6)
	{
		if (*file && *file == element[i])
		{
			if (*content[i])
				return (pr_err(DUP_ELEMENTS));
			*content[i] = get_val(file + 2);
			if (!(content[i]))
				return (pr_err(MALL_ERR), EXIT_FAILURE);
			if (!ft_strncmp(*content[i], "", 1))
				return (pr_err(M_PATH), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
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

int	end_of_map(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (valid_map_char(file[i]) || file[i] == '\n')
			i++;
		if (only_spaces(file))
			break ;
	}
	return (i);
}

int	input_map_lexer(char *file, t_map *map)
{
	int	i = 0;

	if (*file)
	{
		i = end_of_map(file);
		map->map_element = ft_substr(file, 0, i);
		if (!map->map_element)
			return (pr_err(MALL_ERR));
		return (EXIT_SUCCESS);
	}

	return (pr_err(MISSING_MAP));
}

void	skip_map_element(char **file, int *skip)
{
	*skip = 0;
	while (*file)
	{
		if (is_map_element(*file))
			skip_line(file);
		if (only_spaces(*file) || !is_map_element(*file))
			break ;
	}
}

bool	is_valid_extra(char *file)
{
	if (*file && !ft_strncmp(file, "SP", 2))
		return (true);
	return (false);
}

int	lexer_input_extra(t_flag *extras, char *file, int *skip)
{
	t_flag *new_node;
	new_node = malloc(sizeof(t_flag) * 1);
	if (!new_node)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	new_node->content = get_val(file);
	if (extras == NULL)
		extras = new_node;
	else
	{
		while (extras->next == NULL)
			extras = extras->next;
		extras->next = new_node;
	}
	*skip = 1;
	return (EXIT_SUCCESS);
}

int	lex(char *file, t_lex *lexer, t_map *map, t_flag *extras)
{
	int	exit_code;
	int	skip;

	skip = 1;
	exit_code = 0;
	while (*file)
	{
		skip_spaces(&file);
		if (is_valid_element(file))
		{
			exit_code = input_lexer(lexer, file, &skip);
			if (exit_code)
				printf("1\n");
		}
		else if (!only_spaces(file) && is_map_element(file))
		{
			if (map->map_element != NULL)
			{
				exit_code = pr_err(DUP_ELEMENTS);
				if (exit_code)
					printf("2.1\n");
			}
			else if (mandatory_elements(lexer))
			{
				exit_code = input_map_lexer(file, map);
				if (exit_code)
					printf("2.2\n");
			}
			else
			{
				exit_code = pr_err(FILE_ORDER);
				if (exit_code)
					printf("2.3\n");
			}
			if (exit_code)
				printf("2\n");
			skip_map_element(&file, &skip);
		}
		else if (is_valid_extra(file))
		{
			exit_code = lexer_input_extra(extras, file, &skip);
			if (exit_code)
				printf("3\n");
		}
		else if (!only_spaces(file))
		{
			exit_code = pr_err(INV_ELE);
			if (exit_code)
				printf("4\n");
		}
		else
			skip = 1;
		if (exit_code)
			return (EXIT_FAILURE);
		if (skip)
			skip_line(&file);
	}
	return (EXIT_SUCCESS);
}

// read the file into one string and lexes the elements into a linked list
int	lexer(t_meta *meta, char *map_file)
{
	char	*file = NULL;
	
	meta->scene_name = map_file;
	file = extract_file(map_file);
	if (!file)
		return(EXIT_FAILURE);
	if (lex(file, &meta->lexer, &meta->map, meta->extras))
		return (EXIT_FAILURE); //also free everything in case of error!
	return (EXIT_SUCCESS);
}
