/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:12:48 by jboeve            #+#    #+#             */
/*   Updated: 2023/10/04 17:47:39 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strisempty(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
