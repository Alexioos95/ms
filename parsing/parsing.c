/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/07/05 15:45:51 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


int	ft_start(int nb_cmd, t_list *pars_lst, char **ev)
{
	char		*in;
	char		*out;
	t_struct	*m;

	m = NULL;
	m = ft_init(m, nb_cmd, pars_lst, ev);
	if (!m)
		return (1);
	in = NULL;
	out = NULL;
	m->bhole = open("/dev/null", O_WRONLY);
	ft_openin(m, in);
	if (nb_cmd >= 2 && ev)
		ft_pipex(m, out, in);
	else if (nb_cmd == 1 && ev)
		ft_forkex(m, in, out);
	ft_free_process(m, errno);
	return (1);
}

// Parser.
int	parser(struct s_shell *ms)
{
	if (ms->split != NULL)
	{
		freesplit(ms->split);
		ms->split = NULL;
	}
	if (ms->line == NULL)
		return (0);
	if (checkorphanbracket(ms->line) == 1 || checkorphanquote(ms->line) == 1)
		return (2);
	// ms->lexer = split_pipe(ms->line, ms);
	ft_parcour(ms);
	if (ms->lexer)
	{
		printf("Taille du Lexer: %d\n", ms->lexer->len);
		ft_print_lexerlst(ms->lexer);
	}
	return (0);
}


int	ft_state(char *str, int state)
{
	if ((state == 0) && (str[0] != ' ' && str[0] != '\"' && str[0] != '\''))
		state = 1;
	else if (state == 1 && (str[0] == ' '))
		state = 0;
	else if (str[0] == '\"' && (state == 0 || state == 1))
		state = 2;
	else if (str[0] == '\"' && (state == 2 && (str[1] == ' ' || !str[1])))
		state = 0;
	else if (str[0] == '\'' && (state == 0 || state == 1))
		state = 3;
	else if (str[0] == '\'' && (state == 3 && str[1] == ' '))
		state = 0;
	else if (str[0] == '\'' && (state == 3 && str[1] != ' '))
		state = 1;
	return (state);
}

t_tokens	ft_newtoken(char *token, char *arg)
{
	t_tokens	new;

	new.token = token;
	new.arg = arg;
	return (new);
}

int	ft_is_arg(char *str, int state)
{
	int		i;
	char	*token;

	i = 0;
	if (!str)
		return (0);
	while ((!ft_istoken(&str[i], state) || \
		ft_state(&str[i], state)) && str[i])
		i++;
	token = ft_istoken(str, state);
	if (token)
		ft_errors_1_5(0, token);
	free(token);
	return (i);
}

int	ft_is_goodtoken(char *curr_token)
{
	int		i;
	int		len;
	char	**good_token;

	i = 0;
	if (!curr_token)
		return (0);
	good_token = ft_split("<< >> || && < > |", ' ');
	while (good_token[i])
	{
		if (ft_strcmp(curr_token, good_token[i]))
		{
			len = ft_strlen(good_token[i]);
			freesplit(good_token);
			return (len);
		}
		i++;
	}
	ft_errors_1_5(0, &curr_token[ft_strlen(curr_token) - 1]);
	freesplit(good_token);
	free(curr_token);
	return (0);
}

char	*ft_istoken(char *str, int state)
{
	int		i;
	int		y;
	char	*tokens;
	char	*curr_token;

	if (state >= 2 || !str)
		return (NULL);
	tokens = "<>|&";
	i = 0;
	y = 0;
	// printf("In ft_token\n");
	while (tokens[i] && str[y])
	{
		if (tokens[i] == str[y])
		{
			y++;
			i = 0;
			// printf("en boucle\n");
			// printf("State: %d\n", state);
		}
		else
			i++;
	}
	curr_token = ft_substr(str, 0, y);
	if (y)
		return (curr_token);
	return (NULL);
}

int	ft_isword(char *str, int state)
{
	int	i;
	int	curr_state;
	int	tmp_state;

	i = 0;
	if (!str)
		return (0);

	curr_state = ft_state(&str[i], state);
	tmp_state = curr_state;
	while ((curr_state != 0) && str[i])
	{
		if (ft_istoken(&str[i], curr_state))
			return (i);
		// printf("State: %d!\n", curr_state);
		if (!str[i] || (str[i] == ' ' && (curr_state == 0 || curr_state == 1)))
			return (i);
		i++;
		curr_state = ft_state(&str[i], curr_state);
	}
	return (i + 1);
}

