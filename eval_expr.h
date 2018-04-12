/**
* \file			    eval_expr.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				12 Avril 2018
*/

#ifndef EVAL_EXPR_H_
# define EVAL_EXPR_H_

typedef enum					e_eval_expr_status
{
								EVAL_EXPR_PARENTHESIS = 0,
								EVAL_EXPR_DIVIDE_ZERO,
								EVAL_EXPR_MODULO_ZERO,
								EVAL_EXPR_INCORRECT,
								EVAL_EXPR_INVALID_NUMBER,
								EVAL_EXPR_SUCCESS,
}								t_eval_expr_status;


typedef enum					e_eval_expr_operator
{
								EVAL_EXPR_ADD = 0,
								EVAL_EXPR_SUB,
								EVAL_EXPR_MUL,
								EVAL_EXPR_DIV,
								EVAL_EXPR_MOD,
								EVAL_EXPR_NONE,
}								t_eval_expr_operator;

#endif /* !EVAL_EXPR_H_ */
