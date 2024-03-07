/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:57:54 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/01/11 11:58:01 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user(t_mini *mini)
{
	int		i;
	char	*user;
	char	**line;

	i = 0;
	while (mini->env[i] && ft_strncmp(mini->env[i], "USER", 4))
		i++;
	if (!mini->env[i])
		return (NULL);
	line = ft_split(mini->env[i], '=');
	user = malloc((ft_strlen(line[1]) + 1) * sizeof(char));
	if (!user)
		return (NULL);
	user = ft_strcpy(user, line[1]);
	free_matrix(line);
	return (user);
}

static char	*get_dir(t_mini *mini)
{
	int		i;
	char	*dir;
	char	**line;
	char	**head;

	i = 0;
	while (mini->env[i] && ft_strncmp(mini->env[i], "PWD", 3))
		i++;
	if (!mini->env[i])
		return (NULL);
	line = ft_split(mini->env[i], '/');
	head = line;
	while (*line && *line + 1)
		line++;
	dir = malloc((ft_strlen(*--line) + 1) * sizeof(char));
	if (!dir)
		return (NULL);
	dir = ft_strcpy(dir, *line);
	free_matrix(head);
	return (dir);
}

// static char	*get_dir(t_mini *mini)
// {
// 	char	*dir;
// 	char	**line;

// 	while (*mini->env && ft_strncmp(*mini->env, "PWD", 3))
// 		mini->env++;
// 	if (!mini->env)
// 		return (NULL);
// 	line = ft_split(*mini->env, '/');
// 	dir = malloc(ft_strlen(line[4]) + 1 * sizeof(char));
// 	if (!dir)
// 		return (NULL);
// 	dir = ft_strcpy(dir, line[4]);
// 	free_matrix(line);
// 	printf("%s\n", line[4]);
// 	return (dir);
// }

char	*get_prompt(t_mini *mini)
{
	char	*dir;
	char	*user;
	char	*prompt;

	prompt = NULL;
	dir = get_dir(mini);
	user = get_user(mini);
	prompt = ft_strjoin(prompt, "\033[31;49;3;1m");
	prompt = ft_strjoin2(prompt, user);
	free(user);
	prompt = ft_strjoin2(prompt, "@Mini$hell🔥:\033[32m~/");
	prompt = ft_strjoin2(prompt, dir);
	free(dir);
	prompt = ft_strjoin2(prompt, "$ \033[0m");
	return (prompt);
}
