/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pipex.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 19:30:56 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/10/06 15:10:42 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_pipex2(t_data *data)
{
	ft_free(data);
	data->ret = close(data->my_pipe[1]);
	if (data->ret == -1)
		ft_errors(4, "in: ft_pipex2\n", 0, data);
	data->ret = close(data->my_pipe[0]);
	if (data->ret == -1)
		ft_errors(4, "in: ft_pipex2\n", 0, data);
	data->ret = close(data->fd1);
	if (data->ret == -1)
		ft_errors(4, "in: ft_pipex2\n", 0, data);
	data->ret = close(data->fd2);
	if (data->ret == -1)
		ft_errors(4, "in: ft_pipex2\n", 0, data);
	data->pidret = waitpid(data->child1, &data->status, 0);
	if (data->pidret == -1)
		ft_errors(3, "in: ft_pipex\n", 0, data);
	data->pidret = waitpid(data->child2, &data->status, 0);
	if (data->pidret == -1)
		ft_errors(3, "in: ft_pipex2\n", 0, data);
}

void	ft_pipex(t_data *data, char *cmd1, char *cmd2)
{
	ft_findpaths(data, cmd1);
	data->child1 = fork();
	if (data->child1 < 0)
		ft_errors(2, "in: ft_pipex\n", 1, data);
	if (data->child1 == 0)
		ft_child1process(data);
	else
	{
		ft_free(data);
		ft_findpaths(data, cmd2);
		data->child2 = fork();
		if (data->child2 < 0)
			ft_errors(2, "in: ft_pipex\n", 1, data);
		if (data->child2 == 0)
			ft_child2process(data);
		else
			ft_pipex2(data);
	}
}

static void	open_fds(t_data *data, char **av)
{
	data->ret = access(av[1], F_OK);
	if (data->ret == -1)
	{
		data->fd1 = open(av[1], O_RDONLY | O_CREAT, 0444);
		data->noinfile = 1;
	}
	data->fd1 = open(av[1], O_RDONLY);
	if (data->fd1 < 0)
		ft_errors(0, "in: main\n", 0, data);
	data->fd2 = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd2 < 0)
		ft_errors(0, "in: main\n", 0, data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 5)
	{
		data.envp = envp;
		if (data.envp == NULL)
			ft_errors(5, "in: main\n", 0, &data);
		open_fds(&data, av);
		data.ret = pipe(data.my_pipe);
		if (data.ret == -1)
			ft_errors(1, "in: main\n", 0, &data);
		ft_pipex(&data, av[2], av[3]);
	}
	else
		write(1, "Error:\nInput should be: inputfile cmd1 cmd2 outputfile\n", 55);
	if (data.noinfile == 1)
	{
		unlink(av[1]);
		ft_errors(0, "in: main\n", 0, &data);
	}
}
