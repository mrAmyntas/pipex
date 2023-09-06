/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/03 17:53:03 by bhoitzin      #+#    #+#                 */
/*   Updated: 2021/10/03 19:39:51 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_checkprefix(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0') && (j < ft_strlen(set)))
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				i++;
				break ;
			}
			j++;
		}
	}
	return (i);
}

static int	ft_checksuffix(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while ((s1[i] != '\0') && (j < ft_strlen(set)))
	{
		j = 0;
		while (set[j] != '\0')
		{
			if ((s1[i] == set[j]) && (i != 0))
			{
				i--;
				break ;
			}
			j++;
		}
	}
	return (i);
}

char	*ft_strtrim(char *s1, char const *set)
{
	int		i;
	int		j;
	char	*ret;

	if (s1 == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
	{
		ret = (char *)malloc(1);
		ret[0] = '\0';
		return (ret);
	}
	i = ft_checkprefix(s1, set);
	j = ft_checksuffix(s1, set);
	ret = ft_substr(s1, i, (j - i + 1), 0);
	if (ret == NULL)
		return (NULL);
	free(s1);
	return (ret);
}

void	ft_mallocfail(int x, t_data *data)
{
	int	i;

	i = 0;
	perror("Malloc Fail");
	if (x > 0)
	{
		while (data->paths[i] != NULL)
		{
			free(data->paths[i]);
			i++;
		}
		free(data->paths);
	}
	i = 0;
	if (x > 1)
	{
		while (data->splitcmd[i] != NULL)
		{
			free(data->splitcmd[i]);
			i++;
		}
		free(data->splitcmd[i]);
	}
	exit(EXIT_FAILURE);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->paths[i] != NULL)
	{
		free(data->paths[i]);
		i++;
	}
	free(data->paths);
	i = 0;
	while (data->splitcmd[i] != NULL)
	{
		free(data->splitcmd[i]);
		i++;
	}
	free(data->splitcmd);
}
