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

// saves the RGB values of the F and C elements
// check if RGB is correct?
void get_colour_value(char *file, t_rgba *col)
{
    skip_spaces(&file);
    col->r = (uint8_t)ft_atoi(file);
    while (*file && *file != ',')
        file++;
    col->g = ft_atoi(file + 1);
    while (*file && *file != ',')
        file++;
    col->b = ft_atoi(file + 1);
}

// mallocs the paths to NO, SO, WE, EA elements
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

// returns true of the characters match those of a valid texture element
bool is_texture(char *file)
{
    char    *tx[4] = {"NO", "SO", "WE", "EA"};
    int     i;

    i = 0;
    while (i < 4)
    {
        if (!ft_strncmp(file, tx[i], 2))
            return (true);
        i++;
    }
    return (false);
}

// returns true of the characters match those of a valid colour element
bool is_colour(char *file)
{
    if (*file == 'F')
        return (true);
    if (*file == 'C')
        return (true);
    return (false);
}