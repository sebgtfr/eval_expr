/**
* \file			    eval_expr.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				12 Avril 2018
*/

#include <stdint.h>
#include <stdlib.h>
#include "eval_expr.h"

static t_eval_expr_status		operation(char const **expr,
										  double *res,
										  unsigned char const parenthesis);

static unsigned char			isOperator(char const expr)
{
	return (expr == '+' || expr == '-' || expr == '*' || expr == '/');
}

static void						delete_space(char const **expr)
{
	while (**expr && (**expr == ' ' || **expr == '\t'))
		++(*expr);
}

static t_eval_expr_status		calc(double const left, double const right,
									 double *res, t_eval_expr_operator const op)
{
	t_eval_expr_status			status = EVAL_EXPR_SUCCESS;

	switch (op)
	{
	case EVAL_EXPR_ADD:
		*res = left + right;
		break;
	case EVAL_EXPR_SUB:
		*res = left - right;
		break;
	case EVAL_EXPR_MUL:
		*res = left * right;
		break;
	case EVAL_EXPR_DIV:
		if (right)
			*res = left / right;
		else
			status = EVAL_EXPR_DIVIDE_ZERO;
		break;
	case EVAL_EXPR_MOD:
		if (right != 0.0d)
			*res = ((uint64_t)left) % ((uint64_t)right);
		else
			status = EVAL_EXPR_MODULO_ZERO;
		break;
	default:
		status = EVAL_EXPR_INCORRECT;
		break;
	}
	return status;
}

static t_eval_expr_status		number(char const **expr, double *num)
{
	t_eval_expr_status			status = EVAL_EXPR_SUCCESS;

	delete_space(expr);
	if (**expr)
	{
		*num = strtod(*expr, (char **)expr);
		if (**expr == '(')
		{
			if (*num == 0.0d)
			{
				++(*expr);
				status = operation(expr, num, 1);
			}
		}
		else if (!(!**expr || isOperator(**expr) || **expr == ' ' ||
				   **expr == '\t' || **expr == ')'))
			status = EVAL_EXPR_INVALID_NUMBER;
	}
	return status;
}

static t_eval_expr_status		product(char const **expr,
										double *res)
{
	double						leftOperand = 0;
	double						rightOperand = 0;
	t_eval_expr_operator		op = EVAL_EXPR_MUL;
	t_eval_expr_status			status = EVAL_EXPR_SUCCESS;

	if ((status = number(expr, &leftOperand)) == EVAL_EXPR_SUCCESS)
	{
		delete_space(expr);
		switch (**expr)
		{
		case '*':
		case '/':
			if (**expr == '/')
				op = EVAL_EXPR_DIV;
		case '%':
			if (**expr == '%')
				op = EVAL_EXPR_MOD;
			++(*expr);
			delete_space(expr);
			status = (isOperator(**expr)) ? EVAL_EXPR_INCORRECT : product(expr, &rightOperand);
			break;
		case '(':
			status = EVAL_EXPR_INCORRECT;
			break;
		case '+':
		case '-':
		case ')':
		case '\0':
			rightOperand = 1.0d;
			break;
		default:
			status = EVAL_EXPR_INCORRECT;
			break;
		}
		if (status == EVAL_EXPR_SUCCESS)
		{
			if (rightOperand != 1.0d || op == EVAL_EXPR_MOD)
				status = calc(leftOperand, rightOperand, res, op);
			else
				*res = leftOperand;
		}
	}
	return status;
}

static t_eval_expr_status		sum(char const **expr,
									double *res)
{
	double						leftOperand = 0;
	double						rightOperand = 0;
	t_eval_expr_operator		op = EVAL_EXPR_ADD;
	t_eval_expr_status			status = EVAL_EXPR_SUCCESS;

	if ((status = product(expr, &leftOperand)) == EVAL_EXPR_SUCCESS)
	{
		switch (**expr)
		{
		case '-':
			op = EVAL_EXPR_SUB;
		case '+':
			++(*expr);
			delete_space(expr);
			status = (isOperator(**expr)) ? EVAL_EXPR_INCORRECT : sum(expr, &rightOperand);
			if (status == EVAL_EXPR_SUCCESS)
				status = calc(leftOperand, rightOperand, res, op);
			break;
		default:
			*res = leftOperand;
			break;
		}
	}
	return status;
}

static t_eval_expr_status		operation(char const **expr,
										  double *res,
										  unsigned char const parenthesis)
{
	double						operand = 0;
	t_eval_expr_status			status = EVAL_EXPR_SUCCESS;

	delete_space(expr);
	switch (**expr)
	{
	case '\0':
		break;
	default:
		if (((status = sum(expr, res)) == EVAL_EXPR_SUCCESS) && **expr == '(')
		{
			++(*expr);
			status = operation(expr, &operand, 1);
		}
		break;
	}
	if (parenthesis)
	{
		if (**expr == ')')
			++(*expr);
		else
			status = EVAL_EXPR_PARENTHESIS;
	}
	*res += operand;
	return status;
}


t_eval_expr_status				eval_expr(char const *expr, double *res)
{
	*res = 0;
	return operation(&expr, res, 0);
}
