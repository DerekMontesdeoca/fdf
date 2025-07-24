/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_format_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:30:41 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/13 13:53:45 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include <libft/libft.h>

static int	parse_positive_int(const char *str, int *n);

/*
 * If specifier is invalid, returns false and sets specifier on token_meta to -1
 */
bool	parser_parse_conversion_specifier(t_parser *p)
{
	static const char	specifier_list[] = "cspdiuxX%";
	const char			*found;
	char				specifier;

	specifier = -1;
	found = NULL;
	if (p->format[p->index] != '\0')
		found = ft_strchr(specifier_list, p->format[p->index]);
	if (found != NULL)
	{
		specifier = *found;
		++p->index;
	}
	p->token_meta.specifier = specifier;
	return (found != NULL);
}

/*
 * Returns:
 * 	n if width set on format
 * 	FLAG_NOT_SET if not set
 * 	PARAM_ASTERISK if * param
 */
void	parser_parse_precision(t_parser *p)
{
	int	precision;

	precision = FLAG_NOT_SET;
	if (p->format[p->index] == '.')
	{
		++p->index;
		if (p->format[p->index] == '*')
		{
			precision = PARAM_ASTERISK;
			++p->index;
		}
		else
			p->index += parse_positive_int(p->format + p->index, &precision);
	}
	p->token_meta.precision = precision;
}

/*
 * Sets width to:
 * 	+n if width set on format
 * 	 0 if not set or set to 0 on format
 * 	 PARAM_ASTERISK if * param;
 */
void	parser_parse_width(t_parser *p)
{
	int	width;

	width = 0;
	if (p->format[p->index] == '*')
	{
		width = PARAM_ASTERISK;
		++p->index;
	}
	else
		p->index += parse_positive_int(p->format + p->index, &width);
	p->token_meta.width = width;
}

void	parser_parse_flags(t_parser *p)
{
	static const char	flag_list[] = "-+0# ";
	int					flags;
	char				*found;

	flags = 0;
	found = NULL;
	if (p->format[p->index] != '\0')
		found = ft_strchr(flag_list, p->format[p->index]);
	while (found != NULL)
	{
		flags |= 1 << (found - flag_list);
		++p->index;
		found = ft_strchr(flag_list, p->format[p->index]);
	}
	p->token_meta.flags = flags;
}

/*
 * Returns the amount of chars consumed.
 */
static int	parse_positive_int(const char *str, int *n)
{
	int	i;

	*n = 0;
	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		*n *= 10;
		*n += (str[i] - '0');
		++i;
	}
	return (i);
}
