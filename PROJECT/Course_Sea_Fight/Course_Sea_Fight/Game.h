#pragma once
#include "stdafx.h"


//*********����� GAME**********
class Game
{
	bool new_generate_koordinat;	//��� ���������� ��������� ����� ���������
	int _x_;		//������  1 >< 10
	int _y_;		//������� A >< J
	bool alive_ship_on_which_the_last_hit;		//��� ����������� ����� ������� �� �������� ��� ��������� �������, 
												//����� ���������� ���������� �� �������� ����� �� ����� �������
public:
	Game() 
	{
		new_generate_koordinat = true;
		alive_ship_on_which_the_last_hit = false;
		_x_ = _y_ = 0;
	}
	~Game() {}
	//***************************
	//start battle time
	void timer_start_battle();
	//����� ������ ����������� � ����
	void designations_in_game();

	//******************����******************
	//����� ���� Player vs Player 
	void Player_vs_Player(Player player1OBJ, Player player2OBJ);
	//����� ���� COMP vs Player
	void COMP_vs_Player(Player compOBJ, Player playerOBJ);
	//����� ���� Player vs COMP
	void Player_vs_COMP(Player playerOBJ, Player compOBJ);
	//������ ����
	void start_game();

};
