/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/02 19:06:47 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"


static void free_t_tex(t_tex *tex)
{
    free(tex->no);
    free(tex->so);
    free(tex->ea);
    free(tex->we);
}

void meta_free(t_meta *meta)
{
    free_t_tex(&(meta->tex));
    free(meta->map.level);
}
