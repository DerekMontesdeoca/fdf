/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:45:31 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/14 00:38:25 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include "fdf.h"
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int		exit_code;
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_fprintf(STDERR_FILENO, "Usage: fdf FILE \n");
		return (EXIT_FAILURE);
	}
	fdf = (t_fdf){0};
	if (make_fdf(&fdf, argv[1]))
	{
		exit_code = EXIT_SUCCESS;
		mlx_loop(fdf.mlx);
	}
	else
		exit_code = EXIT_FAILURE;
	fdf_destroy_contents(&fdf);
	return (exit_code);
}
