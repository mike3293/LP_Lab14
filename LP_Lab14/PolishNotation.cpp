#include "stdafx.h"
#include <stack>
#include <queue>

using namespace std;

bool PolishNotation(int i, Lex::LEX& lex)
{
	stack<LT::Entry> stack;		
	queue<LT::Entry> queue;		
	LT::Entry temp;				// лексема для подстановки
	temp.idxTI = INT_MIN;
	temp.lexema = '#';
	temp.sn = lex.lextable.table[i].sn;

	int countLex = 0;			// количество преобразованных лексем
	int posLex = i;				// запоминаем номер лексемы перед преобразованием

	for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
		switch (lex.lextable.table[i].lexema)
		{
		case LEX_ID:
		{
			queue.push(lex.lextable.table[i]);
			continue;
		}
		case LEX_LITERAL:		
		{
			queue.push(lex.lextable.table[i]);	// помещаем в очередь
			continue;
		}
		case LEX_LEFTTHESIS:		
		{
			stack.push(lex.lextable.table[i]); // помещаем ее в стек
			continue;
		}
		case LEX_RIGHTTHESIS:	
		{
			while (stack.top().lexema != LEX_LEFTTHESIS)
			{
				queue.push(stack.top());	// выталкиваем со стека в очередь
				stack.pop();

				if (stack.empty())
					return false;
			}
			stack.pop();	// удаляем (
			continue;
		}
		case LEX_OPERATOR:
		{
			while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority)	// пока приоритет текущего оператора 
																								//меньше или равен приоритету оператора в вершине стека
			{
				queue.push(stack.top());	// выталкиваем со стека в выходную строку
				stack.pop();
			}
			stack.push(lex.lextable.table[i]);
			continue;
		}
		}
	}
	while (!stack.empty())	// если стек не пустой
	{
		if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
			return false;
		queue.push(stack.top());	// выталкиваем все в очередь
		stack.pop();
	}
	while (countLex != 0)		// замена текущего выражения в таблице лексем на выражение в polish notation
	{
		if (!queue.empty()) {
			lex.lextable.table[posLex++] = queue.front();

			cout << lex.idtable.table[queue.front().idxTI].id;

			queue.pop();
		}
		else
		{
			lex.lextable.table[posLex++] = temp;			// заменяем скобки
		}
		countLex--;
	}

	for (int i = 0; i < posLex; i++)		// восстановление индексов IT
	{
		if (lex.lextable.table[i].lexema == LEX_OPERATOR || lex.lextable.table[i].lexema == LEX_LITERAL)
			lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}