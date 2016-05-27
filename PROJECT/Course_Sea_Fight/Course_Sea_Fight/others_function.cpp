#pragma once
#include "stdafx.h"

//***************������� ����� � ����� ��� ����� ���������***************
int check_input_symb(char column)
{
	int tmp;

	if (column == 'a' || column == 'A')
		tmp = 0;
	else if (column == 'b' || column == 'B')
		tmp = 1;
	else if (column == 'c' || column == 'C')
		tmp = 2;
	else if (column == 'd' || column == 'D')
		tmp = 3;
	else if (column == 'e' || column == 'E')
		tmp = 4;
	else if (column == 'f' || column == 'F')
		tmp = 5;
	else if (column == 'g' || column == 'G')
		tmp = 6;
	else if (column == 'h' || column == 'H')
		tmp = 7;
	else if (column == 'i' || column == 'I')
		tmp = 8;
	else if (column == 'j' || column == 'J')
		tmp = 9;

	//return tolower(column) - 'a';	//��� �������� �� ���� ������� ����
	return tmp;
}
//������� ��������� ������ ���� ����������� � �������
void MyColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//****************���� ���****************
//������� ������
void put_top_line(ostream& stream)
{
	stream << "\t\t  " << char(201);	//����� ������� ���� ����
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << char(205) << char(203);	//������
	}
	stream << char(205) << char(187) << endl;	//����� ������� ���� ���� 
}
//���������� ������ 
void put_middle_line(ostream& stream)
{
	stream << "\t\t  " << char(204);		//������ ������ ������
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << char(205) << char(206);	//������
	}
	stream << char(205) << char(185) << endl;	//��������� ������ ������ + �������
}
//������ ������
void put_bottom_line(ostream& stream)
{
	stream << "\t\t  " << char(200);	//������ ����� ����
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << char(205) << char(202);		//������
	}
	stream << char(205) << char(188) << endl;	//������ ������ ����
}
//����� ����
ostream& battlefield(ostream&stream, char arr[][COLUMNS], char *name)
{
	MyColor(Yellow, Black);
	stream << endl << endl;
	stream << "\t\t   A B C D E F G H I J " << endl;
	MyColor(LightCyan, Black);
	put_top_line(stream);				//����� ������� ������
	for (int i = 0; i < ROWS; i++)
	{
		MyColor(Yellow, Black);	//������ ����� � ����� �����
		stream << "\t\t" << setw(2) << i + 1;	//����� ������ ������
		MyColor(LightCyan, Black);			//���� ���� 
		for (int j = 0; j < COLUMNS; j++)
		{
			//��������� �������
			if (arr[i][j] == ship)
			{
				stream << char(186);			//���������� ����� ��������
				MyColor(LightGreen, Black);		//������ ���� �������
				stream << arr[i][j];			//��� �������
				MyColor(LightCyan, Black);		//���������� ���� ����
			}
			//��������� ��������� �� �������
			else if (arr[i][j] == hit)
			{
				stream << char(186);		//���������� ����� ���������
				MyColor(LightRed, Black);		//�������� ���� ����� ���������
				stream << arr[i][j];		//����� ����� ���������
				MyColor(LightCyan, Black);	//���������� ���� ����
			}
			//��������� �����
			else if (arr[i][j] == bomb)
			{
				stream << char(186);		//���������� ����� ���������
				MyColor(DarkGray, Black);	//����� - ����� ���� �����
				stream << arr[i][j];		//����� �����
				MyColor(LightCyan, Black);	//���������� ���� ����
			}
			//� ����� ������ ������
			else {
				MyColor(LightCyan, Black);			//���� ����
				stream << char(186) << arr[i][j];	//����� ���������� ����� + ������
			}
		}
		stream << char(186);	//���������� �����
								//����� ������
		if (i == 0)
		{
			MyColor(Magenta, Black);			//��������� ����
			stream << "\t\t" << name << endl;	//����� ����� ������
			MyColor(LightCyan, Black);			//���������� ���� ����
		}
		else
		{
			stream << endl;
		}
		if (i < 9)
			put_middle_line(stream);	//����� ����� ����� ������� � ������
	}
	put_bottom_line(stream);	//����� ������ ������

	return stream;
}

