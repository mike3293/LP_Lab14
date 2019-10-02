#include "stdafx.h"
#include "Div.h"

unsigned char** divideText(unsigned char text[], int size)		// ������������ ������� �����, ���������� �� ������
{
	unsigned char** word = new unsigned char*[max_world]; //��������� ������ ��� ���������� ������
	for (int i = 0; i < max_world; i++)
		word[i] = new unsigned char[size_world] {NULL};

	bool findSP, findLit = false; //����� ����������� � ���������
	int j = 0;
	char SP[] = { " ,;(){}=+-*/\n" }; //������ �����������
	for (int i = 0, k = 0; i < size - 1; i++, k++) //������ ������
	{
		findSP = false;
		if (text[i] == '\'') //���� ������ �������
			findLit = !findLit;
		for (int t = 0; t < sizeof(SP) - 1; t++) //�������� �� ���������
		{
			if ((text[i] == SP[t] ) && !findLit) //�������� �� ���������
			{
				findSP = true;				  
				if (word[j][0] != NULL)
				{
					word[j++][k] = '\0'; //������� ������������� �����
					k = 0;
				}
				if (SP[t] == ' ') //���� ������ - ����������
				{
					k = -1;
					break;
				}
				word[j][k++] = SP[t]; //������ ����������
				word[j++][k] = '\0'; //������� ���������� ������� �������
				k = -1;
				break;
			}
		}
		if (!findSP)		//���� �� ���������
			word[j][k] = text[i];		//�����������
	}
	word[j] = NULL;
	//for (int i = 0; i < j; i++) //��������
	//{
	//	if (!strcmp((char*)word[i], ""))
	//		return NULL;
	//	std::cout << i << ">"<< word[i] << " ";
	//}
	return word;
}

