#pragma once
#define IN_MAX_LEN_TEXT 1024*1024 //���� ������ ��������� ���� 1MB
#define IN_CODE_ENDL '\0' // ������ ����� ������
//������� �������� ������� ����������, ������ = ���(Windows-1251) �������
// �������� IN::F - ����������� ������ IN::T-����������� ������ IN::I-������������(�� �������),
//		���� 0<= �������� < - �� ��������� ������ ��������
#define IN_CODE_TABLE {\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,  '|' , IN::T, IN::T, IN::I, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	's'  , IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, 's'  , 's'  , 's'  , 's'  , 's'  , 's'  , IN::F, 's'  , \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, 's'  , IN::T, 's'  , IN::T, IN::F, \
	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::T, \
	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, 's'  , IN::T, 's'  , IN::F, IN::F, \
	\
	IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
}
namespace In
{
	struct IN //�������� ������
	{
		enum { T = 1024, F = 2048, I = 4096, S = 512 }; //�-���������� ������ F- ������������  I- ������������ ����� ��������
		int size; //������ ��������� ����
		int lines; //���������� �����
		int ignor;// ���������� ����������������� �����
		unsigned char* text; //�������� �����
		int code[256]; // ������� ��������: T,F,I ����� ��������
	};
	IN getin(wchar_t infile[], wchar_t outfile[]);//������ � ��������� ������� ����� 
}

// " ,;(){}=+-*/|"