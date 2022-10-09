/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_five_norm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:37:15 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 20:44:32 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_execve_extra(t_mainik *mnk, t_tokens *tkns, int j)
{
	mnk->path[j] = ft_strjoin(mnk->path[j], "/");
	mnk->path[j] = ft_strjoin(mnk->path[j], mnk->tkn[0]);
	if (mnk->path[j] == NULL)
	{
		tkns->flag_error = 1;
		return ;
	}
	mnk->res_stat = stat(mnk->path[j], mnk->buf);
}

void	ft_init_mstruct(t_mainik *mainik, char **envp, int argc, char **argv)
{
	(void) argv;
	mainik->pid = 0;
	mainik->res_f = 0;
	mainik->path = 0;
	mainik->res_stat = 0;
	mainik->envp = envp;
	mainik->tkn = 0;
	mainik->i = 0;
	mainik->cnt_tkn = 0;
	if (argc != 1)
		printf("Error argument\n");
}

void	ft_execve(t_mainik *mnk, t_tokens *tkns)
{
	int	j;

	if (mnk->res_f != 2)
	{
		j = -1;
		if (ft_strchr(mnk->tkn[0], '/'))
			tkns->flag = execve(mnk->tkn[0], mnk->tkn, mnk->envp);
		else
		{
			while (++j < tkns->path_cnt)
			{			
				ft_execve_extra(mnk, tkns, j);
				if (mnk->res_stat == 0)
				{
					tkns->flag = execve(mnk->path[j], mnk->tkn, mnk->envp);
					break ;
				}
			}
			if (j == tkns->path_cnt && mnk->res_stat != 0)
				printf("minishell: %s: command not found\n", mnk->tkn[0]);
		}
		exit(tkns->flag);
	}
	else
		exit(mnk->pid);
}

void	ft_loop(t_mainik *mainik, t_tokens *tokens,
	t_parser *tokens_struct, t_export_list ***exp_lst)
{
	mainik->pid = fork();
	if (mainik->pid == 0)
	{
		fd_connect(mainik->prev_pipe,
			mainik->next_pipe, tokens, tokens_struct[mainik->i]);
		mainik->res_f = ft_what_function(tokens, mainik->i, exp_lst);
		ft_execve(mainik, tokens);
	}
	if (mainik->pid < 0)
	{
		write(2, "error: fatal\n", 13);
		exit(1);
	}
	waitpid(-1, &tokens->flag, 0);
}

void	ft_tkn(t_mainik *mainik, t_tokens *tokens,
	t_parser *tokens_struct, t_export_list ***exp_lst)
{
	if (mainik->tkn[0])
	{
		mainik->cnt_tkn = 0;
		while (mainik->tkn[mainik->cnt_tkn] != NULL)
				mainik->cnt_tkn++;
		if (!(ft_strncmp(mainik->tkn[0], "exit", 4096)))
		{
			printf("exit\n");
			exit(0);
		}
		else if (!(ft_strncmp(mainik->tkn[0], "cd", 4096)))
		{
			if (mainik->cnt_tkn > 1)
				ft_cd(tokens, mainik->i);
			mainik->res_f = 2;
		}
		else if (mainik->cnt_tkn > 1
			&& ft_strncmp(mainik->tkn[0], "export", 10) == 0)
			ft_crt_export_arr(tokens, mainik->tkn);
		else if (mainik->cnt_tkn > 1
			&& ft_strncmp(mainik->tkn[0], "unset", 10) == 0)
			ft_unset(tokens, mainik->tkn);
		else
			ft_loop(mainik, tokens, tokens_struct, exp_lst);
	}
}