int ft_instate(char *line, int state, t_lexer **lexer, int i)
{
	int			word_len;
	char		*word;
	t_tokens	new_token;

	new_token = ft_newtoken(NULL, NULL);
	// printf("IN_ft_instate_Chara: %c\n", line[i]);
	word_len = ft_isword(&line[i], state);
	if (word_len > 0)
	{
		word = ft_substr(line, i, word_len);
		ft_lstaddback_lexer(lexer, ft_lstnew_lexer(word, new_token));
		i += word_len;
	}
	else
		i += ft_token_or_word(line, state, lexer, i);
		// word_len = ft_strlen(ft_istoken(&line[i], state));
	return (i);
}

int	ft_findword(char *line, int state, t_lexer **lexer, int i)
{
	int			word_len;
	char		*word;
	t_tokens	new_token;

	new_token = ft_newtoken(NULL, NULL);
	word_len = ft_isword(&line[i], state);
	if (word_len > 0)
	{
		word = ft_split(ft_substr(line, i, word_len), ' ')[0];
		ft_lstaddback_lexer(lexer, ft_lstnew_lexer(word, new_token));
	}
	i = i + word_len;
	return (i);
}

int	ft_token_or_word(char *line, int state, t_lexer **lexer, int i)
{
	int			token_len;
	int			arg_len;
	char		*token;
	char		*t_arg;
	t_tokens	new_token;

	while (line[i] && line[i] == ' ' && state == 0)
		i++;
	token = ft_istoken(&line[i], state);
	token_len = ft_strlen(token);
	arg_len = 0;
	if (token)
	{
		i += token_len;
		while (line[i] && line[i] == ' ' && state == 0)
			i++;
		arg_len = ft_isword(&line[i + token_len], state);
		t_arg = ft_split(ft_substr(line, i + token_len, arg_len), ' ')[0];
		new_token = ft_newtoken(token, t_arg);
		ft_lstaddback_lexer(lexer, ft_lstnew_lexer(NULL, new_token));
		return (i + token_len + arg_len);
	}
	else
		return (ft_findword(line, state, lexer, i));
}

void	ft_parcour(t_shell *ms)
{
	int			i;
	// int			state;
	char		*line;
	t_lexer		*lexer;

	line = ms->line;
	i = 0;
	lexer = NULL;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		i = ft_instate(line, 0, &lexer, i);
	}
	ms->lexer = lexer;
}
// void	ft_parcour(t_shell *ms)
// {
// 	int			i;
// 	int			state;
// 	char		*line;
// 	t_lexer		*lexer;

// 	i = 0;
// 	line = ms->line;
// 	lexer = NULL;
// 	printf("first\n");
// 	state = ft_state(&line[i], 0);
// 	printf("Start State: %d!!!\n", state);
// 	printf("Start Charactere: %c!!!\n", line[i]);
// 	while (line[i])
// 	{
// 		while (state == 0 && line[i])
// 		{
// 			printf("Token or word\n");
// 			i = ft_token_or_word(line, state, &lexer, i);
// 			state = ft_state(&line[i], state);
// 			printf("Token or word_End\n");
// 		}
// 		while (state != 0 && line[i])
// 		{
// 			printf("InState: %d\n", state);
// 			i = ft_instate(line, state, &lexer, i);
// 			state = ft_state(&line[i], state);
// 			// printf("State: %d!\n", state);
// 		}
// 	}
// 	ms->lexer = lexer;
// }

		// state = ft_state(line[i], 0);
	// printf("ETAT:%d au Charactere: %c\n", tmp_state, line[i + word_len]);

// tro"pomme>lo"

// faire une state machine 
// parcourir la ligne char par char
// etat si "quote" "double quote" "espace rencontrer"
// mettre dans une node ce qui etait avant et continuer
// exemple test>test>test ls -la | awk '"{print $1}"' | "il faut ouvrir les"
// state = 0 au debut
// on parcoure la ligne et on rencontre un token > < | &
// comme letat est a zero on prend test et on le met dans la node lexer
// check si le premier char du token est <>|& et si le deuxième est identique
// 	renvoyer la lg du token (1 ou 2)
// 	sinon, 0
// mettre le token dans lexer.token
// on met dans la meme node lexer token son arg sil ya sauf si c'est un pipe
// toujours avec les regles de state machine


