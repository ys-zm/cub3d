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

char	*get_key(char *file)
{
	int		i;
	char	*key;

	i = 0;
	while (file[i] != ' ')
		i++;
	if (i)
	{
		key = ft_substr(file, 0, i);
		if (!key)
			return (pr_err(MALL_ERR), NULL);
		return (key);
	}
	return (ft_strdup(""));
}

char	*get_val(char *file)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	j = 0;
	while (file[j] != ' ')
		j++;
	while (file[j] == ' ')
		j++;
	i = j;
	while (file[j] != '\n' && file[j])
		j++;
	if (i < j)
	{	val = ft_substr(file, i, j);
		if (!val)
			return (pr_err(MALL_ERR), NULL);
		return (val);
	}
	return (ft_strdup(""));
}

t_flag	*create_new_node(char *file)
{
	t_flag	*node;

	node = malloc(sizeof(t_flag) * 1);
	node->flag = get_key(file);
	if (!node->flag)
		return (NULL);
	node->content = get_val(file);
	if (!node->content)
		return (free(node->flag), NULL);
	node->next = NULL;
	return (node);
}

void	add_to_list (t_flag **elements, t_flag *new_node)
{
	t_flag **list;

	list = elements;
	if (!*list)
	{	
		*list = new_node;
	}
	else
	{
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = new_node;
	}
}

bool	is_duplicate_flag(t_flag *elements, char *key)
{
	while (elements != NULL)
	{
		if (!ft_strncmp(elements->flag, key, ft_strlen(key)))
			return (true);
		elements = elements->next;
	}
	return (false);
}

// if key is not a duplicate and is mandatory
bool	is_valid_key(t_flag **elements, t_flag *new_node)
{
	if (is_duplicate_flag(*elements, new_node->flag) && is_valid_element(new_node->flag))
		return (false);
	return (true);
}

int	lex(char *file, t_map *map, t_flag **elements)
{
	t_flag	*new_node;
	int	exit_code;
	int	skip;
	int	mandatory = 0;

	while (*file)
	{
		exit_code = 0;
		skip = 1;
		skip_spaces(&file);
		if (is_map_element(file) && !only_spaces(file))
		{
			exit_code = map_lex(&file, map, &skip, mandatory);
		}
		else if (only_spaces(file))
			skip = 1;
		else
		{	
			new_node = create_new_node(file);
			if (!new_node)
				return (pr_err(MALL_ERR));
			if (is_valid_key(elements, new_node))
				mandatory++;
			else
				return (free(new_node->flag), free(new_node->content), \
						free(new_node), pr_err(DUP_ELEMENTS));
			add_to_list(elements, new_node);
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
	if (lex(file, &meta->map, &meta->elements))
		return (EXIT_FAILURE); //also free everything in case of error!
	return (EXIT_SUCCESS);
}
