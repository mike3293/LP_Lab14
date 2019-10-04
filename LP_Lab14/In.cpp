#include "stdafx.h"

namespace In
{

	IN getin(wchar_t infile[], wchar_t outfile[])
	{
		int currentLine = 0, currentCol = 0;
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };					//uniform инициализация (альтернатива == списки инициализации)
		std::ifstream in(infile);									//открывает файл для чтения
		std::ofstream out(outfile);									//открывает файл для записи
		if (!out.is_open())											//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);
		if (!in.is_open())											//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);
		std::string fulltext;
		std::string temp;
		while (!in.eof())											//пока открыт файл
		{
			Info.lines++;											//считаем кол-во линий
			std::getline(in, temp);									//запись строки в tеmp
			temp += "\n";											//знак окончания строки
			fulltext += temp;
		}
		Info.text = new unsigned char[fulltext.size() + 1];			//выделяем память для текста
		unsigned char * Ptemp = Info.text;							//указатель на участок пямати
		for (int i = 0; i < fulltext.size(); ++i)
		{
			if (Info.code[(unsigned char)fulltext[i]] == IN::F) //Если запр символ => ошибка
			{
				throw ERROR_THROW_IN(111, currentLine, currentCol)
			}
			else if (Info.code[(unsigned char)fulltext[i]] == IN::I) // Если игнор символ 
				++Info.ignor;
			else if (Info.code[(unsigned char)fulltext[i]] == IN::T)// Если разрешенный символ 
			{
				*Ptemp = fulltext[i];
				++Ptemp;
			}
			else													//Если не указан символ ,  увелич счетчик игнор элем на 1
			{
				*Ptemp = Info.code[(unsigned char)fulltext[i]];
				++Ptemp;
			}
			if (fulltext[i] == '\n')								//если конец строки, увелич счетчик строки на 1 
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}
		*Ptemp = IN_CODE_ENDL;										//признак конца строки
		Info.size = strlen((char*)Info.text) ;			//количество символо = количество всех элем - \n
		unsigned char *str = new unsigned char[Info.size];
		//for (int i = 0,j = 0; i < Info.size + Info.lines; i++)
		//	if (Info.text[i] == '|')
		//	{
		//		
		//		str[j] = '\0';
		//		j = 0;
		//		FST::FST fst(
		//			str,
		//			8,
		//			/*0*/	FST::NODE(1, FST::RELATION('i', 1)),
		//			/*1*/	FST::NODE(4, FST::RELATION('w', 1), FST::RELATION('w', 2), FST::RELATION('w', 4), FST::RELATION('w', 5)),
		//			/*2*/	FST::NODE(3, FST::RELATION('a', 3), FST::RELATION('c', 3), FST::RELATION('C', 3)),
		//			/*3*/	FST::NODE(4, FST::RELATION('w', 5), FST::RELATION('w', 4), FST::RELATION('w', 3), FST::RELATION('w', 2)),
		//			/*4*/	FST::NODE(2, FST::RELATION('w', 4), FST::RELATION('w', 5)),
		//			/*5*/	FST::NODE(1, FST::RELATION('r', 6)),
		//			/*5*/	FST::NODE(1, FST::RELATION(';', 7)),
		//			FST::NODE()
		//		);
		//		
		//		if (execute(fst) == true)
		//			out << str << std::endl;
		//		else std::cout << str << " Ошибка разбора" << std::endl;
		//	}
		//	else if (Info.text[i] != '\n')
		//	{
		//		str[j] = Info.text[i];
		//		j++;
		//	}
		
		out.close();
		in.close();
		return Info;
	}
}