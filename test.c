/**
* \file			    test.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				12 Avril 2018
*/

#include "eval_expr.h"
#include <stdio.h>

static void						printExpr(char const * expr,
										  double const c,
										  double const e)
{
	(void)printf("%s =\nC : %.2f\nE : %.2f\n\n", expr, c, e);
}

int								main(void)
{
	char const					*expr;
	double						res;

	(void)printf("----- TEST EVAL -----\n");

	(void)printf("-----> SOMMES :\n");

	expr = "5 + 5";
	eval_expr(expr, &res);
	printExpr(expr, 5 + 5, res);

	expr = "16-5";
	eval_expr(expr, &res);
	printExpr(expr, 16-5, res);

	expr = "16- (-5)";
	eval_expr(expr, &res);
	printExpr(expr, 16- (-5), res);

	(void)printf("-----> PRODUITS :\n");

	expr = "5 * 5";
	eval_expr(expr, &res);
	printExpr(expr, 5 * 5, res);

	expr = "64/8";
	eval_expr(expr, &res);
	printExpr(expr, 64/8, res);

	expr = "10 + 9 * 10";
	eval_expr(expr, &res);
	printExpr(expr, 10 + 9 * 10, res);

	(void)printf("-----> DECIMAL :\n");

	expr = "22 / 7";
	eval_expr(expr, &res);
	printExpr(expr, 22.0d / 7, res);

	expr = "2.5*4";
	eval_expr(expr, &res);
	printExpr(expr, 2.5d*4, res);

	expr = "5 + 5.5 * 10";
	eval_expr(expr, &res);
	printExpr(expr, 5 + 5.5d * 10, res);

	(void)printf("-----> COMPLEXE :\n");

	expr = "(2 + 3) * (15 - 20 / 2)";
	eval_expr(expr, &res);
	printExpr(expr, (2 + 3) * (15 - 20 / 2), res);

	expr = "(8 * (5 - 13)) + 25";
	eval_expr(expr, &res);
	printExpr(expr, (8 * (5 - 13)) + 25, res);

	expr = "(((14 + 6) / (12 - 32) + 1) + 25 * 4)";
	eval_expr(expr, &res);
	printExpr(expr, (((14 + 6) / (12 - 32) + 1) + 25 * 4), res);

	return 0;
}
