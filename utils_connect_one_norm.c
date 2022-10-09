/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_connect_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:31:19 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 15:58:55 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	fd_coonect_one(int	*prev, int *next,
	t_tokens *tkns, t_parser t_sct)
{
	if (prev[0] != -1 && t_sct.c_r_red == 0)
	{
		dup2(prev[0], 0);
		close(prev[0]);
		close(prev[1]);
	}
	if (next[1] != -1 && t_sct.c_r_red == 0)
	{
		dup2(next[1], 1);
		close(next[1]);
		close(next[0]);
	}
	if (next[1] == -1 && prev[0] == -1 && t_sct.c_r_red != 0)
	{
		tkns->r_r_f = open(t_sct.r_red[0],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(tkns->r_r_f, 1);
		close(tkns->r_r_f);
		close(next[1]);
		close(next[0]);
	}
}

void	fd_coonect_two(int	*prev, int *next,
	t_tokens *tkns, t_parser t_sct)
{
	if (prev[0] != -1 && t_sct.c_r_red != 0)
	{
		tkns->r_r_f = open(t_sct.r_red[0],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(prev[0], 0);
		dup2(tkns->r_r_f, 1);
		close(tkns->r_r_f);
		close(prev[0]);
		close(prev[1]);
	}
	if (next[1] != -1 && t_sct.c_r_red != 0)
	{
		tkns->r_r_f = open(t_sct.r_red[0],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(next[1], 1);
		dup2(tkns->r_r_f, 1);
		close(next[1]);
		close(tkns->r_r_f);
		close(next[0]);
	}
}

void	fd_coonect_three(int *prev, int *next,
	t_tokens *tkns, t_parser t_sct)
{
	if (next[1] == -1 && prev[0] == -1 && t_sct.c_d_r_red != 0)
	{
		tkns->d_r_r_f = open(t_sct.d_r_red[0],
				O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(tkns->d_r_r_f, 1);
		close(tkns->d_r_r_f);
	}
	if (prev[0] != -1 && t_sct.c_d_r_red != 0)
	{
		tkns->d_r_r_f = open(t_sct.d_r_red[0],
				O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(prev[0], 0);
		dup2(tkns->d_r_r_f, 1);
		close(tkns->d_r_r_f);
		close(prev[0]);
		close(prev[1]);
	}
}

void	fd_coonect_four(int *next,
	t_tokens *tkns, t_parser t_sct)
{
	if (next[1] != -1 && t_sct.c_d_r_red != 0)
	{
		tkns->d_r_r_f = open(t_sct.d_r_red[0],
				O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(next[1], 1);
		dup2(tkns->d_r_r_f, 1);
		close(next[1]);
		close(tkns->d_r_r_f);
		close(next[0]);
	}
}

void	fd_connect(int *prev, int *next,
	t_tokens *tkns, t_parser t_sct)
{
	fd_coonect_one(prev, next, tkns, t_sct);
	fd_coonect_two(prev, next, tkns, t_sct);
	fd_coonect_three(prev, next, tkns, t_sct);
	fd_coonect_four(next, tkns, t_sct);
}
