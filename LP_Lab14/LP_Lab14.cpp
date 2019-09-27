#include "pch.h"

#include <iostream>
#include <locale>
#include <cwchar>

#include "Error.h"		//обработка ошибок
#include "Parm.h"		//обработка параметров
#include "Log.h"		//работа с протоколом
#include "In.h"			//ввод исходного файла
#include "Lex.h"

int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		LT::showTable(lex.lextable, log);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	return 0;
}