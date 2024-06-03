/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/05/30 16:06:17 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"

static t_flag	*create_new_node(char *file)
{
	t_flag	*node;

	node = malloc(sizeof(t_flag) * 1);
	if (!node)
		return (NULL);
	node->flag = get_key(file);
	if (!node->flag)
		return (NULL);
	node->content = get_val(file);
	if (!node->content)
		return (free(node->flag), NULL);
	node->next = NULL;
	return (node);
}

static void	add_to_list(t_flag **elements, t_flag *new_node)
{
	t_flag	*list;

	list = *elements;
	if (*elements == NULL)  // If the list is empty
	{
		*elements = new_node; // Set as first node
	}
	else
	{
		while (list->next != NULL) // Skip to the last element in the list
		{
			list = list->next;
		}
		list->next = new_node; 
	}
}

static int	add_element(char *file, t_flag **elements, int *mandatory)
{
	t_flag	*new_node;

	new_node = create_new_node(file);
	if (!new_node)
		return (pr_err(MALL_ERR));
	if (!is_valid_key(*elements, new_node, mandatory))
		return (free(new_node->flag), free(new_node->content), free(new_node), pr_err(DUP_ELEMENTS));
	add_to_list(elements, new_node);
	return (EXIT_SUCCESS);
}

// checks for config file errors such as missing map or duplicate elements
static int	lex(char *file, t_map *map, t_flag **elements)
{
	int	exit_code;
	int	skip;
	int	mandatory;

	mandatory = 0;
	while (*file)
	{
		exit_code = 0;
		skip = 1;
		skip_spaces(&file);
		if (is_map_element(file) && !only_spaces(file))
			exit_code = map_lex(&file, map, &skip, mandatory);
		else if (only_spaces(file))
			skip = 1;
		else
			exit_code = add_element(file, elements, &mandatory);
		if (exit_code)
			return (EXIT_FAILURE);
		skip_line(&file, skip);
	}
	if (!map->map_element)
		return (pr_err(MISSING_MAP));
	return (EXIT_SUCCESS);
}

int	lexer(t_meta *meta, char *map_file)
{
	char	*file;

	file = NULL;
	meta->scene_name = map_file;
	file = extract_file(map_file);
	if (!file)
		return (EXIT_FAILURE);
	if (lex(file, &meta->map, &meta->elements))
		return (free(file), free_t_flag_list(&meta->elements), free(meta->map.map_element), EXIT_FAILURE);
	free(file);
	return (EXIT_SUCCESS);
}
