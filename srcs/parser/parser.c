/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/06 21:10:04 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	check_for_exit_status(t_min *tk, t_parser *all_words)
{
	int			len;
	char		*new;
	t_parser	*p;

	p = all_words;
	while (p)
	{
		len = ft_strlen(p->word);
		if (ft_strncmp(p->word, "$?", 3) && (ft_strnstr(p->word, "$?", len)))
		{
			len = len - ft_strlen(ft_strnstr(p->word, "$?", len));
			new = ft_strjoin(ft_substr(p->word, 0, len), \
				ft_itoa(tk->exit_value));
			if (!new)
				return (MALLOC);
			new = ft_strjoin(new, ft_strnstr(p->word, "$?", \
				ft_strlen(p->word)) + 2);
			if (!new)
				return (free_pointer(new, MALLOC));
			free(p->word);
			p->word = new;
		}
		p = p->next;
	}
	p = all_words;
	while (p)    // This while is just for printing the resulted structure
	{
		printf("Temp:-->%p\n", p);
		printf("Word:--%s--\n", p->word);
		printf("Next:-->%p\n", p->next);
		printf("Before:-->%p\n\n", p->before);
		p = p->next;
	}
	printf("Temp: %p\n", p);
	return (0);
}

void	set_vars(t_vars *v, char *s)
{
	v->i = -1;
	v->count = -1;
	v->sq = 0;
	v->dq = 0;
	v->oq = 1;
	v->nq = 0;
	v->stp = 0;
	v->s = s;
}

int	add_word(t_parser **temp, char *word)
{
	t_parser	*new;

//	printf("Add word: --%s--\n", word);
	if (!word)
		return (MALLOC);
	if (!(*temp)->word)
		(*temp)->word = word;
	else
	{
		new = (t_parser *)malloc(sizeof(t_parser));
		if (!new)
		{
			free(word);
			return (MALLOC);
		}
		new->word = word;
		new->next = NULL;
		new->before = (*temp);
		(*temp)->next = new;
		(*temp) = (*temp)->next;
		new = NULL;
	}
	return (0);
}

int	add_redir(t_parser **temp, t_vars *v, int *idx, int redir)
{
	char	*word;

	if (redir > 0 && (v->s[*idx] == '<' || v->s[*idx] == '>'))
	{
		if ((v->s[*idx] == '<' && v->s[*idx + 1] == '<')
			|| (v->s[*idx] == '>' && v->s[*idx + 1] == '>'))
		{
			redir++;
			(*idx)++;
		}
		word = ft_substr(v->s, v->stp, redir);
		if (!word || add_word(temp, word))
			return (MALLOC);
	}
	v->stp = *idx + 1;
	return (0);
}

int	create_word(t_parser **temp, t_vars *v, int *k, int mode)
{
	int		len;
	char	*word;

	printf("Create word: Idx: %d\tStart: %d\tCar start: --%c--\tCar Idx: --%c--\n", *k, v->stp, v->s[v->stp], v->s[*k]);
	if (!mode)
	{
		printf("Mode 0\n");
		len = 1;
		if ((v->s[*k] == '<' && v->s[*k + 1] == '<')
			|| (v->s[*k] == '>' && v->s[*k + 1] == '>'))
		{
			len++;
			(*k)++;
		}
	}
	else
	{
		printf("Mode 1\n");
		len = *k - v->stp;
		if (!len)
			return (0);
	}
	printf("Len: %d\n", len);
	word = ft_substr(v->s, v->stp, len);
	if (!word || add_word(temp, word))
		return (MALLOC);
	v->stp += len;
	printf("End start: %d\n\n", v->stp);
	return (0);
//	redir = 0;
//	if (*idx == v->stp && v->s[*idx] == ' ')
//		return (0);
//	if (*idx == v->stp)
//		len = 1;
//	else
//	{
//		redir++;
//		len = *idx - v->stp;
//	}
//	if (len == 1 && ((v->s[*idx] == '<' && v->s[*idx + 1] == '<')
//		|| (v->s[*idx] == '>' && v->s[*idx + 1] == '>')))
//	{
//		len++;
//		(*idx)++;
//	}
//	else if (v->s[*idx + 1] == '\0' && v->s[*idx] != ' '
//		&& v->s[*idx] != '<' && v->s[*idx] != '>')
//		len++;
//	printf("Len: %d\n", len);
//	word = ft_substr(v->s, v->stp, len);
//	if (!word || add_word(temp, word))
//		return (MALLOC);
//	v->stp = v->stp + len;
//	printf("Start point: %d\n", v->stp);
//	return (add_redir(temp, v, idx, redir));
}

int	find_more_words(t_parser **temp, t_vars *v)
{
	int	k;

	k = v->stp - 1;
	printf("\nBefore: Arr 4: %d\tK: %d\tI: %d\n", v->stp, k, v->i);
	while (++k < v->i)
	{
		if (v->s[k] == '<' || v->s[k] == '>'
			|| v->s[k] == '|')
		{
			if (k - v->stp > 0 && create_word(temp, v, &k, 1))
				return (MALLOC);
			if (create_word(temp, v, &k, 0))
				return (MALLOC);
		}
	}
	printf("After:  Arr 4: %d\tK: %d\tI: %d\n", v->stp, k, v->i);
	if (v->s[v->i + 1] == '\0')
		k++;
	if (create_word(temp, v, &k, 1))
		return (MALLOC);
	return (0);
}

