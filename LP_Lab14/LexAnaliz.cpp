#include "stdafx.h"

#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define SLASH '/'
#define EQUAL '='

using namespace std;

namespace Lex
{
	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE); //�������� ������� ���� �������
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);//�������� ������� ���� �������

		unsigned char** word = new unsigned char*[MAX_WORDS]; //��������� ������ ��� ���������� ������
		for (int i = 0; i < MAX_WORDS; i++)
			word[i] = new unsigned char[WORD_SIZE] {NULL};
		
		word = divideText(in); //���������� �� ������� 


		int indexLex = 0;		// ������ �������
		int indexID = 0;		// ������ �����.
		int countLit = 1;		// ������� ���������
		int line = 1;			// ����� ������
		int position = 0;		// ����� ������� � �������� �����

		unsigned char emptystr[] = "";	// ������ ������
		unsigned char* regionPrefix = new unsigned char[10]{ "" };	// ������� �������
		unsigned char* bufRegionPrefix = new unsigned char[10]{ "" };	// ����� ��� ��������
		unsigned char* oldRegionPrefix = new unsigned char[10]{ "" };	// ���������� �������
		unsigned char* L = new unsigned char[2]{ "L" };		// ��������� ������ ��� ��� ��������� + \0
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[TI_STR_MAXSIZE]{ "" };
		char* charCountLit = new char[10]{ "" };		// ��� ��������� ������ ��������
		unsigned char* startWord = new unsigned char[WORD_SIZE] {NULL}; //��� ������� ���������

		bool findFunc = false;
		bool findParm = false;
		IT::Entry entryIT; //�������� ������� ��� ��������� � ���� ��������������� 

		for (int i = 0; word[i] != NULL; i++, indexLex++) //������ �� ���� ��������
		{

			bool findSameID = false; 

			FST::FST fstDeclare(word[i], FST_DECLARE); // �������� �� �������� �����
			if (FST::execute(fstDeclare))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_DECLARE, LT_TI_NULLIDX, line); //�������� ���������
				LT::Add(lextable, entryLT); //���������� ��������� � �������
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstTypeInteger(word[i], FST_INTEGER);// �������� �� �������� �����
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_INTEGER, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::INT; //������ ���� �������������� � ���������
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstTypeString(word[i], FST_STRING);// �������� �� �������� �����
			if (FST::execute(fstTypeString))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_STRING, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::STR;			//������ ���� �������������� � ���������
				_mbscpy(entryIT.value.vstr.str, emptystr); //������� ������ ��� ������ ��������������
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstFunction(word[i], FST_FUNCTION);// �������� �� �������� �����
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.idtype = IT::F;
				findFunc = true; //��������� ����� �������
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstReturn(word[i], FST_RETURN);// �������� �� �������� �����
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RETURN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstPrint(word[i], FST_PRINT);// �������� �� �������� �����
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_PRINT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstMain(word[i], FST_MAIN);// �������� �� �������� �����
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				_mbscpy(oldRegionPrefix, regionPrefix);
				_mbscpy(regionPrefix, word[i]);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstIdentif(word[i], FST_ID); //�������� �� �������������
			if (FST::execute(fstIdentif))
			{
				FST::FST fstLibFunc(word[i], FST_LIBFUNC); //�������� �� substr � strlen

				if((_mbslen(word[i]) > 5) && !(FST::execute(fstLibFunc)))
					throw ERROR_THROW_IN(116, line, position);
				_mbscpy(startWord, word[i]);

				// ����� ������ ��
				if (findFunc)	// ���� �������
				{
					int idx = IT::IsIDRegion(idtable, word[i]);	// ���� ��� ��������
					if (idx != TI_NULLIDX)						// ���� ����� ������������� ��� ����
					{
						if (lextable.table[indexLex-1].lexema == LEX_FUNCTION)
							throw ERROR_THROW_IN(114, line, position);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						position += _mbslen(word[i]) + 1;
						continue;
					}
				}
				else
				{
					int idx = IT::IsIDRegion(idtable, word[i]);	
					if (idx != TI_NULLIDX)					
					{
						if (lextable.table[indexLex - 2].lexema == LEX_DECLARE)
							throw ERROR_THROW_IN(114, line, position);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						position += _mbslen(word[i]) + 1;
						continue;
					}
					_mbscpy(bufRegionPrefix, regionPrefix);
					word[i] = _mbscat(bufRegionPrefix, word[i]);
					idx = IT::IsIDRegion(idtable, word[i]);
					if (idx != TI_NULLIDX)		// ���� ����� ������������� ��� ����
					{
						if (lextable.table[indexLex - 2].lexema == LEX_DECLARE)
							throw ERROR_THROW_IN(114, line, position);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						position += _mbslen(word[i]) + 1;
						continue;
					}
				}
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ID, indexID++, line);
				LT::Add(lextable, entryLT);
				if (findParm)				// ���� ��������
				{
					entryIT.idtype = IT::P;
				}
				else if (!findFunc) 
				{
					// ���� ����������
					entryIT.idtype = IT::V;
					if (entryIT.iddatatype == IT::INT)
						entryIT.value.vint = TI_INT_DEFAULT;
					if (entryIT.iddatatype == IT::STR) {
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
					}
				}
				else {		// ���� �������
					_mbscpy(oldRegionPrefix, regionPrefix);
					_mbscpy(regionPrefix, word[i]);
				}

				entryIT.idxfirstLE = indexLex;
				_mbscpy(entryIT.id, startWord);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idtable, entryIT);
				findFunc = false;
				position += _mbslen(word[i]) + 1;
				continue;
			}

			FST::FST fstLiteralInt(word[i], FST_INTLIT); //���� ������� 
			if (FST::execute(fstLiteralInt))
			{
				int value = atoi((char*)word[i]);	// �������� ��������
				for (int k = 0; k < idtable.size; k++) // ����� ������ ��
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
			}
				if (findSameID)	// ���� ��� ������ ����� ��
				{
					position += _mbslen(word[i]) + 1;
					continue;
				}
					
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = indexLex;	//����� � ���� ������
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// ����������� �������� �������� � ������(charCountLit) 
				
				// ������������ ����� ��������
				_mbscpy(bufL, L);	// �������� � ����� "L"
				word[i] = _mbscat(bufL, (unsigned char*)charCountLit);	// ��������� ��� ��� ��������
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, emptystr);
				IT::Add(idtable, entryIT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstLiteralString(word[i], FST_STRLIT);
			if (FST::execute(fstLiteralString))
			{
				// ������ ��������
				int length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)	// ���������� �������, ������� �������
					word[i][k] = word[i][k + 1];

				word[i][length - 2] = '\0';

					
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				_mbscpy(entryIT.value.vstr.str, word[i]);	// ������ �������� ���������� ��������
				entryIT.value.vstr.len = length - 2;		// ������ ����� ���������� ��������
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STR;
				entryIT.idxfirstLE = indexLex;
				// ������������ ����� ��������
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// ����������� �������� �������� � ������(charCountLit)
				_mbscpy(bufL, L);	// �������� � ����� "L"
				nameLiteral = _mbscat(bufL, (unsigned char*)charCountLit);	// ��������� ��� ��� �������� (L + charCountLit)
				_mbscpy(entryIT.id, nameLiteral);
				_mbscpy(entryIT.idRegion, emptystr);
				IT::Add(idtable, entryIT);
				position += _mbslen(word[i]) + 1;
				continue;
			}

			FST::FST fstOperator(word[i], FST_OPERATOR);
			if (FST::execute(fstOperator))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_OPERATOR, indexID++, line);
				switch (word[i][0])
				{
				case PLUS: case MINUS:
					entryLT.priority = 2;
					break;
				case SLASH: case STAR:
					entryLT.priority = 3;
					break;
				}
				LT::Add(lextable, entryLT);
				_mbscpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indexLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lextable, entryLT);
				if (idtable.table[indexID - 1].idtype == IT::F)
					findParm = true;
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;

				if (findParm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE && !checkBrace(word, i + 1))		// ���� ����� ������� ��� {
					_mbscpy(regionPrefix, oldRegionPrefix);		// ���������� ���������� ���. ���������
				findParm = false;
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				position += _mbslen(word[i]) + 1;
				continue;
			}
			position += _mbslen(word[i]) + 1;
			if (word[i][0] == DIV) {
				line++;
				position = 0;
				indexLex--;
				continue;
			}
			throw ERROR_THROW_IN(115, line, position);
		}
		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}

	bool checkBrace(unsigned char** word, int k)
	{
		while (word[k][0] == DIV)
		{
			k++;
		}
		if (word[k][0] == LEX_LEFTBRACE)
			return 1;
		else
			return 0;
	}
}