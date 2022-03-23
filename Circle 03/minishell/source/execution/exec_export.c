/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:15:15 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:15:18 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_with_quote(int fd, char *str)
{
	int	i;

	i = 0;
	write(STDOUT_FILENO, "declare -x ", 11);
	while (str[i] != '=' && str[i] != '\0')
		write(fd, &(str[i++]), 1);
	if (str[i] != '=')
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	write(fd, &(str[i++]), 1);
	write(fd, "\"", 1);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '$')
			write(1, "\\", 1);
		write(fd, &(str[i++]), 1);
	}
	write(fd, "\"", 1);
	write(STDOUT_FILENO, "\n", 1);
}

int	ex_export_ch(t_cmd *inst)
{
	char	**env;
	int		i;
	char	*min;
	char	*last;

	if (ft_strncmp(inst->args[0], "export", 7) || inst->args[1])
		return (0);
	env = new_environ(NULL);
	last = NULL;
	while (1)
	{
		i = -1;
		min = NULL;
		while (env[++i])
			if ((!min || ft_strncmp(min, env[i], ft_strlen(env[i]) + 1) > 0)
				&& (!last || ft_strncmp(last, env[i],
						ft_strlen(env[i]) + 1) < 0))
				min = env[i];
		if (last && ft_strncmp(min, last, ft_strlen(min) + 1) == 0)
			break ;
		if (!(*min == '_' && min[1] == '='))
			write_with_quote(STDOUT_FILENO, min);
		last = min;
	}
	return (1);
}

int	valid_var_name(char *name)
{
	char	*var_name;
	int		status;
	int		i;

	status = 1;
	var_name = get_var_name(name);
	if (*var_name == '\0')
	{
		free (var_name);
		return (0);
	}
	if (!ft_isalpha(*var_name) && *var_name != '_')
		status = 0;
	i = -1;
	while (status == 1 && var_name[++i] != '\0')
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			status = 0;
	free(var_name);
	return (status);
}

static void	add_exiting(char **env, int stat, char *input, char *var)
{
	int		content;
	char	*str;
	int		i;

	content = 0;
	while (input[content] != '=' && input[content] != '\0')
		content++;
	i = (stat != -1 && env[stat][ft_strlen(var)] == '=');
	if (stat == -1 && input[content] == '\0')
		env = append_2d_array(env, var);
	else if (stat == -1)
	{
		str = ft_strjoin(ft_strdup(var), ft_strdup(&input[content]));
		env = append_2d_array(env, str);
		free(str);
	}
	else if (input[content] == '=' && input[ft_strlen(var)] == '+')
		env[stat] = ft_strjoin(env[stat], ft_strdup(&input[content + i]));
	else if (input[content] == '=')
	{
		free(env[stat]);
		env[stat] = ft_strdup(input);
	}
	free(var);
	new_environ(env);
}

int	ex_export_pr(t_cmd *inst)
{
	char	**env;
	int		status;
	int		i;

	if (ft_strncmp(inst->args[0], "export", 7) || !inst->args[1])
		return (0);
	i = 0;
	exit_status(0);
	while (inst->args[++i])
	{
		env = new_environ(NULL);
		status = in_2d_array(env, inst->args[i]);
		if (!valid_var_name(inst->args[i]))
			put_error(inst->args[0], inst->args[i],
				"not a valid identifier\n", 1);
		else
			add_exiting(env, status, inst->args[i],
				get_var_name(inst->args[i]));
	}
	return (1);
}
