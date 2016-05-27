#pragma once
#include "stdafx.h"
#include "defines.h"

//*****����� �������*****
class SHIP
{
public:
	//���������� �������
	int x_begin;	//���������� ������ ������� �� ������
	int y_begin;	//���������� ������ ������� �� �������
	int x_end;		//���������� ����� ������� �� �������
	int y_end;		//���������� ����� ������� �� �������

	bool alive;	//��������� �������
	int num_deck_ship;	//���������� �����
	char *new_ship;		//��� �������� �������
	direction dir_n;	//��������� �������
	int num_shot;			//���������� ��������� �� �������

	SHIP() {}
	SHIP(int _x_begin, int _y_begin, int _x_end, int _y_end, int _deck, bool _is_dead, direction _dir_on)
	{
		x_begin = _x_begin;
		y_begin = _y_begin;
		x_end = _x_end;
		y_end = _y_end;
		num_deck_ship = _deck;
		alive = true;
		new_ship = new char[_deck];
		dir_n = _dir_on;
		num_shot = 0;
		for (int i = 0; i < _deck; i++)
			new_ship[i] = ship;
	}
	~SHIP() {}
	//������� ���� �������
	void dead_zone_the_ship(char arr[][COLUMNS], bool _is_dead, direction dir_n);
};