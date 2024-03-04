/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 15:16:04 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"

uint32_t	count_doors(t_cell_type *map, uint32_t w, uint32_t h)
{
	uint32_t	doors;
	uint32_t	i;

	doors = 0;
	i = 0;
	while (i < w * h)
	{
		if (map[i] == MAP_DOOR_CLOSED)
			doors++;
		i++;
	}
	return (doors);
}

int	save_door_index(uint32_t *arr, uint32_t door_count, t_map map)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < map.width * map.height)
	{
		if (map.level[i] == MAP_DOOR_CLOSED)
		{
			arr[j] = i;
			if (j < door_count)
				j++;
			else
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	set_doors(t_door *doors, t_map map)
{
	if (!doors->door_count)
		return (EXIT_SUCCESS);
	doors->idx = malloc(sizeof(uint32_t) * doors->door_count);
	if (!doors->idx)
		return (pr_err(MALL_ERR));
	if (save_door_index(doors->idx, doors->door_count, map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	input_path(char **path, char *content)
{
	if (*path)
		return (EXIT_SUCCESS);
	*path = ft_strdup(content);
	if (!*path)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
