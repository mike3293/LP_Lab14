#include "pch.h"

#define DIV '|'
#define SPACE ' '
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'
#define EQUAL '='

using namespace std;

namespace Lex
{
	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);
		clearSpace(in.text, in.size);

		unsigned char** word = new unsigned char*[max_world];
		for (int i = 0; i < max_world; i++)
			word[i] = new unsigned char[size_world] {NULL};

		do {
			word = divideText(in.text, in.size);
		} while (word == NULL);

		int indxLex = 0;		// индекс лексемы
		int indexID = 0;		// индекс идент.
		int clit = 1;			// счетчик литералов
		int line = 1;			// номер строки
		int position = 0;			// номер позиции в исходном файле

		unsigned char emptystr[] = "";	// пустая строка
		unsigned char* prefix = new unsigned char[10]{ "" };	// текущий префикс
		unsigned char* bufprefix = new unsigned char[10]{ "" };	// буфер для префикса
		unsigned char* oldprefix = new unsigned char[10]{ "" };	// предыдущий префикс
		unsigned char* L = new unsigned char[2]{ "L" };
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[10]{ "" };
		char* charclit = new char[10]{ "" };		// для строковой записи счетчика

		bool findFunc = false;
		bool findParm = false;
		IT::Entry entryIT;

		for (int i = 0; word[i] != NULL; i++, indxLex++)
		{

			bool findSameID = false;

			FST::FST fstDeclare(word[i], FST_DECLARE);
			if (FST::execute(fstDeclare))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_DECLARE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstTypeInteger(word[i], FST_INTEGER);
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_INTEGER, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::INT;
				continue;
			}
			FST::FST fstTypeString(word[i], FST_STRING);
			if (FST::execute(fstTypeString))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_STRING, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::STR;
				_mbscpy(entryIT.value.vstr.str, emptystr);
				continue;
			}
			FST::FST fstFunction(word[i], FST_FUNCTION);
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::F;
				findFunc = true;
				continue;
			}
			FST::FST fstReturn(word[i], FST_RETURN);
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RETURN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstPrint(word[i], FST_PRINT);
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_PRINT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			/*FST::FST fstMain(word[i], FST_MAIN);
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				_mbscpy(oldprefix, prefix);
				_mbscpy(prefix, word[i]);
				_mbscpy(entryIT.visibility, emptystr);
				continue;
			}*/
			position += _mbslen(word[i]);
			if (word[i][0] == DIV) {
				line++;
				position = 0;
				indxLex--;
				continue;
			}
		}
		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}
}