/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2023/11/09 18:52:24 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

int	print_err(char *err, int exit_code)
{
	write(2, err, ft_strlen(err));
	return (exit_code);
}

int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *line;
	char *full_map;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_err("map file failed to open\n", 1));
	line = get_next_line(fd);
	full_map = NULL;
	while (line)
	{
		full_map = ft_strjoin(full_map, line);
		free(line);
		line = get_next_line(fd);
	}
	printf("fullmap: %s\n", full_map);
	(void)meta->map;
	return (0);
}
