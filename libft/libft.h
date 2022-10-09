/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:31:03 by tblink            #+#    #+#             */
/*   Updated: 2022/02/11 18:32:34 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*ft_strnstr(const char *str1, const char *str2, int len);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
char				*ft_itoa(int n);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(char *s1);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strlen(const char *str);
int					ft_strncmp(const char *str1, const char *str2, int n);
char				*ft_substr(char const *s, unsigned int start, size_t len);

#endif
