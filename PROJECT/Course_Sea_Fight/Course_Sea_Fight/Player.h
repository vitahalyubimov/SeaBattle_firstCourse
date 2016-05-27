#pragma once
#include "stdafx.h"
using namespace std;

class Game;		//���������� ��������� ������ Game ��� �������������� ������� ������ Game � ������ Player

//******����� Player******
class Player
{
	//protected:
	char battle_field_arr[10][10];		//arr - ��������� ������������ ������ ��� ���� ��� 
	char hiden_sea_battle[10][10];		//������� ���� ��� �� ������� ��������� �������
	string name;						//���
	int num_ship;						//����� ���������� ��������
	vector<SHIP> ships;					//�������� ���� ��������
public:
	Player() {}
	Player(string name)
	{
		//���������� ����
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				hiden_sea_battle[i][j] = tag_sea;
				battle_field_arr[i][j] = tag_sea;
			}
		}
		this->name = name;
		num_ship = 0;
	}
	~Player() {}

	//**********������**********
	//����� �������� ���� ��� 
	void show_sea_battle_hidden_player();
	//**********����������� ��������**********
	//*****RAND*****
	//��� ��������� ������ �������
	vector<SHIP> set_ship_rand(int size_deck);
	//��������� �������� �� ������� ������� + 1 ������
	bool inspection_of_the_ship_at_the_touch(int x, int y, direction dir, int size_deck);
	//���������� ��� �������
	void all_set_ships_rand();
	//*****MANUALLY*****
	//��������� ���� �������
	vector<SHIP> set_ship_manually(int size_deck);
	//������ ����������� ���� �������� ��������
	void all_set_ships_manually();

	//������������� �����
	friend class Game;
	
	//******************���������� �����/������******************
	friend ostream& operator << (ostream&stream, Player& obj);
	friend istream& operator >> (istream&stream, Player& obj);
};

