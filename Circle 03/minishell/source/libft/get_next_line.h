/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:52:11 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/17 15:53:40 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
int		alt_strchr(const char *s, int c);
int		check_nl(char *ln);
char	*copy_line(char *ans, char *ln);
char	*shift_ln(char *ln);

#endif
