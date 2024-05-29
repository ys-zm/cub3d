/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                     :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/05/29 12:23:21 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"

static bool	is_duplicate_flag(t_flag *elements, char *key)
{
	while (elements != NULL)
	{
		if (!ft_strcmp_largest(elements->flag, key))
			return (true);
		elements = elements->next;
	}
	return (false);
}

// if key is not a duplicate and is mandatory
bool	is_valid_key(t_flag *elements, t_flag *new_node, int *mandatory)
{
	if (is_duplicate_flag(elements, new_node->flag) && is_valid_element(new_node->flag))
	{
		return (false);
	}
	if (!is_duplicate_flag(elements, new_node->flag) && is_valid_element(new_node->flag))
	{
		(*mandatory)++;
	}
	return (true);
}

char	*extract_file(char *map_file)
{
	int		fd;
	char	*file;

	file = NULL;
	if (map_extension(map_file))
		return (pr_err(INV_EXT), NULL);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (pr_err(INV_FILE), NULL);
	file = file_to_string(fd);
	close(fd);
	if (!file)
		return (pr_err(MALL_ERR), NULL);
	return (file);
}

char	*get_key(char *file)
{
	int		i;
	char	*key;

	i = 0;
	while (file[i] && (file[i] != ' ' && file[i] != '\t') && file[i] != '\n')
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
	while (file[j] && (file[j] != ' ' && file[j] != '\t') && file[j] != '\n')
		j++;
	while (file[j] && (file[j] == ' ' || file[j] == '\t') && file[j] != '\n')
		j++;
	i = j;
	while (file[j] && file[j] != '\n')
		j++;
	if (i < j)
	{
		val = ft_substr(file, i, j - i);
		if (!val)
			return (pr_err(MALL_ERR), NULL);
		return (val);
	}
	return (ft_strdup(""));
}
