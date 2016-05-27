#pragma once
#include "stdafx.h"

//*********��������*********
//�������� ��� ������ ��������� ��������� ������� 
class PREDICAT_downed_ship
{
	int x;		//������
	int y;		//�������
public:
	PREDICAT_downed_ship(int _x, int _y) : x(_x), y(_y) {}

	bool operator()(SHIP obj)
	{
		//���� ��������� ������� ������������
		if (obj.dir_n == VERTICAL)
		{
			//�������� ��������� ������� ����� ����� ������� � ������ �������
			return ((x >= obj.x_begin && y == obj.y_begin) && (x <= obj.x_end && y == obj.y_end));
		}
		//���� ��������� ������� ��������������
		else if (obj.dir_n == HORIZONTAL)
		{
			//�������� ��������� ������� ����� ����� ������� � ������ �������
			return ((x == obj.x_begin && y >= obj.y_begin) && (x == obj.x_end && y <= obj.y_end));
		}
	}
};
