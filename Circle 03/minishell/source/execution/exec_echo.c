/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:16:02 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:16:03 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_nl(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str++;
	while (*(++str) != '\0')
		if (*str != 'n')
			return (0);
	return (1);
}

int	ex_echo(t_cmd *inst)
{
	char		*str;
	int			i;
	int			nl;

	if (ft_strncmp(inst->args[0], "echo", 5))
		return (0);
	nl = 0;
	while (inst->args[1 + nl] && is_nl(inst->args[1 + nl]))
		nl++;
	i = nl;
	str = NULL;
	while (inst->args[++i])
	{
		if (!str)
			str = ft_strdup(inst->args[i]);
		else
			str = ft_strjoin(str, ft_strjoin(ft_strdup(" "),
						ft_strdup(inst->args[i])));
	}
	write(STDOUT_FILENO, str, ft_strlen(str));
	if (!nl)
		write(STDOUT_FILENO, "\n", 1);
	free(str);
	return (1);
}
