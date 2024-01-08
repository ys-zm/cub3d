/* ************************************************************************** */
/**/
/*::::::::*/
/*   get_next_line.c:+::+:*/
/* +:+*/
/*   By: jboeve <marvin@42.fr>+#+ */
/*   +#+  */
/*   Created: 2022/11/21 19:26:30 by joppe #+##+# */
/*   Updated: 2023/03/08 09:24:43 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*next(char **file_content)
{
	char	*end;
	char	*line;
	char	*file_content_new;
	int		line_len;

	if (!*file_content)
		return (NULL);
	end = gnl_strchr(*file_content, '\n') + 1;
	if (!end)
		end = *file_content + (gnl_strlen(*file_content) * sizeof(char));
	line_len = end - *file_content;
	line = gnl_substr(*file_content, 0, line_len);
	if (!line)
		return (NULL);
	file_content_new = gnl_substr(*file_content, line_len,
			gnl_strlen(*file_content) - line_len);
	if (!file_content_new)
		return (free(line), NULL);
	free(*file_content);
	*file_content = file_content_new;
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

static	char	*read_file(char *file_content, int fd)
{
	int		r;
	char	read_buf[BUFFER_SIZE + 1];

	r = 1;
	read_buf[BUFFER_SIZE] = 0;
	while (r)
	{
		r = read(fd, read_buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(file_content);
			return (NULL);
		}
		if (r == 0)
			return (file_content);
		if (r < BUFFER_SIZE)
			read_buf[r] = 0;
		file_content = gnl_strjoin_free(file_content, read_buf);
		if (!file_content)
			return (NULL);
		if (gnl_strchr(read_buf, '\n'))
			break ;
	}
	return (file_content);
}

char	*get_next_line(int fd)
{
	static char	*file_content[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!file_content[fd])
		file_content[fd] = gnl_strdup("");
	if (!file_content[fd])
		return (NULL);
	file_content[fd] = read_file(file_content[fd], fd);
	if (!file_content[fd])
		return (NULL);
	line = next(&file_content[fd]);
	if (!line)
	{
		free(file_content[fd]);
		file_content[fd] = NULL;
		return (NULL);
	}
	return (line);
}
