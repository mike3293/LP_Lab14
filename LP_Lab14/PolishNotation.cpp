#include "stdafx.h"
#include <queue>

using namespace std;
bool PolishNotation(int i, Lex::LEX& lex)
{
	stack<LT::Entry> stack;									
	
	queue<LT::Entry> queue;	

	int lineNum = lex.lextable.table[i].sn;
	LT::Entry temp;			// ������� ��� �����������
	temp.idxTI = INT_MIN;
	temp.lexema = '#';
	temp.sn = lineNum;

	LT::Entry funcParm;			// ������� ��� ������ �������
	funcParm.idxTI = INT_MIN;
	funcParm.lexema = '@';
	funcParm.sn = lineNum;
	int countLex = 0;															// ���������� ��������������� ������
	int countParm = 0;															// ���������� ���������� �������
	int posLex = i;																// ���������� ����� ������� ����� ���������������
	bool findFunc = false;														// ���� ��� �������
	bool findComma = false;														// ���� ��� ������� (���-�� ���������� +2 �����)
	char* buf = new char[2];													// ����� ��� countParm � ��������� �������������
	for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
		switch (lex.lextable.table[i].lexema)
		{
		case LEX_ID:			
		{
			if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F)
				findFunc = true;
			queue.push(lex.lextable.table[i]);
			continue;
		}
		case LEX_LITERAL:				
		{
			queue.push(lex.lextable.table[i]);										
			continue;
		}
		case LEX_LEFTTHESIS:	
		{
			stack.push(lex.lextable.table[i]);										// �������� � ����
			continue;
		}
		case LEX_RIGHTTHESIS:				
		{
			if (findFunc)															// ���� ��� ����� �������, �� ������� () ���������� �� @ � ���-�� ����������
			{
				if (findComma)
				{
					countParm++;
				}
				lex.lextable.table[i] = funcParm;
				queue.push(lex.lextable.table[i]);									// ��������� � ������� ������� ������ �������
				_itoa_s(countParm, buf, 2, 10);										// �������������� ����� countParm � ������
				stack.top().lexema = buf[0];
				stack.top().idxTI = INT_MIN;
				stack.top().sn = lineNum;						// ��������� �������, ����������� ���������� ���������� �������
				queue.push(stack.top());											// ��������� � ������� ��� �������
				findFunc = false;
			}
			else {
				while (stack.top().lexema != LEX_LEFTTHESIS)						// ���� �� �������� (
				{
					queue.push(stack.top());										// ����������� �� ����� � �������
					stack.pop();

					if (stack.empty())
						return false;
				}
			}
			stack.pop();															// ���������� ( ��� �������, ����������� ���������� ���������� �������
			continue;
		}
		case LEX_OPERATOR:															// ���� ���� ���������
		{
			while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority)	// ���� ��������� �������� ��������� 
																					//������ ��� ����� ���������� ��������� � ������� �����
			{
				queue.push(stack.top());											// ����������� �� ����� � �������� ������
				stack.pop();
			}
			stack.push(lex.lextable.table[i]);
			continue;
		}
		case LEX_COMMA:																// ���� �������
		{
			findComma = true;
			countParm++;
			continue;
		}
		}
	}
	while (!stack.empty())															// ���� ���� �� ������
	{
		if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
			return false;
		queue.push(stack.top());													// ����������� ��� � �������
		stack.pop();
	}
	while (countLex != 0)															// ������ �������� ��������� � ������� ������ �� �������� ������
	{
		if (!queue.empty()) {
			lex.lextable.table[posLex++] = queue.front();	
			queue.pop();
		}
		else
		{
			lex.lextable.table[posLex++] = temp;
		}
		countLex--;
	}
	for (int i = 0; i < posLex; i++)												// �������������� �������� ������� ��������� � ������� ������ � ���������� �� ������� ���������������
	{
		if (lex.lextable.table[i].lexema == LEX_OPERATOR || lex.lextable.table[i].lexema == LEX_LITERAL)
			lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}