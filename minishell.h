/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:46:21 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 19:04:31 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "./libft/libft.h"
# include <fcntl.h>

int	g_exit;

typedef struct s_tokens
{
	char		**tokens_list;
	int			*tokens_prior;
	char		**path_list;
	char		**envp_list;
	char		**export_list;
	char		**mini_export_list;
	int			export_flag;
	char		**right_red;
	char		*dbl_right_red;
	char		**left_red;
	int			r_r_f;
	int			d_r_r_f;
	int			left_red_flag;
	int			flag_j_cnt;
	char		**ep_lst;
	int			flag_q;
	char		*input;
	char		*red_input;
	int			path_cnt;
	int			flag_error;
	int			cnt_tokens;
	int			h_lev;
	int			flag;
}				t_tokens;

typedef struct s_export_list
{
	char		*tkn;
	char		*v;
	char		*var;
	int			cnt_tkn;
}				t_export_list;

typedef struct s_parser
{
	char		*tkn;
	char		*iter;
	int			i;
	int			c_d_l_red;
	char		**d_l_red;
	int			c_d_r_red;
	char		**d_r_red;
	int			c_l_red;
	char		**l_red;
	int			c_r_red;
	char		**r_red;
}				t_parser;

typedef struct s_mainik
{
	pid_t		pid;
	int			prev_pipe[2];
	int			next_pipe[2];
	int			res_f;
	char		**path;
	int			res_stat;
	struct stat	buf[4096];
	char		**envp;
	char		**tkn;
	int			i;
	int			cnt_tkn;
}				t_mainik;

t_export_list	*ft_parse_export_tkn_flag(t_export_list *alst, char **tkn);
t_export_list	*ft_parse_export_tkn(t_export_list	*alst, char **tkn);
t_export_list	**ft_crt_mini_export_list(t_tokens *tokens,
					t_export_list **tmp2);
t_parser		*ft_lexer(t_tokens *tokens);

char			**ft_split(char const *s, char c);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			**ft_split_mult(char const *s, char c1, char c2, char c3);
/// MAIN
int				ft_cnt_d_quotes(char *str);
int				ft_cnt_quotes(char *str);
void			ft_split_for_parser(t_tokens *tokens, char *str);
int				ft_cnt_j(char *s, int *flag_join_d, int *flag_join);
void			ft_cnt_tkn_d(int *flag_join_d, char *s, int *cnt_tkn);
void			ft_cnt_tkn(int *flag_join, char *s, int *cnt_tkn);
char			*ft_full_one(t_tokens *tokens, char *s, int *flag_join,
					int *cnt_tkn);
char			*ft_full_d_one(t_tokens *tokens, char *s, int *flag_join_d,
					int *cnt_tkn);
int				ft_cnt_j_all(char **tmp3, int *flag_join_d, int *flag_join,
					int *cnt_tkn);
void			ft_full_all(t_tokens *tokens, char **tmp3, int *flag_join,
					int *flag_join_d);
/// PAR		ERS_FUNCTION
void			ft_parser(t_tokens *tokens);
void			ft_for_parser(t_tokens *tokens);
void			ft_for_pipe(t_tokens *tokens);
int				ft_chek_pipes(t_tokens *tokens);
void			ft_print_error(t_tokens *tokens, int f);
int				ft_count_cnt(int i, int *cnt, char *str, char c);
void			ft_free_str(char ***str);
int				utils_chek_pipes(char *tmp3, int i, int *pipe,
					t_tokens *tokens);
char			**ft_split_modif(char *s, char c, int nb);
int				ft_next_step(int i, char const *s);
int				ft_skip_quote(int i, unsigned int *next_str_len,
					char **next_str);
int				ft_chek_simb(char c);
void			get_status(t_tokens *tokens);
int				ft_new_ep_lst(t_tokens *tokens, int str, int pos, int start);
int				ft_flag_q(t_tokens *tokens, int start, int str, int pos);
int				ft_chek_flag(t_tokens *tokens, char *tmp2);
int				ft_full_ep(t_tokens *tokens, int j, int str, int start);
int				ft_q_all(t_tokens *tokens, int str, int start, int pos);
int				ft_simb_pos(t_tokens *tokens, int str, int pos);
// ALL		
void			ft_struct_init(t_tokens *tokens);
void			ft_parse_vpath(t_tokens *tokens, char **envp);
int				ft_what_function(t_tokens *tokens, int i,
					t_export_list ***alst);
void			ft_crt_envp_list(t_tokens *tokens, char **envp);
void			ft_cd(t_tokens *tokens, int k);
int				ft_count_smbls(char *str, char smbl);
void			ft_export(t_tokens *tokens, int j, t_export_list ***alst);
void			ft_crt_export_arr(t_tokens *tokens, char	**tkn);
void			ft_clear(char **str, int start, int end);
void			ft_exp_list_to_arr(t_export_list *alst, t_tokens *tokens,
					char **tkn);
void			ft_unset(t_tokens *tokens, char **tkn);
void			signals(void);
void			get_status(t_tokens *tokens);
void			ft_env(t_tokens *tokens);
char			*ft_pwd(void);
int				ft_same(t_tokens *tokens, char *str, int j, int i);
void			ft_echo(t_tokens *tokens, int j);
char			*ft_pwd_for_cd(void);
char			**ft_arrdup(char **arr);
void			ft_mini_export(t_tokens *tokens, int j);
void			ft_exp_list_to_arr_flag(t_export_list *alst, t_tokens *tokens,
					char **tkn);
void			ft_exp_list_to_arr_flag_lst(t_tokens *tokens, int cnt,
					int cnt_exp, t_export_list *ex_lst);
char			*ft_dbl_lft_red_help_two(char **tmp, int cnt);
int				ft_dbl_lft_red(t_parser *tkn_strc, t_tokens *tokens, int i,
					int j);
int				ft_dbl_lft_red_help_one(t_parser *tkn_strc, t_tokens *tokens,
					int i, int j);
int				ft_dbl_rght_red(t_parser *tkn_strc, int i, t_tokens *tokens,
					int j);
int				ft_lft_red(t_parser *tkn_strc, int i, t_tokens *tokens, int j);
int				ft_redirect_if_two(char **tmp, int k);
int				ft_redirect_if_one(char **tmp, int k);
void			ft_red_helper_one(t_parser *tkn_strc, t_tokens *tokens);
char			*ft_lft_red_helper(char **tmp, int cnt);
int				ft_dbl_rght_red_help_one(t_parser *tkn_strc, t_tokens *tokens,
					int i, int j);
char			*ft_dbl_rght_red_help_two(char **tmp, int cnt);
int				ft_rght_red(t_parser *tkn_strc, int i, t_tokens *tokens, int j);
void			ft_r_red(t_parser *tkn_strc, int i);
void			ft_c_l_red(t_parser *tkn_strc, int i);
void			ft_d_r_red(t_parser *tkn_strc, int i);
void			fd_connect(int	*prev, int *next, t_tokens *tokens,
					t_parser tokens_struct);
char			**ft_cp_path_arr(t_tokens *tokens);
int				ft_c_l_red_utils(t_parser *tokens_struct, int i,
					t_tokens *tokens);
void			ft_c_d_l_red_util(t_parser *tokens_struct, int i,
					t_tokens *tokens);
void			ft_init_mstruct(t_mainik *mainik, char **envp, int argc,
					char **argv);
void			ft_tkn(t_mainik *mainik, t_tokens *tokens,
					t_parser *tokens_struct, t_export_list ***exp_lst);
#endif