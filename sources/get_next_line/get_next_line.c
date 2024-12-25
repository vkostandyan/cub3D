/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:33 by vkostand          #+#    #+#             */
/*   Updated: 2024/05/24 14:31:03 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*remove_line(char *buffer)
{
	int		i;
	int		j;
	char	*without_line;	

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	without_line = (char *)malloc(sizeof(char) * (gnl_strlen(buffer) - i + 1));
	if (!without_line)
		return (NULL);
	j = 0;
	while (buffer[i + j])
	{
		without_line[j] = buffer[i + j];
		j++;
	}
	without_line[j] = '\0';
	free(buffer);
	return (without_line);
}

static char	*get_new_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_line(int fd, char *buffer)
{
	char	*rd_line;
	int		bufsize;

	bufsize = 1;
	rd_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!rd_line)
		return (NULL);
	while (bufsize > 0 && !gnl_strchr(buffer, '\n'))
	{
		bufsize = read(fd, rd_line, BUFFER_SIZE);
		if (bufsize < 0)
		{
			free(rd_line);
			return (NULL);
		}
		rd_line[bufsize] = '\0';
		buffer = gnl_join(buffer, rd_line);
	}
	free(rd_line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_new_line(buffer);
	buffer = remove_line(buffer);
	if (*line == '\0')
	{
		free(line);
		free(buffer);
		buffer = NULL;
		line = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;

// 	fd = open("test.txt", O_RDWR | O_CREAT);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("\n%d\n", get_next_line(fd) == '\0');

// 	// system("leaks a.out");
// 	close(fd);
// 	return (0);
// }
