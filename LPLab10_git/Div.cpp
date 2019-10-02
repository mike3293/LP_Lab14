#include "stdafx.h"
#include "Div.h"

unsigned char** divideText(unsigned char text[], int size)		// формирование массива строк, состоящего из лексем
{
	unsigned char** word = new unsigned char*[max_world]; //выделение памяти для разделения лексем
	for (int i = 0; i < max_world; i++)
		word[i] = new unsigned char[size_world] {NULL};

	bool findSP, findLit = false; //флаги сепараторов и литералов
	int j = 0;
	char SP[] = { " ,;(){}=+-*/\n" }; //массив сепараторов
	for (int i = 0, k = 0; i < size - 1; i++, k++) //проход текста
	{
		findSP = false;
		if (text[i] == '\'') //если найден литерал
			findLit = !findLit;
		for (int t = 0; t < sizeof(SP) - 1; t++) //проверка на сепаратор
		{
			if ((text[i] == SP[t] ) && !findLit) //проверка на сепаратор
			{
				findSP = true;				  
				if (word[j][0] != NULL)
				{
					word[j++][k] = '\0'; //признак завершенности слова
					k = 0;
				}
				if (SP[t] == ' ') //если пробел - пропускаем
				{
					k = -1;
					break;
				}
				word[j][k++] = SP[t]; //запись сепаратора
				word[j++][k] = '\0'; //признак завершения разбора лексемы
				k = -1;
				break;
			}
		}
		if (!findSP)		//если не сепаратор
			word[j][k] = text[i];		//переписывем
	}
	word[j] = NULL;
	//for (int i = 0; i < j; i++) //проверка
	//{
	//	if (!strcmp((char*)word[i], ""))
	//		return NULL;
	//	std::cout << i << ">"<< word[i] << " ";
	//}
	return word;
}

