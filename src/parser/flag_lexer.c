/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:18:50 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "parser.h"

char	*get_val(char *file)
{
	int		i;
	char	*val;

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

int	input_lexer(t_lex *lex, char *file, int *skip)
{
	char	element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
	char**	content[6] = {&lex->n.content, &lex->s.content, &lex->w.content, &lex->e.content, &lex->c.content, &lex->f.content};
	int i;

	i = 0;
	*skip = 1;
	skip_spaces(&file);
	while (i < 6)
	{
		if (*file && *file == element[i])
		{
			if (*content[i])
				return (pr_err(DUP_ELEMENTS));
			*content[i] = get_val(file + 2);
			if (!(content[i]))
				return (pr_err(MALL_ERR), EXIT_FAILURE);
			if (!ft_strncmp(*content[i], "", 1))
				return (pr_err(M_PATH), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}