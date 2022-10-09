/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:36:24 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 21:10:04 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_main_utils(t_mainik *mainik,
	t_tokens *tokens, t_parser *tokens_struct, t_export_list ***exp_lst)
{
	while (tokens->tokens_list[mainik->i] != NULL)
	{
		tokens->ep_lst = 0;
		ft_split_for_parser(tokens, tokens->tokens_list[mainik->i]);
		ft_parser (tokens);
		mainik->prev_pipe[0] = mainik->next_pipe[0];
		mainik->prev_pipe[1] = mainik->next_pipe[1];
		if (tokens->tokens_list[mainik->i + 1] != NULL)
			pipe(mainik->next_pipe);
		else
		{
			mainik->next_pipe[0] = -1;
			mainik->next_pipe[1] = -1;
		}
		close(mainik->prev_pipe[1]);
		ft_c_d_l_red_util(tokens_struct, mainik->i, tokens);
		if (ft_c_l_red_utils(tokens_struct, mainik->i, tokens) == 0)
			break ;
		mainik->tkn = tokens->ep_lst;
		ft_tkn(mainik, tokens, tokens_struct, exp_lst);
		mainik->i++;
	}
}

void	ft_free_helper(t_parser *tokens_struct, t_tokens *tokens)
{
	int	i;

	i = 0;
	free(tokens_struct);
	while (tokens->tokens_list[i] != NULL)
	{
		free(tokens->tokens_list[i]);
		i++;
	}
	free(tokens->tokens_list);
	free(tokens->ep_lst);
}

void	ft_main_loop(t_tokens *tokens, t_parser *tokens_struct,
	t_mainik *mainik, t_export_list ***exp_lst)
{
	while (1)
	{
		tokens->flag_error = 0;
		tokens->input = readline("minishell$ ");
		if (tokens->input == NULL)
			tokens->input = "exit";
		add_history(tokens->input);
		ft_for_parser(tokens);
		if (ft_strchr(tokens->input, '|'))
			ft_for_pipe(tokens);
		tokens_struct = ft_lexer(tokens);
		tokens->r_r_f = 0;
		tokens->d_r_r_f = 0;
		tokens->left_red_flag = 0;
		mainik->i = 0;
		if (tokens->input != NULL)
		{
			if (tokens->input[0] != '\0')
				ft_main_utils(mainik, tokens, tokens_struct, exp_lst);
			else
				continue ;
		}
		close(mainik->prev_pipe[0]);
		ft_free_helper(tokens_struct, tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_tokens		tokens;
	t_export_list	**exp_lst;
	t_parser		*tokens_struct;
	t_mainik		mainik;

	tokens_struct = 0;
	ft_struct_init(&tokens);
	ft_init_mstruct(&mainik, envp, argc, argv);
	ft_parse_vpath(&tokens, envp);
	ft_crt_envp_list(&tokens, envp);
	signals();
	mainik.path = ft_cp_path_arr(&tokens);
	mainik.next_pipe[0] = -1;
	mainik.next_pipe[1] = -1;
	ft_main_loop(&tokens, tokens_struct, &mainik, &exp_lst);
	return (g_exit);
}
