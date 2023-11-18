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

// why are my skip functions not working >_<
void skip_line(char **file)
{
    while (file && *file && **file && **file != '\n')
        (*file)++;
    if (**file == '\n')
        (*file)++;
}

void skip_spaces(char **file)
{
    while (file && *file && **file && **file == ' ')
        (*file)++;
}

int is_valid_element(char *file)
{
    char    *el[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
    size_t  i;

    i = 0;
    while (i < 6)
    {
        if (ft_strncmp(file, el[i], ft_strlen(el[i])) == 0)
            return (1);
        i++;
    }
    return (0);
}

int only_spaces(char *file)
{
    while (*file && *file == ' ')
        file++;
    if (*file == '\0' || *file == '\n')
        return (1);
    return (0);
}

int count_elements(char *file)
{
    int elements = 0;
    bool map = false;
    bool order = true;

    while (*file)
    {
        skip_spaces(&file);
        if (is_valid_element(file))
        {
            if (map)
                order = false;
            elements++;
        }
        else if (!only_spaces(file))
            map = true;
        skip_line(&file);
    }
    if (order == false)
        pr_err(FILE_ORDER);
    if (elements < 6)
        return (pr_err(M_ELEMENTS), 0);
    if (elements > 6)
        return (pr_err(T_ELEMENTS), 0);
    return (order == true);
}


int get_col_val(char *file, t_rgba *col)
{
    skip_spaces(&file);
    col->r = (uint8_t)ft_atoi(file);
    while (*file && *file != ',')
        file++;
    col->g = ft_atoi(file + 1);
    while (*file && *file != ',')
        file++;
    col->b = ft_atoi(file + 1);
    return (0);
}

char *get_tex_val(char *file)
{
    int     i;
    char    *val;

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

int inp_tex(t_tex *tex, char *file)
{
    char    tx[4] = {'N', 'S', 'W', 'E'};
    char    **st[4] = {&tex->no, &tex->so, &tex->we, &tex->ea};
    int     i;

    i = 0;
   skip_spaces(&file);
    while (i < 4 && *file && *file != tx[i])
        i++;
    *st[i] = get_tex_val(file + 2);
    if (!st[i])
    if (!(st[i]))
        return (pr_err(MALL_ERR));
    if (!ft_strncmp(*st[i], "", 1))
        return (pr_err(M_PATH));
    return (0); 
}

int inp_col(t_tex *tex, char *file)
{
    char    tx[2] = {'F', 'C'};
    t_rgba  *st[2] = {&tex->floor_c, &tex->ceiling_c};
    int     i;

    i = 0;
   skip_spaces(&file);
    while (i < 2 && *file && *file != tx[i])
        i++;
    if (get_col_val(file + 1, st[i]))
        return (pr_err(MALL_ERR));
    return (0); 
}

int is_tex(char *file)
{
    char    *tx[4] = {"NO ", "SO ", "WE ", "EA "}; // leak bait
    int     i;

    i = 0;
    while (i < 4)
    {
        if (!ft_strncmp(file, tx[i], 3))
            return (1);
        i++;
    }
    return (0);
}

int is_col(char *file)
{
    if (*file == 'F')
        return (1);
    if (*file == 'C')
        return (1);
    return (0);
}

int save_elements(t_tex *tex, char *file)
{
    while (*file)
    {
        skip_spaces(&file);
        if (is_tex(file))
        {
            if (inp_tex(tex, file))
            {
                return (1);
            }
        }
        else if (is_col(file))
        {
            if (inp_col(tex, file))
                return (1);
        }
        skip_line(&file);
    }
    return (0);
}

int check_if_map_line(char *file)
{
	while (*file && *file != '\n')
	{
		if (*file != ' ')
			break ;
		file++;
	}
	if (*file == '\n')
		return (0);
	return (1);
}

int save_map(t_meta *meta, char *file)
{
    int	i;

    while (*file)
    {
        if (check_if_map_line(file))
            break ;
        skip_line(&file);
    }
    if (*file)
	{
		i = ft_strlen(file);
		meta->map_file = ft_substr(file, 0, i);
        if (!meta->map_file)
            return (pr_err(MALL_ERR));
		return (0);
	}
	else
		return (1);
}

int parse_textures(t_meta *meta, char *file)
{

    if (count_elements(file) == 0)
        return (1);
    if (save_elements(&(meta->tex), file))
        return (1);
    if (save_map(meta, file))
        return (1);
    return (0);
}