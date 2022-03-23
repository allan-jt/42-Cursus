/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:15:33 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:15:35 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

int	in_2d_array(char **ary, char *str)
{
	char	*ary_name;
	char	*str_name;
	int		i;

	i = -1;
	str_name = get_var_name(str);
	while (ary[++i])
	{
		ary_name = get_var_name(ary[i]);
		if (!ft_strncmp(ary_name, str_name, ft_strlen(ary_name) + 1))
		{
			free(ary_name);
			free(str_name);
			return (i);
		}
		free(ary_name);
	}
	free(str_name);
	return (-1);
}

char	**append_2d_array(char **ary, char *str)
{
	char	**new_ary;
	int		length;
	int		i;

	length = d2_len(ary) + (str != NULL);
	new_ary = ft_calloc(length + 1, sizeof(char *));
	i = -1;
	while (ary && ary[++i])
		new_ary[i] = ft_strdup(ary[i]);
	if (i == -1)
		i = 0;
	if (str)
		new_ary[i] = ft_strdup(str);
	free_2d(ary);
	return (new_ary);
}

int	ex_unset(t_cmd *inst)
{
	char	**env;
	char	**new_env;
	int		i;

	if (ft_strncmp(inst->args[0], "unset", 6))
		return (0);
	i = -1;
	exit_status(0);
	env = new_environ(NULL);
	new_env = NULL;
	while (inst->args[++i + 1])
		if (!valid_var_name(inst->args[i + 1]))
			put_error(inst->args[0], inst->args[i + 1],
				"not a valid identifier\n", 1);
	i = -1;
	while (env[++i])
		if (in_2d_array(&(inst->args[1]), env[i]) == -1)
			new_env = append_2d_array(new_env, env[i]);
	new_environ(new_env);
	free_2d(env);
	return (1);
}