int	take_one_word(t_parser **temp, t_vars *v, int *i, int mode)
{
	int		k;
	int		l;
	int		sq;
	int		dq;
	int		end;
	int		count;
	char	*word;

	(void)temp;
	(void)mode;
	end = *i;
	count = 0;
	sq = 0;
	dq = 0;
	k = v->stp - 1;
	if ((v->s[*i] == '<' && v->s[*i + 1] == '<')
		|| (v->s[*i] == '>' && v->s[*i + 1] == '>'))
		end++;
	while (++k < end)
	{	
		if (v->s[k] == '\"' && !dq && !sq)
			dq++;
		else if (v->s[k] == '\'' && !dq && !sq)
			sq++;
		else if (v->s[k] == '\"' && dq && !sq)
			dq--;
		else if (v->s[k] == '\'' && !dq && sq)
			sq--;
		else
			count++;
	}
	word = (char *)malloc(sizeof(char) * (count + 1));
	if (!word)
		return (MALLOC);
	l = v->stp - 1;
	k = v->stp - 1;
	while (++k < end)
	{		
		if (v->s[k] == '\"' && !dq && !sq)
			dq++;
		else if (v->s[k] == '\'' && !dq && !sq)
			sq++;
		else if (v->s[k] == '\"' && dq && !sq)
			dq--;
		else if (v->s[k] == '\'' && !dq && sq)
			sq--;
		else
			word[++l] = v->s[k];
	}
	word[++l] = '\0';
	//	if (mode)
	//	{
	//		word = ft_substr(v->s, v->stp, *i - v->stp + 1);
	//		if (!word || add_word(temp, word))
	//			return (MALLOC);
	//		return (0);
	//	}
	return (0);
}

int	add_redir(t_parser **temp, t_vars *v, int *i, int *count)
{
	// Aggiungere la parola prima della redirezione e aggiungere la redirezione e aggiornare i e count
}

int	take_words(t_parser **temp, t_vars *v)
{
	int		i;
	int		sq;
	int		dq;
	int		count;

	i = v->stp - 1;
	((sq = 0) && (dq = 0) && (count = 0));
	while (++i < v->i)
	{
		if (v->s[i] == '\"' && !dq && !sq)
			dq++;
		else if (v->s[i] == '\'' && !dq && !sq)
			sq++;
		else if (v->s[i] == '\"' && dq && !sq)
			dq--;
		else if (v->s[i] == '\'' && !dq && sq)
			sq--;
		else if ((v->s[i] == '<' || v->s[i] == '>' || v->s[i] == '|')
			&& !dq && !sq && add_redir(temp, v, &i, &count))
				return (MALLOC);
		else
			count++;
	}
	return (0);
//	printf("Count: %d\n", count);
//	word = (char *)malloc(sizeof(char) * (count + 1));
//	if (!word)
//		return (NULL);
//	i = v->stp - 1;
//	l = -1;
//	sq = 0;
//	dq = 0;
//	while (v->s[++i])
//	{		
//		if (v->s[i] == '\"' && !dq && !sq)
//			dq++;
//		else if (v->s[i] == '\'' && !dq && !sq)
//			sq++;
//		else if (v->s[i] == '\"' && dq && !sq)
//			dq--;
//		else if (v->s[i] == '\'' && !dq && sq)
//			sq--;
//		else
//			word[++l] = v->s[i];
//	}
//	word[++l] = '\0';
//	return (word);
}

int	find_word(t_parser **temp, t_vars *v)
{
//	char	*word;

//	printf("Check quotes\n");
	check_quotes(v, v->s[v->i]);      // This function is used to count the number of quotes and to check
                                                // whether you are in a simple or double quote or in neither of those
	if (((v->s[v->i] == ' ' && v->oq)                    // This if is used to take a word, or multiple words if they are
		|| (v->s[v->i + 1] == '\0' && v->s[v->i] != ' '))) // all together and you put some special symbols into a single word
	{
		if (v->nq)   // This variable is to check if your word has quotes or not
		{
			if (take_words(temp, v))
				return (MALLOC);
//			if (!word || add_word(temp, word))
//				return (MALLOC);
		}
		else if (find_more_words(temp, v))
			return (MALLOC);
		v->nq = 0;
	}
	return (0);
}

int	parse_string(t_min *tk, t_parser *all_words, char *env[], char *s)
{
	t_vars		v;
	t_parser	*temp;

	set_vars(&v, s);  // Here I set the structure with all variables
	temp = all_words;    // This temp is the one used to create every word, since the pointer 'all_words'
	while (s[++v.i])  // has always to point to the first word
	{
		if ((s[v.i] == ' ' && v.i == 0 && v.oq)
				|| (s[v.i - 1] == ' ' && s[v.i] == ' ' && v.oq))
			while (s[v.i] == ' ')
				v.i++;
		if ((s[v.i - 1] == ' ' || v.i == 0)
			&& s[v.i] != ' ' && v.oq)
			v.stp = v.i;
		if (s[v.i] == '$'
			&& (v.oq || (!v.oq && v.dq)))
			if (check_env_var(&temp, &v, env))
				return (MALLOC);
		if (s[v.i] == '\0')
			break ;
		if (find_word(&temp, &v)) // Here I find the words or the multiple words to put into the all_words structure
			return (MALLOC);
	}
	printf("\n");
	return (check_for_exit_status(tk, all_words));
}

int	parser(t_min *tk, char *env[], char *string)
{
	t_parser	*all_words;

	if (count_quotes(string))    // If the line you write has a impair number of quotes, the program will just stop
		return (free_tokens(&tk, NULL, SYNTAX));
	all_words = (t_parser *)malloc(sizeof(t_parser));
	if (!all_words)
		return (free_tokens(&tk, NULL, MALLOC));
	all_words->word = NULL;
	all_words->next = NULL;
	all_words->before = NULL;
	if (parse_string(tk, all_words, env, string))    // Here I parse the string and separate it into words
		return (free_tokens(&tk, &all_words, MALLOC));
//	return (load_commands(tk, all_words));           // Here I load all the words into commands in the main sucture
	exit(0);
}
