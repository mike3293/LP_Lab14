#include "pch.h"
//#include <iostream>
//#include <locale>
//#include <cwchar>
//
//#include "Error.h"		//обработка ошибок
//#include "Parm.h"		//обработка параметров
//#include "Log.h"		//работа с протоколом
//#include "In.h"			//ввод исходного файла
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	setlocale(LC_ALL, "rus");
//	std::cout << " ----------тест In::getin    ---" << std::endl << std::endl;
//	try
//	{
//		Parm::PARM parm = Parm::getparm(argc, argv);
//		In::IN in = In::getin(parm.in, parm.out);
//		std::cout << in.text << std::endl;
//		std::cout << "Всего символов" << in.size <<std::endl;
//		std::cout << "Всего строк" << in.lines<<std::endl;
//		std::cout << "Всего пропущено" << in.ignor << std::endl;
//	}
//	catch (Error::ERROR e)
//	{
//		std::cout << "Ошибка " << e.id << ":" << e.message << std::endl << std::endl;
//	};
//
//	system("pause");
//	return 0;
//}