/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_lexer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:18:50 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "parser.h"

char	*get_title_val(char *file)
{
	int		i;
	char	*val;

	i = 0;
	skip_spaces(&file);
	while (file[i] && file[i] != ' ')
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

// saves the flag of the extra (for now only sprites called "OBJ")
int	save_extra_title(t_flag **extras, char **file)
{
	t_flag *new_node;
	int	i;

	i = 0;
	new_node = malloc(sizeof(t_flag) * 1);
	if (!new_node)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	new_node->next = NULL;
	new_node->flag = get_title_val(*file);
	if (*extras == NULL)
		*extras = new_node;
	else
	{
		while ((*extras)->next == NULL)
			*extras = (*extras)->next;
		*extras = new_node;
	}
	while (new_node->flag[i])
	{
		i++;
		(*file)++;
	}
	return (EXIT_SUCCESS);
}

bool	is_valid_extra(char *file)
{
	if (*file && !ft_strncmp(file, "OBJ", 3))
		return (true);
	return (false);
}

// inputs extras into the extras linked list (for now only sprites)
int	lexer_input_extra(t_flag **extras, char *file, int *skip)
{
	while (*extras && (*extras)->next != NULL)
		*extras = (*extras)->next;
	(*extras)->content = get_val(file);
	(*extras)->next = NULL;
	*skip = 1;
	return (EXIT_SUCCESS);
}