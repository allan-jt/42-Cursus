/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:15:04 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:15:07 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_env(t_cmd *inst)
{
	char	**env;
	int		i;

	if (ft_strncmp(inst->args[0], "env", 4))
		return (0);
	i = -1;
	env = new_environ(NULL);
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (1);
}
