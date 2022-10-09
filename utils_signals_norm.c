/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals_norm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:11:01 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 01:11:03 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	sig_in(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putstr_fd("\n", 1);
}

void	sig_quit(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 1);
	}
	else
		ft_putstr_fd("Quit: 3\n", 1);
}

void	sig_handler(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
		sig_in(pid);
	else if (signum == SIGQUIT)
		sig_quit(pid);
}

void	signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
