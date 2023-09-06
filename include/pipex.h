/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 12:17:59 by bhoitzin      #+#    #+#                 */
/*   Updated: 2021/10/08 15:39:37 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <strings.h>

typedef struct s_data {
	int		fd1;
	int		fd2;
	int		my_pipe[2];
	int		ret;
	pid_t	child1;
	pid_t	child2;
	pid_t	pidret;
	int		status;
	char	**envp;
	char	**paths;
	char	**splitcmd;
	int		noinfile;
}				t_data;

void	ft_child1process(t_data *data);
void	ft_child2process(t_data *data);
void	ft_checkstatus(int status);
void	ft_pipex(t_data *data, char *cmd1, char *cmd2);
void	ft_findpaths(t_data *data, char *cmd);
int		ft_strpath(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len, size_t i);
char	*ft_strtrim(char *s1, char const *set);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char const *s2);
void	ft_free(t_data *data);
void	ft_mallocfail(int x, t_data *data);
void	ft_errors(int x, char *str, int y, t_data *data);
void	ft_errors2(int x, char *str, int y, t_data *data);
void	ft_findpaths2(t_data *data);

#endif
