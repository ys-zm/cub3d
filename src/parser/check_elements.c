/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                  :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/02 18:57:17 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// checks if the element abbreviations are valid
bool    is_valid_element(char *file)
{
    char    *el[6] = {"NO", "SO", "WE", "EA", "F", "C"};
    size_t  i;

    i = 0;
    while (i < 6)
    {
        if (ft_strncmp(file, el[i], ft_strlen(el[i])) == 0)
            return (true);
        i++;
    }
    return (false);
}

// returns true if there are only spaces until '\0' or '\n'
bool    only_spaces(char *file)
{
    while (*file && *file == ' ')
        file++;
    if (*file == '\0' || *file == '\n')
        return (true);
    return (false);
}

// returns true if the map element is reached
bool    is_map_element(char *file)
{
    while (*file && valid_map_char(*file))
        file++;
    if (*file == '\0' || *file == '\n')
        return (true);
    return (false); 
}

// checks if there are elements after the MAP elements
// returns true if order is correct (i.e. map element at the end)
bool    elements_order(char *file)
{
    bool map = false;
    bool order = true;

    while (*file)
    {
        skip_spaces(&file);
        if (is_valid_element(file))
        {
            if (map)
                order = false;
        }
        else if (!only_spaces(file))
            map = true;
        skip_line(&file);
    }
    if (order == false)
        pr_err(FILE_ORDER);
    return (order == true);
}

bool check_missing(int *found)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (found[i] == 0)
            return (pr_err(MISSING_ELEMENTS), true);
        i++;
    }
    return (false);
}

bool is_missing(char *file)
{
    char    element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
    int     found[6] = {0, 0, 0, 0, 0, 0};
    int     i;

    while (*file)
    {
        i = 0;
        skip_spaces(&file);
        if ((is_valid_element(file) || is_colour(file)))
        {
            while (*file && *file != element[i] && i < 6)
                i++;
            found[i] = 1;
        }
        skip_line(&file);
    }
    return (check_missing(found));
}

// returns true if there are duplicate elements
bool is_duplicate(char *file)
{
    char    element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
    int     found[6] = {0, 0, 0, 0, 0, 0};
    int     i;

    while (*file)
    {
        i = 0;
        skip_spaces(&file);
        if ((is_valid_element(file) || is_colour(file)))
        {
            while (*file && *file != element[i] && i < 6)
                i++;
            if (found[i] == 0)
                found[i] = 1;
            else
                return (pr_err(DUP_ELEMENTS), true);
        }
        skip_line(&file);
    }
    return (false);
}
