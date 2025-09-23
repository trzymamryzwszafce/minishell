#include "../minishell.h"

static int	is_meta(char c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|'); //zmienić ' ' na is white space
}

static int	is_quote(char c)
{
	return (c == 39 || c == 34);
}

static void	adv_plain(const char *s, int *i, int *cnt)
{
	while (s[*i] && !is_meta(s[*i]) && !is_quote(s[*i]))
	{
		(*i)++;
		(*cnt)++;
	}
}

static void	adv_quoted(const char *s, int *i, int *cnt)
{
	char	q;

	q = s[*i];
	(*i)++;
	(*cnt)++;
	while (s[*i] && s[*i] != q)
	{
		(*i)++;
		(*cnt)++;
	}
	if (s[*i] == q)
	{
		(*i)++;
		(*cnt)++;
	}
}

static void	advance_word(const char *s, int *i, int *cnt)
{
	while (s[*i] && !is_meta(s[*i]))
	{
		if (is_quote(s[*i]))
			adv_quoted(s, i, cnt);
		else
			adv_plain(s, i, cnt);
	}
}

int	ft_count_until_deli(char *s, int n, char delimiter, int count)
{
	if (!s)
		return (count);
	count++;
	n++;
	while (s[n] && s[n] != delimiter)
	{
		n++;
		count++;
	}
	if (s[n] == delimiter)
	{
		n++;
		count++;
	}
	advance_word(s, &n, &count);
	return (count);
}