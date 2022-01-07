/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:04:04 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/17 16:24:00 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		ft_strlen(const char *str);
void	*ft_calloc(int count, int size);
int		ft_strchr(const char *s, int c);
int		check_nl(char *ln);
char	*copy_line(char *ans, char *ln);
char	*shift_ln(char *ln);

#endif