// if (ft_strncmp(ms->line, "echo", 4) == 0)		// .
// 	ft_echo(ms->split[1], ms->split[2]);		// .
// else if (ft_strncmp(ms->line, "pwd", 3) == 0)	// .
// 	ft_pwd(ms);									// .
// else if (ft_strncmp(ms->line, "cd", 2) == 0)	// .
// 	ft_cd(ms, ms->split[1]);					// .
// else if (ft_strncmp(ms->line, "exit", 4) == 0)	// .
// 	ft_exit(ms, ms->split[1]);					// .
// else if (ft_strncmp(ms->line, "env", 3) == 0)	// .
// 	ft_env(ms, ms->split[1]);					// .
// else if (ft_strncmp(ms->line, "unset", 5) == 0)	// .
// 	ft_unset(ms, ms->split[1], ms->split[2]);	// .
// else if (ft_strncmp(ms->line, "export", 6) == 0)// .
// 	ft_export(ms, ms->split[1]);				// -----------------------


// int	ft_token_or_word(char *line, int state, t_lexer **lexer, int i)
// {
// 	int			token_len;
// 	int			arg_len;
// 	char		*token;
// 	char		*t_arg;
// 	t_tokens	new_token;

// 	token = ft_istoken(&line[i], state);
// 	token_len = ft_is_goodtoken(token);
// 	arg_len = 0;
// 	if (token)
// 	{
// 		if (!token_len)
// 			return (i + ft_strlen(token));
// 		else
// 		{
// 			arg_len = ft_is_arg(&line[i + token_len], state);
// 			t_arg = ft_split(ft_substr(line, i + token_len, arg_len), ' ')[0];
// 			new_token = ft_newtoken(token, t_arg);
// 			ft_lstaddback_lexer(lexer, ft_lstnew_lexer(NULL, new_token));
// 			return (i + token_len + arg_len);
// 		}
// 	}
// 	else
// 		return (ft_findword(line, state, lexer, i));
// }
// int	ft_isword(char *str, int state)
// {
// 	int	i;
// 	int	c;

// 	i = 0;
// 	c = state;
// 	if (!str)
// 		return (0);
// 	while (((ft_istoken(&str[i], c) == 0 || c == state) )&& &str[i])
// 	{
// 		c = ft_state(str[++i], c);
// 		if (!str[i] || (str[i] == ' ' && c == 0 && str[i - 1] != ' '))
// 			return (i);
// 	}
// 	return (i);
// }

// <in   echo   “COUCOU’>> |‘TU’‘VAS’ && || < BIEN?””top”>out|<<eof 
//  cat   >>    out |ls -la&&cat||yes


// int	ft_unexpected_token(int error, char *str, char *tokens)
// {
// 	int		i;
// 	int		y;
// 	char	bad_token[2];
// 	char	**good_token;

// 	i = 0;
// 	printf("WTF\n");
// 	good_token = ft_split("<> >< <<< >> | || &&", ' ');
// 	while (i < 2 && str[i])
// 	{
// 		y = 0;
// 		while (tokens[y] && tokens[y] != str[i])
// 			y++;
// 		if (tokens[y] == str[i])
// 			bad_token[i] = str[i];
// 		i++;
// 	}
// 	i = 0;
// 	y = 0;
// 	while (good_token[i] && y == 0)
// 		y = ft_strcmp(bad_token, good_token[i++]);
// 	i = ft_errors_1_5(error, good_token[i - 1]);
// 	freesplit(good_token);
// 	return (i);
// }

// int	ft_tokencmp(char c)
// {
// 	int		i;
// 	char	*tokens;			printf("en boucle\n");


// 	tokens = "<>|&";
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		if (tokens[i++] == c)
// 			return (1);
// 	}
// 	return (0);
// }

// int	ft_istoken(char *str, int state)
// {
// 	int			i;
// 	int			y;
// 	int			token_len;
// 	char		*tokens;

// 	i = 0;
// 	y = 0;
// 	if (state != 0)
// 		return (0);
// 	token_len = 0;
// 	tokens = "<>|&";
// 	while (tokens[i] && tokens[i] != str[0])
// 		i++;
// 	if (tokens[i] == str[0])
// 	{
// 		token_len = 1;
// 		while (tokens[y] && tokens[y] != str[1])
// 			y++;
// 		if (str[1] == str[0])
// 			token_len = 2;
// 		else if (tokens[y] == str[1] && str[1] != str[0])
// 			token_len = ft_unexpected_token(0, &str[1], tokens);
// 	}
// 	return (token_len);
// }

// if (str[1] == str[0]) 
// cas : >> << || &&

// else if (tokens[y] == str[1] && str[1] != str[0])
// cas : >< >| >& <> <| <& |< |> |& &< &> &|
