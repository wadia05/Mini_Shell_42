/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:46:51 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/04 20:46:52 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_dollar(char *line, int *i, t_env *env, char *processed_line)
{
	char	*temp;

	temp = NULL;
	processed_line = malloc(1);
	processed_line[0] = '\0';
	if (line[*i + 1] == '?')
	{
		temp = ft_strjoin(processed_line, ft_itoa(g_exit_status));
		free(processed_line);
		processed_line = temp;
		(*i)++;
	}
	else if (line[*i + 1] == '@')
	{
		temp = ft_strjoin(processed_line, "$@");
		free(processed_line);
		processed_line = temp;
		(*i)++;
	}
	else
	{
		processed_line = handle_dollar_sign(line, i, env, processed_line);
	}
	return (processed_line);
}

static char	*process_heredoc_line(char *line, t_env *env)
{
	char	current[2];
	char	*processed_line;
	char	*temp;
	int		i;

	processed_line = malloc(1);
	processed_line[0] = '\0';
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
		{
			processed_line = handle_dollar(line, &i, env, processed_line);
		}
		else
		{
			current[0] = line[i];
			current[1] = '\0';
			temp = ft_strjoin(processed_line, current);
			free(processed_line);
			processed_line = temp;
		}
	}
	return (processed_line);
}

static char	*read_heredoc_line(char *end_str)
{
	char	*line;

	line = readline(YAW"heredoc> "RS);
	if (!line)
		return (NULL);
	if (ft_strncmp(line, end_str, ft_strlen(end_str) + 1) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	process_heredoc(char *end_str, t_env *env, char *name_file)
{
	int		fd;
	char	*line;
	char	*processed_line;

	fd = open(name_file, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	while (1)
	{
		line = read_heredoc_line(end_str);
		if (line == NULL)
			break ;
		processed_line = process_heredoc_line(line, env);
		write(fd, processed_line, ft_strlen(processed_line));
		write(fd, "\n", 1);
		free(processed_line);
		free(line);
	}
	close(fd);
}
