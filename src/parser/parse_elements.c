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

// skips a line on the file until '\n' char
void skip_line(char **file)
{
    while (file && *file && **file && **file != '\n')
        (*file)++;
    if (**file == '\n')
        (*file)++;
}

// skips all spaces in a line
void skip_spaces(char **file)
{
    while (file && *file && **file && (**file == ' ' || **file == 9))
        (*file)++;
}

// saves path value and checks of value us empty
int input_texture(t_tex *tex, char *file)
{
    char    element[4] = {'N', 'S', 'W', 'E'};
    char    **path[4] = {&tex->no, &tex->so, &tex->we, &tex->ea};
    int     i;

    i = 0;
    skip_spaces(&file);
    while (i < 4)
    {
        if (*file && *file == element[i])
        {
            *path[i] = get_tex_val(file + 2);
            if (!(path[i]))
                return (pr_err(MALL_ERR), EXIT_FAILURE);
            if (!ft_strncmp(*path[i], "", 1))
                return (pr_err(M_PATH), EXIT_FAILURE);
            break ;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

// add check for RBG code correctness?
int input_colour(t_tex *tex, char *file)
{
    char    tx[2] = {'F', 'C'};
    t_rgba  *st[2] = {&tex->floor_c, &tex->ceiling_c};
    int     i;

    i = 0;
   skip_spaces(&file);
    while (i < 2 && *file && *file != tx[i])
        i++;
    get_colour_value(file + 1, st[i]);
    return (EXIT_SUCCESS); 
}

int save_elements(t_tex *tex, char *file)
{
    while (*file)
    {
        skip_spaces(&file);
        if (is_texture(file))
        {
            if (input_texture(tex, file))
                return (EXIT_FAILURE);
        }
        else if (is_colour(file))
        {
            if (input_colour(tex, file))
                return (EXIT_FAILURE);
        }
        skip_line(&file);
    }
    return (EXIT_SUCCESS);
}

// check if color code values are between 0-255
bool valid_value(char *file)
{
    int i;

    i = 0;
    skip_spaces(&file);
    while (file[i] && ft_isdigit(file[i]))
        i++;
    if (!i)
        return (false);
    if (i > 3)
        return (false);
    if (i == 3)
    {
        if (file[0] > '2')
            return (false);
        if (file[0] == '2' && file[1] > '5')
            return (false);
        if (file[0] == '2' && file[1] == '5' && file[2] > '5')
            return (false);
    }
    return (true);

}

void skip_digits(char **file)
{
    while (file && *file && **file && ft_isdigit(**file))
        (*file)++;
    skip_spaces(file);
    if (**file == ',')
        (*file)++;
}

bool is_valid_color(char *file)
{
    int i;

    i = 0;
    if (*file && (*file == 'F' || *file == 'C'))
    {
        file++;
        while (i < 3)
        {
            skip_spaces(&file);
            if (!valid_value(file))
                return (pr_err(COLOR_CODE_WRONG), false);
            skip_digits(&file);
            i++;
        }
    }
    return (true);
}

bool colors_valid(char *file)
{
    while (*file)
    {
        skip_spaces(&file);
        if (is_valid_element(file))
        {
            if (is_colour(file) && !is_valid_color(file))
                return (false);
        }
        skip_line(&file);
    }
    return (true);
}

int parse_elements(t_meta *meta, char *file)
{

    if (!elements_order(file) || is_duplicate(file) || is_missing(file) || !colors_valid(file))
        return (EXIT_FAILURE);
    if (save_elements(&(meta->tex), file))
        return (EXIT_FAILURE);
    if (input_map(meta, file))
        return (EXIT_FAILURE);
    free(file);
    return (EXIT_SUCCESS);
}