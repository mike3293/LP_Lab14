#include "pch.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include <fstream>
#include <string>
#include <iostream>
#include <experimental/filesystem>

//#define GRAPH_INTEGER 8, \
//	FST::NODE(1,FST::RELATION('i',1)), \
//	FST::NODE(1,FST::RELATION('n',2)), \
//	FST::NODE(1,FST::RELATION('t',3)), \
//	FST::NODE(1,FST::RELATION('e',4)), \
//	FST::NODE(1,FST::RELATION('g',5)), \
//	FST::NODE(1,FST::RELATION('e',6)), \
//	FST::NODE(1,FST::RELATION('r',7)), \
//	FST::NODE()
//
//#define GRAPH_FUNCTION 9, \
//	FST::NODE(1,FST::RELATION('f',1)), \
//	FST::NODE(1,FST::RELATION('u',2)), \
//	FST::NODE(1,FST::RELATION('n',3)), \
//	FST::NODE(1,FST::RELATION('c',4)), \
//	FST::NODE(1,FST::RELATION('t',5)), \
//	FST::NODE(1,FST::RELATION('i',6)), \
//	FST::NODE(1,FST::RELATION('o',7)), \
//	FST::NODE(1,FST::RELATION('n',8)), \
//	FST::NODE()
//
//bool isFunction(char* str)
//{
//	FST::FST function(str, GRAPH_FUNCTION);
//	return FST::execute(function);
//};

namespace In
{

	IN getin(wchar_t infile[], wchar_t outfile[])
	{
		int currentLine = 0, currentCol = 0;
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };					//uniform инициализация (альтернатива == списки инициализации)
		std::ifstream in(infile);									//открывает файл для чтения
		std::ofstream del(outfile, std::ios::trunc);
		del.close();
		std::fstream out(outfile);									//открывает файл для записи
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
		Info.size = strlen((char*)Info.text) - Info.lines;			//количество символо = количество всех элем - \n
		out << Info.text;
		out.seekg(0);
		currentLine = 0;




		
/*

		int wordP = 0;
		for (; std::getline(out, temp);)
		{
			for (int i = 0; i < temp.length(); i++)
			{
				if (temp[i] == 32)
					continue;

				for (wordP = i; temp[wordP] != 32; wordP++)
				{ }

				std::string word = temp.substr(i, wordP - i);
				i = wordP;
				FST::FST integer((char*)word.c_str(), GRAPH_INTEGER);
				
				if (FST::execute(integer))
				{
					std::cout << "int";
				}

			}
		}*/
		//std::string t_out;

		//for (; std::getline(out, temp) ;)
		//{
		//	if (temp[temp.length()-1] == '|')
		//	{
		//		FST::FST fst2(
		//			(char *)temp.c_str(),
		//			14,
		//			FST::NODE(1, FST::RELATION('i', 1)),
		//			FST::NODE(1, FST::RELATION('f', 2)),
		//			FST::NODE(4, FST::RELATION(' ', 2), FST::RELATION(' ', 3), FST::RELATION(' ', 5), FST::RELATION(' ', 6)),
		//			FST::NODE(3, FST::RELATION('c', 4), FST::RELATION('o', 4), FST::RELATION('n', 4)),
		//			FST::NODE(4, FST::RELATION(' ', 4), FST::RELATION(' ', 5), FST::RELATION(' ', 3), FST::RELATION(' ', 6)),
		//			FST::NODE(2, FST::RELATION(' ', 5), FST::RELATION(' ', 6)),
		//			FST::NODE(1, FST::RELATION('r', 7)),
		//			FST::NODE(1, FST::RELATION('e', 8)),
		//			FST::NODE(1, FST::RELATION('t', 9)),
		//			FST::NODE(1, FST::RELATION('u', 10)),
		//			FST::NODE(1, FST::RELATION('r', 11)),
		//			FST::NODE(1, FST::RELATION('n', 12)),
		//			FST::NODE(1, FST::RELATION('|', 13)),
		//			FST::NODE()
		//		);
		//		if (FST::execute(fst2))
		//		{
		//			temp[temp.length() - 1] = ' ';
		//			t_out += "цепочка ";
		//			t_out += temp;
		//			t_out += "распознана\n";
		//			//std::cout << "Цепочка " << temp << " распознана" << std::endl;
		//		}
		//		else throw ERROR_THROW_IN(113, currentLine, -1);
		//		++currentLine;
		//	}
		//}
		//out.close();
		//std::ofstream del2(outfile, std::ios::trunc);
		//del2 << t_out;
		//del2.close();
		return Info;
	}
}