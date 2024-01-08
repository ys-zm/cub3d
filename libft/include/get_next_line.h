/* ************************************************************************** */
/**/
/*::::::::*/
/*   get_next_line.h:+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/11/13 16:57:23 by joppe #+##+# */
/*   Updated: 2023/03/08 09:24:24 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

char	*get_next_line(int fd);

char	*gnl_substr(char const *s, unsigned int start, size_t len);
int		gnl_strlen(char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin_free(char *s_base, char *s_append);

#endif
