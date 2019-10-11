#include "stdafx.h"

unsigned char** divideText(In::IN in)		// ������������ ������� �����, ���������� �� ������
{
	int size = in.size;
	unsigned char* text = in.text;
	unsigned char** word = new unsigned char*[MAX_WORDS]; //��������� ������ ��� ���������� ������
	for (int i = 0; i < MAX_WORDS; i++)
		word[i] = new unsigned char[WORD_SIZE] {NULL};

	bool findSP, findLit = false; //����� ����������� � ���������
	int j = 0;

	for (int i = 0, k = 0; i < size - 1; i++, k++) //������ ������
	{
		findSP = false;
		if (text[i] == '\'') //���� ������ �������
			findLit = !findLit;

			if (((in.code[(unsigned char)text[i]] == In::IN::S) || (text[i] == DIV)) && !findLit) //�������� �� ���������
			{
				findSP = true;				  
				if (word[j][0] != NULL)
				{
					word[j++][k] = IN_CODE_ENDL; //������� ������������� �����
					k = 0;
				}
				if (text[i] == ' ') //���� ������ - ����������
				{
					k = -1;
					continue;
				}
				word[j][k++] = text[i]; //������ ����������
				word[j++][k] = IN_CODE_ENDL; //������� ���������� ������� �������
				k = -1;
			}
		//}
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

