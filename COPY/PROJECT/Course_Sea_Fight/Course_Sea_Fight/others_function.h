#pragma once
#include "stdafx.h"

//***************������� ����� � ����� ��� ����� ���������***************
int check_input_symb(char column);
//������� ��������� ������ ���� ����������� � �������
void MyColor(int text, int background);
//****************���� ���****************
//������� ������
void put_top_line(ostream& stream);
//���������� ������ 
void put_middle_line(ostream& stream);
//������ ������
void put_bottom_line(ostream& stream);
//����� ����
ostream& battlefield(ostream&stream, char arr[][COLUMNS], char *name);

