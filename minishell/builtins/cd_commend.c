/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_commend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 01:27:53 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/05 02:28:54 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_target_directory(char **name_dir, t_env *env)
{
	char	*target_dir;

	target_dir = NULL;
	if (name_dir[1] == NULL)
		target_dir = error_check("HOME", env, "bash: cd: HOME not set\n");
	else if (ft_strncmp(name_dir[1], "-", 2) == 0)
		target_dir = error_check("OLDPWD", env, "bash: cd: OLDPWD not set\n");
	else if (ft_strncmp(name_dir[1], "$PWD", 4) == 0)
		target_dir = error_check("PWD", env, "bash: cd: PWD not set\n");
	else
		target_dir = ft_strdup(name_dir[1]);
	return (target_dir);
}

void	update_environment_variables(char *old_path, t_env *env)
{
	char	new_path[BUFFER_SIZE];
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	oldpwd = NULL;
	oldpwd = ft_strjoin("OLDPWD=", old_path);
	update_env(env, oldpwd, "OLDPWD");
	free(oldpwd);
	if (getcwd(new_path, sizeof(new_path)) != NULL)
	{
		pwd = ft_strjoin("PWD=", new_path);
		update_env(env, pwd, "PWD");
		free(pwd);
	}
	else
	{
		perror("getcwd error");
	}
	g_exit_status = 0;
}

int	change_directory_and_update_paths(char *target_dir, t_env *env)
{
	char	old_path[BUFFER_SIZE];

	if (getcwd(old_path, sizeof(old_path)) == NULL)
	{
		perror("getcwd error");
		g_exit_status = 1;
		return (1);
	}
	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
		return (1);
	}
	update_environment_variables(old_path, env);
	return (0);
}

void	my_cd(char **name_dir, t_env *env)
{
	char	*target_dir;

	target_dir = NULL;
	target_dir = get_target_directory(name_dir, env);
	if (target_dir == NULL)
		return ;
	if (change_directory_and_update_paths(target_dir, env) == 0)
		g_exit_status = 0;
	free(target_dir);
}
