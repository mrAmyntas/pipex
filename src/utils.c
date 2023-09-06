/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 14:36:58 by bhoitzin      #+#    #+#                 */
/*   Updated: 2021/10/03 19:34:47 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_findpaths(t_data *data, char *cmd)
{
	int	i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		data->ret = ft_strpath(data->envp[i]);
		if (data->ret == 1)
		{
			data->paths = ft_split(data->envp[i], ':');
			if (data->paths == NULL)
				ft_mallocfail(0, data);
			break ;
		}
		i++;
	}
	data->splitcmd = ft_split(cmd, ' ');
	if (data->splitcmd == NULL)
		ft_mallocfail(1, data);
	ft_findpaths2(data);
	data->paths[0] = ft_strtrim(data->paths[0], "PATH=");
	if (data->paths[0] == NULL)
		ft_mallocfail(2, data);
}

void	ft_findpaths2(t_data *data)
{
	int	i;

	i = 0;
	while (data->paths[i] != NULL)
	{
		data->paths[i] = ft_strjoin(data->paths[i], "/");
		if (data->paths[i] == NULL)
			ft_mallocfail(2, data);
		data->paths[i] = ft_strjoin(data->paths[i], data->splitcmd[0]);
		if (data->paths[i] == NULL)
			ft_mallocfail(2, data);
		i++;
	}
}

int	ft_strpath(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'P' && str[i + 1] != '\0')
		{
			if (str[i + 1] == 'A' && str[i + 2] != '\0')
			{
				if (str[i + 2] == 'T' && str[i + 3] != '\0')
				{
					if (str[i + 3] == 'H')
						return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

static char	*ft_join2(char *buff, char *s1, char const *s2)
{
	int	x;
	int	i;

	x = 0;
	while (s1[x] != '\0')
	{
		buff[x] = s1[x];
		x++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		buff[x] = s2[i];
		i++;
		x++;
	}
	buff[x] = '\0';
	return (buff);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*buff;
	int		x;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	x = ft_strlen(s1) + ft_strlen(s2) + 1;
	buff = (char *)malloc(sizeof(char) * x);
	if (buff == NULL)
		return (NULL);
	x = 0;
	buff = ft_join2(buff, s1, s2);
	free(s1);
	return (buff);
}
