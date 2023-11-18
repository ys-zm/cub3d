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


void free_t_tex(t_tex *tex)
{
    printf("free function called\n");
    printf("N: %s\n", tex->no);
     printf("S: %s\n", tex->so);
      printf("E: %s\n", tex->ea);
       printf("W: %s\n", tex->we);
    free(tex->no);
    free(tex->so);
    free(tex->ea);
    free(tex->we);
}

void meta_free(t_meta *meta)
{
    free_t_tex(&(meta->tex));
}