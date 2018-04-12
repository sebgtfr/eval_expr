/**
* \file			    main.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				12 Avril 2018
*/

#include "eval_expr.h"
#include <stdio.h>

int								main(int ac, char **av)
{
	t_eval_expr_status			status;
	double						res;

	if (ac == 2)
	{
		if ((status = eval_expr(av[1], &res)) == EVAL_EXPR_SUCCESS)
		{
			(void)printf("%s = %0.2f\n", av[1], res);
			return 0;
		}
		else
		{
			char const * const	errors[EVAL_EXPR_SUCCESS] =
			{
				"Parenthesis not close !",
				"Division by 0",
				"Modulo by 0",
				"Expression invalid !",
				"Number invalid !"
			};

			(void)fprintf(stderr, "Error: %s\n", errors[status]);
		}
	}
	else
		(void)fprintf(stderr, "Error: %s [expr]\n", av[0]);
	return 1;
}
