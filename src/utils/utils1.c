int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
	{
		return (1);
	}
	return (0);
}

int	is_blank_line(const char *s)
{
	int	i;

	if (!s || !*s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (!ft_isspace((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}
