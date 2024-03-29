/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:20:54 by abuonomo          #+#    #+#             */
/*   Updated: 2024/01/11 15:09:25 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*var_container(t_token *token_lst, t_tree *tree, t_mini *mini, int op)
{
	static t_token	*this_token_lst;
	static t_tree	*this_tree;
	static t_mini	*this_mini;

	if (op == SET)
	{
		this_token_lst = token_lst;
		this_tree = tree;
		this_mini = mini;
		return (NULL);
	}
	else if (op == GET_TREE)
		return (this_tree);
	else if (op == GET_TOKENS)
		return (this_token_lst);
	else if (op == GET_MINI)
		return (this_mini);
	return (NULL);
}

int	ft_isredirection(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<"))
		return (1);
	return (0);
}

void	ctrl_d_case(char *str, t_mini *mini)
{
	printf("\n");
	free(str);
	free_env(mini);
	exit(0);
}

void	syntax_error(char *fixed)
{
	free(fixed);
	if (g_last_exit_status_cmd != 130)
	{
		ft_putstr_fd("Syntax error\n", 2);
		g_last_exit_status_cmd = 2;
	}
}

void	increment_shlvl(t_mini *mini)
{
	char	*shlvl;
	int		i;
	int		j;
	char	*num;

	i = -1;
	while (mini->env[++i])
	{
		if (!ft_strncmp(mini->env[i], "SHLVL=", ft_strlen("SHLVL=")))
		{
			shlvl = ft_strdup(mini->env[i]);
			free(mini->env[i]);
			j = ft_atoi(&shlvl[ft_strlen("SHLVL=")]);
			j++;
			free(shlvl);
			num = ft_itoa(j);
			mini->env[i] = ft_strjoin("SHLVL=", num);
			free(num);
			return ;
		}
	}
}
