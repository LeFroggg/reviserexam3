/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:19:34 by abastian          #+#    #+#             */
/*   Updated: 2024/06/28 18:10:31 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*line_analyse(int fd, char *buffer, char *stash)
{
	char	*temp;
	int		read_value;

	read_value = 1;
	while (read_value > 0)
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		if (read_value < 0)
		{
			free(stash);
			return (NULL);
		}
		else if (read_value == 0)
			break ;
		if (!stash)
			stash = ft_strdup("");
		buffer[read_value] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*clean_stash_line(char *line)
{
	char	*stash;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
		return (NULL);
	stash = ft_substr(line, (i + 1), ft_strlen(line) - i + 1);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash[fd])
			free(stash[fd]);
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || read(fd, buffer, 0) < 0)
	{
		if (stash[fd])
			free(stash[fd]);
		stash[fd] = NULL;
		free(buffer);
		return (NULL);
	}
	line = line_analyse(fd, buffer, stash[fd]);
	free(buffer);
	if (!line)
		return (NULL);
	stash[fd] = clean_stash_line(line);
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int fd;

	fd = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}*/