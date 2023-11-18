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
    char *f;

    f = *file;
    while (*f && *f != '\n')
        f++;
    // if (*f == '\n')
    //     f++;
}

void skip_spaces(char **file)
{
    char *f;

    f = *file;
    while (*f == ' ')
        f++;
}

int is_valid_element(char *file)
{
    char *el[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
    int i;

    i = -1;
    while (++i < 6)
    {
        if (ft_strncmp(file, el[i], ft_strlen(el[i])) == 0)
            return (1);
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
    int map = 0;
    int order = 1;

    while (*file)
    {
        while (*file == ' ')
            file++;
        if (is_valid_element(file))
        {
            if (map)
                order = 0;
            elements++;
        }
        else if (!only_spaces(file))
            map = 1;
        while (*file && *file != '\n')
            file++;
        if (*file == '\n')
            file++;
    }
    if (order == 0)
        pr_err(FILE_ORDER);
    if (elements < 6)
        return (pr_err(M_ELEMENTS));
    if (elements > 6)
        return (pr_err(T_ELEMENTS));
    return (order == 1);
}