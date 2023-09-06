/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_childprocess.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 12:16:22 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/10/06 15:11:23 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_child1process(t_data *data)
{
	int	i;

	dup2(data->fd1, STDIN_FILENO);
	dup2(data->my_pipe[1], STDOUT_FILENO);
	data->ret = close(data->my_pipe[0]);
	if (data->ret == -1)
		ft_errors(4, "in: ft_child1process\n", 1, data);
	data->ret = close(data->fd2);
	if (data->ret == -1)
		ft_errors(4, "in: ft_child1process\n", 1, data);
	i = 0;
	while (data->paths[i] != NULL)
	{
		dprintf(2, "1:%s\n2:%s\n", data->paths[i], data->splitcmd[0]);
		execve(data->paths[i], data->splitcmd, data->envp);
		i++;
	}
	perror("child1process execve didn't work\n");
	exit(EXIT_FAILURE);
}

void	ft_child2process(t_data *data)
{
	int	i;

	dup2(data->fd2, STDOUT_FILENO);
	dup2(data->my_pipe[0], STDIN_FILENO);
	data->ret = close(data->my_pipe[1]);
	if (data->ret == -1)
		ft_errors(4, "in: ft_child2process\n", 1, data);
	data->ret = close(data->fd1);
	if (data->ret == -1)
		ft_errors(4, "in: ft_child2process\n", 1, data);
	i = 0;
	while (data->paths[i] != NULL)
	{
		execve(data->paths[i], data->splitcmd, data->envp);
		i++;
	}
	perror("child2process execve didn't work\n");
	exit(EXIT_FAILURE);
}

void	ft_errors(int x, char *str, int y, t_data *data)
{
	if (x == 0)
	{
		perror("Open Failed");
		write(2, str, ft_strlen(str));
	}
	if (x == 1)
	{
		perror("Pipe creation Failed");
		write(2, str, ft_strlen(str));
	}
	if (x == 2)
	{
		perror("Fork creation Failed");
		write(2, str, ft_strlen(str));
	}
	if (x == 3)
	{
		perror("Waitpid error");
		write(2, str, ft_strlen(str));
	}
	ft_errors2(x, str, y, data);
}

void	ft_errors2(int x, char *str, int y, t_data *data)
{
	if (x == 4)
	{
		perror("Close Failed");
		write(2, str, ft_strlen(str));
	}
	if (y == 1)
		ft_free(data);
	if (x == 5)
	{
		perror("Environment not found");
		write(2, str, ft_strlen(str));
	}
	exit(EXIT_FAILURE);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
