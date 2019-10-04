#include "stdafx.h"
int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
 		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"����", L" ��� ������", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in,parm.out);
		Log::WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);

		LT::showTable(lex.lextable,log);
		IT::showTable(lex.idtable);
		LT::Delete(lex.lextable);
		IT::Delete(lex.idtable);
		system("pause");
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	return 0;
}