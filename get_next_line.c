/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdelmo <aabdelmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:53:29 by aabdelmo          #+#    #+#             */
/*   Updated: 2022/03/22 09:26:43 by aabdelmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_text(char *r, int fd)
{
	char	*buffer;
	int		a;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	a = 1;
	while (a > 0 && ft_strchr(r, '\n') == NULL)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a == 0)
			break ;
		if (a == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[a] = '\0';
		r = ft_strjoin(r, buffer);
	}
	free(buffer);
	return (r);
}

char	*get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	line[i--] = 0;
	while (i >= 0)
	{
		line[i] = str[i];
		i--;
	}
	return (line);
}

char	*ft_save(char *r)
{
	char	*p;
	int		start;
	int		j;

	start = 0;
	while (r[start] != '\0' && r[start] != '\n')
		start++;
	if (r[start] == '\n')
		start++;
	if (r[start] == '\0')
	{
		free(r);
		return (NULL);
	}
	p = (char *)malloc(sizeof(char) * (ft_strlen(r) - start + 1));
	if (!p)
		return (NULL);
	j = 0;
	while (r[start])
		p[j++] = r[start++];
	p[j] = '\0';
	free(r);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*r;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	r = get_text(r, fd);
	if (!r)
		return (NULL);
	line = get_line(r);
	r = ft_save(r);
	return (line);
}

//int main(void)
//{
	//int fd = open("text.txt", O_RDONLY);
	//get_next_line(fd);
	// printf("--%s", get_next_line(fd));
	// printf("--%s", get_next_line(fd));
	// printf("--%s", get_next_line(fd));
	// printf("--%s", get_next_line(fd));
	// printf("--%s", get_next_line(fd));

//	return (0);
//}
