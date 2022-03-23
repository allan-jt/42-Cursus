/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:18:15 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:18:18 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_match(char *nrml_str, char *test_str)
{
	int	match;

	if (*test_str == '\0')
		return (*nrml_str == '\0');
	if (*nrml_str == '\0')
		return (*test_str == '\0'
			|| (*test_str == '*' && *(test_str + 1) == '\0'));
	match = (*test_str == *nrml_str || *test_str == '*');
	if (*test_str == '*')
		return (is_match(nrml_str + 1, test_str)
			|| (is_match(nrml_str, test_str + 1)));
	return (match && is_match(nrml_str + 1, test_str + 1));
}

void	fill_wilcard(t_cmd *inst, char **contents)
{
	char	**new_args;
	int		i[2];
	int		match;

	i[0] = -1;
	new_args = NULL;
	while (inst->args && inst->args[++i[0]])
	{
		i[1] = -1;
		match = 0;
		while (contents[++i[1]])
		{
			match = (match || is_match(contents[i[1]], inst->args[i[0]]));
			if (is_match(contents[i[1]], inst->args[i[0]]))
				new_args = append_2d_array(new_args, contents[i[1]]);
		}
		if (!match)
			new_args = append_2d_array(new_args, inst->args[i[0]]);
	}
	free_2d(inst->args);
	inst->args = new_args;
	if (inst->next)
		fill_wilcard(inst->next, contents);
}

void	wildcard(t_cmd *inst)
{
	struct dirent	*entity;
	DIR				*dir;
	char			**contents;

	if (!inst || !inst->args[0])
		return ;
	dir = opendir(".");
	entity = readdir(dir);
	contents = NULL;
	while (entity)
	{
		if (entity->d_name[0] != '.')
			contents = append_2d_array(contents, entity->d_name);
		entity = readdir(dir);
	}
	fill_wilcard(inst, contents);
	free_2d(contents);
	closedir(dir);
}
