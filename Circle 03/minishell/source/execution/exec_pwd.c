/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:16:21 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:16:23 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_pwd(t_cmd *inst)
{
	char	path[PATH_MAX];

	if (ft_strncmp(inst->args[0], "pwd", 4))
		return (0);
	if (!getcwd(path, PATH_MAX))
	{
		put_error("pwd", inst->args[1], NULL, 1);
		return (2);
	}
	write(STDOUT_FILENO, path, ft_strlen(path));
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}
