/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:14:51 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:14:54 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_environ_pwd(char *old_path, char *new_path, char ***env)
{
	int			old_idx;
	int			new_idx;
	char		*o_path;
	char		*n_path;

	old_idx = in_2d_array(*env, "OLDPWD");
	new_idx = in_2d_array(*env, "PWD");
	o_path = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(old_path));
	n_path = ft_strjoin(ft_strdup("PWD="), ft_strdup(new_path));
	if (old_idx == -1)
		*env = append_2d_array(*env, o_path);
	else
	{
		free((*env)[old_idx]);
		(*env)[old_idx] = ft_strdup(o_path);
	}
	if (new_idx == -1)
		*env = append_2d_array(*env, n_path);
	else
	{
		free((*env)[new_idx]);
		(*env)[new_idx] = ft_strdup(n_path);
	}
	free(o_path);
	free(n_path);
}

int	ex_cd(t_cmd *inst)
{
	char	old_path[PATH_MAX];
	char	new_path[PATH_MAX];
	char	**tmp_env;

	if (ft_strncmp(inst->args[0], "cd", 3))
		return (0);
	exit_status(0);
	getcwd(old_path, PATH_MAX);
	if (d2_len(inst->args) > 2)
		return (put_error(inst->args[0], NULL, "too many arguments\n", 1));
	if (inst->args[1] && chdir(inst->args[1]) == -1)
		return (put_error("cd", inst->args[1], NULL, 1));
	if (!inst->args[1] && (in_2d_array(new_environ(NULL), "HOME") == -1
			|| chdir(getenv("HOME")) == -1))
		return (put_error("cd", NULL, "HOME not set\n", 1));
	getcwd(new_path, PATH_MAX);
	tmp_env = new_environ(NULL);
	change_environ_pwd(old_path, new_path, &tmp_env);
	new_environ(tmp_env);
	return (1);
}
