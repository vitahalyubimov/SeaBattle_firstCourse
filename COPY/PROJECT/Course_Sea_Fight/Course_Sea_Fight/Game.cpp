#include "stdafx.h"

//******************������ ����******************
//����� ���� Player1 vs Player2
void Game::Player_vs_Player(Player player1OBJ, Player player2OBJ)
{
	system("cls");
	//����� �������� ���� ��� � ��������� �����
	player1OBJ.show_sea_battle_hidden_player();
	//����� ���� ��� ����
	cout << player2OBJ << endl;
	//���������� ��� ���
	cout << "Goes " << player1OBJ.name << endl;
	cout << "Enter koordinat A1 > J10: ";

	int row = 0;
	char column = ' ';

	//�������� �� ������� ��������
	if (player1OBJ.num_ship == 0)
	{
		system("cls");			//������� ������
		MyColor(LightRed, Black);		//������� ����
		cout << player1OBJ.name << ", LOSE!!! " << endl;	//� ��� �� �������� ��������, �� ���������
		MyColor(LightCyan, Black);			//������ - ��������� ����
		cout << endl << endl << "Press any key to continue " << endl;		//������ ����� ������� ��� �����������
		Sleep(4000);			//�������� 4 ���
		start_game();			//������ ����� ����
	}else if (player1OBJ.num_ship > 0)
	{
		//�������� �� ���� ���������
		do
		{
			//���� �� ����� ������ ������, ���� ����� �����������
			do
			{
				cin >> column;		//������ ����� (����������)
			}while(isdigit(column));
			//���� �� ����� ������� ����� (����������)
			while (!(cin >> row))
			{
				cin.clear();	
				while (cin.get() != '\n');
			}
			//�������� �������� �� ���� (tolower - ������ ������� ��������� �����)
		} while ((tolower(column) < 'a' && tolower(column) > 'j') && (row >= 1 || row <= 10));

		//�������������� ������ ������ ������� ��� �������� ����� -> �����
		int tmp = check_input_symb(column);	//������� ��������� ����� ��������� � ����� 

		row -= 1;	//�������� -1 ��� ��� ���������� ����� ������� � 0


		//���� ������� ����� �������� ����������
		if (player2OBJ.battle_field_arr[row][tmp] == hit)
		{
			cout << "The ship had been struck " << endl;		//������� ��� ��� �������
			Sleep(1500);			//�������� 1.5 ���
			cout << "Goes, " << player1OBJ.name << endl;
			Player_vs_Player(player1OBJ, player2OBJ);			//��� �����1
			system("cls");			//������� ������
		}
		//���� ������� ����� ���� �������� ����
		else if (player2OBJ.battle_field_arr[row][tmp] == bomb)
		{
			cout << "We have a shot at this place " << endl;	//�� ��� �������� � ��� �����
			Sleep(1500);				//�������� 1.5 ���
			cout << "Goes, " << player1OBJ.name << endl;
			system("cls");				//������� ������
			Player_vs_Player(player1OBJ, player2OBJ);			//��� �����1
		}
		//���� ������� ����� �����
		else if (player2OBJ.hiden_sea_battle[row][tmp] == tag_sea)
		{
			cout << "PAST! " << endl;			//����� "����"
			player2OBJ.battle_field_arr[row][tmp] = bomb;			//������ ����� �� �������� ����
			player2OBJ.hiden_sea_battle[row][tmp] = bomb;			//������ ����� �� ������� ����
			Sleep(1500);				//�������� 1.5 ���
			cout << "Goes, " << player2OBJ.name << endl;			//
			system("cls");
			Player_vs_Player(player2OBJ, player1OBJ);			//��� �����2
		}
		//���� �� ������� ����� �������
		else if (player2OBJ.hiden_sea_battle[row][tmp] == ship)
		{
			player2OBJ.battle_field_arr[row][tmp] = hit;			//������ ����� ��������� �� �������� ����
			player2OBJ.hiden_sea_battle[row][tmp] = hit;			//������ ����� ��������� �� ������� ����

			//�������� ��� �������� ������� �� �������� ������
			vector<SHIP>::iterator _itShips = find_if(player2OBJ.ships.begin(), player2OBJ.ships.end(), PREDICAT_downed_ship(row, tmp));
			
			//������� �������� �� ������� �� �������� ������ 
			if (_itShips != player2OBJ.ships.end())
			{
				_itShips->num_shot++;				//+1 � ���������� ���������
				//���� ���������� ��������� ��������� ���������� �����
				if (_itShips->num_shot == _itShips->num_deck_ship)
				{
					MyColor(LightRed, Black);		//������� ����
					cout << "KILL" << endl;			//����� "����"
					player2OBJ.num_ship--;		//-1 �� ���������� ������� ������
					_itShips->alive = false;	//������� ���� 
					_itShips->dead_zone_the_ship(player2OBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� ������� �� ������� ���� ���
					_itShips->dead_zone_the_ship(player2OBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� ������� �� �������� ���� ���
				}else
				{
					MyColor(Yellow, Black);			//����� ����
					cout << "STRUCK " << endl;		//����� "�����"
				}
			}

			Sleep(1000);			//�������� 1 ���
			system("cls");			//������� ������
			//�������� ��� ���� ���
			Player_vs_Player(player1OBJ, player2OBJ);				//��� �����1
		}
	}
}
//����� ���� COMP vs Player (��� ���������)
void Game::COMP_vs_Player(Player compOBJ, Player playerOBJ)
{
	system("cls");
	compOBJ.show_sea_battle_hidden_player();		//����� �������� ���� ��� �����
	
		//���� ���������� �������� ������ 0, �� �� �������� 
		if (playerOBJ.num_ship == 0)
		{
			system("cls");					//������� ������
			playerOBJ.show_sea_battle_hidden_player();
			MyColor(LightRed, Black);		//������ - ������� ����
			cout << playerOBJ.name << ", LOSE!!! " << endl;	//� ��� �� �������� ��������, �� ���������
			MyColor(LightCyan, Black);		//������ - ���������
			Sleep(4000);			//�������� 4 ���
			start_game();			//����� ���� ������
		}
	
		//�������� �� ������� ��������
		else if (compOBJ.num_ship > 0)
		{
		//������������� ���������
			//���� true, �� ����������
			//���� false, �� �������� ������� ���������� ��� ����������� �������� �� ��������� �������
			if (new_generate_koordinat == true)
			{
				_x_ = rand() % 10;
				_y_ = rand() % 10;
				new_generate_koordinat = false;		//������ ����� ���������
			}

			//���� ������� ����� �������� ����������	(�������� �� ������������� ����)
			if (playerOBJ.battle_field_arr[_x_][_y_] == hit && alive_ship_on_which_the_last_hit == false)
			{
				system("cls");						//������� ������
				new_generate_koordinat = true;		//��������� ��������� ����� ���������
				COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
			}
			//���� ������� ����� ���� �������� ����	(�������� �� ������������� ����)
			else if (playerOBJ.battle_field_arr[_x_][_y_] == bomb)
			{
				system("cls");							//������� ������
				new_generate_koordinat = true;			//��������� ��������� ����� ���������
				COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
			}
			//���� ������� ����� �����	(�������� �� ������������� ����)
			else if (playerOBJ.hiden_sea_battle[_x_][_y_] == tag_sea)
			{
				if (playerOBJ.hiden_sea_battle[_x_][_y_] != ship && 
					playerOBJ.hiden_sea_battle[_x_][_y_] != hit){
				playerOBJ.battle_field_arr[_x_][_y_] = bomb;		//��������� ����� �� ������� ������, �� �������� ���� ���
				playerOBJ.hiden_sea_battle[_x_][_y_] = bomb;		//��������� ����� �� ������� ������, �� ������� ���� ���
				}
				system("cls");								//������� ������
				new_generate_koordinat = true;				//��������� ��������� ����� ���������
				Player_vs_COMP(playerOBJ, compOBJ);			//��� �����
			}
			//���� �� ������� ����� �������	(�������� �� ������� ����)
			else if (playerOBJ.hiden_sea_battle[_x_][_y_] == ship || alive_ship_on_which_the_last_hit == true)
			{
				playerOBJ.battle_field_arr[_x_][_y_] = hit;		//��������� ����� ��������� ��� ��������� �� �������� ���� ���
				playerOBJ.hiden_sea_battle[_x_][_y_] = hit;		//��������� ����� ��������� ��� ��������� �� ������� ���� ���
				system("cls");			//������� ������
				playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
				MyColor(Yellow, Black);			//������ ����
				cout << "STRUCK " << endl;		//����� �� ����� "�����"
				Sleep(500);			//�������� 0.5 ���	

				//�������� ��� �������� ������� �� �������� ������
				vector<SHIP>::iterator _itShips = find_if(playerOBJ.ships.begin(), playerOBJ.ships.end(), PREDICAT_downed_ship(_x_, _y_));
				//������� ��������
				if (_itShips != playerOBJ.ships.end())
				{
					if (alive_ship_on_which_the_last_hit == false)
						_itShips->num_shot++;			//+1 � ����������
					//���� ��������� ���� �� ��������� ������, �� ������� ���� � ��������� � ����� ��������� ���������
					if (_itShips->num_deck_ship == _itShips->num_shot)
					{
						MyColor(LightRed, Black);			//������ - ������� ����
						cout << "KILL " << endl;			//����� �� ����� ��� �������� "����"
						_itShips->alive = false;			//�������� � ������� ������� ������� ����
						new_generate_koordinat = true;		//��������� ��������� ����� ���������
						alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
						playerOBJ.num_ship--;				//-1 ������� �� ���� �������� ������, ��� ��������
						_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, VERTICAL);				//��������� ������� ���� ��� �������� (�� �������� ����)
						_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, VERTICAL);				//��������� ������� ���� ��� �������� (�� ������� ����)
						Sleep(500);					//�������� 0.5 ���
						COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
					}	
					//******************************************************************************************************
					
						//���������, ����� ������ �������� ��� ������ �����/������
						int tmp_column = _y_;		//���������� �������

						//------------->	�������� ������ �� ����������� 
						if (_itShips->alive == true && _itShips->dir_n == HORIZONTAL &&
							playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == ship  && _y_ + 1 <= COLUMNS - 1)
						{
						
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == ship)
							{
								_itShips->num_shot++;		//+1 � �����������
								playerOBJ.battle_field_arr[_x_][tmp_column + 1] = hit;			//�� �������� ���� ������ ����� ���������
								playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] = hit;			//�� ������� ���� ������ ����� ���������
								system("cls");				//������� ������
								playerOBJ.show_sea_battle_hidden_player();		//����� �������� ���� ���
								MyColor(Yellow, Black);					//������ ����
								cout << "STRUCK " << endl;				//����� "�����"
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Sleep(1000);			//�������� 1 ���
								tmp_column += 1;		//����� ������ �� 1 ������
							}
								//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);			//������� ����
									cout << "KILL" << endl;				//����� "����"
									playerOBJ.num_ship--;				//-1 �� ���������� �������� ������
									_itShips->alive = false;			//������� ����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� �� �������� ���� ��� 
									Sleep(1000);				//�������� 1 ���
									system("cls");				//������� ������
									playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
								}
							//���� ������� ��������� � ������ ���� � ���
							if (_itShips->y_end == COLUMNS - 1 && _itShips->alive == true)
							{
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
							}
								//���� ������� ��������� � ������ ���� � ����
							else if (_itShips->y_end == COLUMNS - 1  && _itShips->alive == false)
							{
								new_generate_koordinat = true;			//��������� ������������ ����� ���������� ��� ��������
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
							}
								//���� ������� �� ��������� � ������ ���� � ���
							else if (_itShips->y_end + 1 <= COLUMNS - 1  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								if (playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == tag_sea)
								{
									playerOBJ.battle_field_arr[_x_][tmp_column + 1] = bomb;			//�� �������� ���� ��� ������ �����
									playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] = bomb;			//�� ������� ���� ��� ������ �����
								}
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Player_vs_COMP(playerOBJ, compOBJ);		//��� ������
							}		
								//���� ������� �� ��������� � ������ ���� � ����
							else if (_itShips->y_end + 1 <= COLUMNS - 1  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;			//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
							}
						}
						//******************************************************************************************************
						//<-------------	�������� ����� �� ����������� 
						if (_itShips->alive == true && new_generate_koordinat == false && _itShips->dir_n == HORIZONTAL &&
							playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == ship  && _y_ - 1 >= 0)
						{
						
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == ship)
							{
								_itShips->num_shot++;				//+1 � ���������� ��������� �� �������
								playerOBJ.battle_field_arr[_x_][tmp_column - 1] = hit;			//�� �������� ���� ������ ����� ���������
								playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] = hit;			//�� ������� ���� ������ ����� ���������
								system("cls");					//������� ������
								playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
								MyColor(Yellow, Black);			//������ ����
								cout << "STRUCK " << endl;			//����� "�����"
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Sleep(500);			//�������� 0.5 ���
								tmp_column -= 1;			//����� �����
							}
							//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);				//������� ����
									cout << "KILL" << endl;				//����� "����"
									playerOBJ.num_ship--;				//-1 �� ���������� �������� 
									_itShips->alive = false;			//��������, ��� ������� ����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� �������� ���� ��� 
									Sleep(1000);				//�������� 1 ���
									system("cls");				//������� ������
									playerOBJ.show_sea_battle_hidden_player();				//����� �������� ���� ��� 
								}
							//���� ������� ��������� � ����� ���� � ���
							if (_itShips->y_begin == 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� ��������� � ����� ���� � ����
							else if (_itShips->y_begin == 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;					//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� �� ��������� � ����� ���� � ���
							else if (_itShips->y_begin - 1 > 0  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;								//������ ����� ��������� ���������
								if (playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == tag_sea)
								{
									playerOBJ.battle_field_arr[_x_][tmp_column - 1] = bomb;		//�� - 1 ������ ������ ����� (�� �������� ����)
									playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] = bomb;		//�� - 1 ������ ������ ����� (�� ������� ����)
								}
								Player_vs_COMP(playerOBJ, compOBJ);							//��� ������
							}
								//���� ������� �� ��������� � ����� ���� � ����
							else if (_itShips->y_begin - 1 >= 0  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;							//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);						//��� �����
							}
						}
			//******************************************************************************************************
						//���������, ����� ������� �������� ��� ������ �����/����
						int tmp_row = _x_;			//��������� ���������� ������
					
						// |
						// |
						// |
						// |
						// |
						//\_/
						//�������� ���� �� ���������
						if (_itShips->alive == true && _itShips->dir_n == VERTICAL &&
							playerOBJ.hiden_sea_battle[_x_ + 1][_y_] == ship && _x_ + 1 <= ROWS - 1)
						{
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[tmp_row + 1][_y_] == ship)
							{
								_itShips->num_shot++;				//+1 � ��������� ��������� �� �������
								playerOBJ.battle_field_arr[tmp_row + 1][_y_] = hit;			//�������� ������ ���������
								playerOBJ.hiden_sea_battle[tmp_row + 1][_y_] = hit;
								system("cls");
								playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ��� 
								MyColor(Yellow, Black);
								cout << "STRUCK " << endl;	
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Sleep(500);
								tmp_row += 1;			//����� ����
							}
							//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);
									cout << "KILL" << endl;
									playerOBJ.num_ship--;				//-1 �� ���������� �������� 
									_itShips->alive = false;			//������� �����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);				//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);				//��������� ������� ���� �� �������� ���� ��� 
									Sleep(1000);
									system("cls");
									playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
								}
								//���� ������� ��������� ���� � ���
							if (_itShips->x_end == ROWS - 1 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� ��������� ���� � ����
							else if (_itShips->x_end == ROWS - 1 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;					//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� �� ��������� ���� � ���
							else if (_itShips->x_end + 1 <= ROWS - 1  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								if (playerOBJ.hiden_sea_battle[tmp_row + 1][tmp_column] == tag_sea)
								{
									playerOBJ.battle_field_arr[tmp_row + 1][tmp_column] = bomb;
									playerOBJ.hiden_sea_battle[tmp_row + 1][tmp_column] = bomb;
								}
								Player_vs_COMP(playerOBJ, compOBJ);		//��� ������
							}
								//���� ������� �� ��������� ���� � ����
							else if (_itShips->x_end + 1 <= ROWS - 1  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;				//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}
						}
			//******************************************************************************************************
						//�������� ����� �� ���������
						//	 _
						//	/ \
						//	 |
						// 	 |
						//	 |
						//	 |
						//	 |
						if (_itShips->alive == true && _itShips->dir_n == VERTICAL &&
							playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] == ship && _x_ - 1 >= 0)
						{
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] == ship)
							{
								_itShips->num_shot++;				//+1 � ���������� ��������� �� ������� 
								playerOBJ.battle_field_arr[tmp_row - 1][_y_] = hit;		//�� �������� ���� ������ ����� ���������
								playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] = hit;		//�� ������� ���� ������ ����� ���������
								system("cls");				//������� ������
								playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ��� 
								MyColor(Yellow, Black);				//������ ����
								cout << "STRUCK " << endl;			//����� "�����"
								new_generate_koordinat = false;				//������ ����� ��������� ���������
								Sleep(500);			//�������� 0.5 ���
								tmp_row -= 1;				//����� �����
							}
							//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);			//������ - ������� ����
									cout << "KILL" << endl;				//����� "����"
									playerOBJ.num_ship--;				//-1 �� ���������� ��������
									_itShips->alive = false;			//������� �����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);					//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);					//��������� ������� ���� �� �������� ���� ��� 
									Sleep(1000);				//�������� 1 ���
									system("cls");				//������� ������
									playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ��� 
								}
								//���� ������� ��������� ����� � ���
							if (_itShips->x_begin == 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;				//������ ����� ��������� ���������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}	
								//���� ������� ��������� ����� � ����
							else if (_itShips->x_begin == 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;				//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}
								//���� ������� �� ��������� ����� � ���
							else if (_itShips->x_begin - 1 >= 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;				//������ ����� ��������� ���������
								if (playerOBJ.hiden_sea_battle[_x_ - 1][tmp_column] == tag_sea)
								{
									playerOBJ.battle_field_arr[tmp_row - 1][_y_] = bomb;
									playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] = bomb;
								}
								Player_vs_COMP(playerOBJ, compOBJ);			//��� ������
							}
								//���� ������� �� ��������� ����� � ����
							else if (_itShips->x_begin - 1 >= 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;				//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}
						}
				}
				COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
			}
	}
}
//����� ���� Player vs COMP	(��� �����)
void Game::Player_vs_COMP(Player player1OBJ, Player compOBJ)
{
	system("cls");
	//����� �������� ���� ��� � ��������� �����
	player1OBJ.show_sea_battle_hidden_player();
	//����� ���� ��� ����
	cout << compOBJ << endl;

	cout << "Goes " << player1OBJ.name << endl;
	cout << "Enter koordinat A1 > J10: ";

	int row = 0;
	char column = ' ';

	//�������� �� ������� ��������

	//���� ���������� �������� ����� 0, �� �� ��������
	if (compOBJ.num_ship == 0)
	{
		system("cls");				//������� ������
		MyColor(LightRed, Black);			//������� ����
		cout << compOBJ.name << ", LOSE!!! " << endl;	//� ��� �� �������� ��������, �� ���������
		MyColor(LightCyan, Black);			//������ - ���������
		Sleep(4000);				//�������� 4 ���
		start_game();				//����� ����� ����
	}
	//���� ���������� �������� ������ 0, ������������ ����
	if (player1OBJ.num_ship > 0)
	{
		//�������� �� ���� ���������
		do
		{
			//���� �� ����� ������ ������, ���� ����� �����������
			do
			{
				cin >> column;		//����� ����� (����������)
			}while(isdigit(column));
			//���� �� ����� ������� ����� (����������)
			while (!(cin >> row))
			{
				cin.clear();	
				while (cin.get() != '\n');
			}
		} while ((tolower(column) < 'a' && tolower(column) > 'j') && (row >= 1 || row <= 10));

		//�������������� ������ ������ ������� ��� �������� ����� -> �����
		int tmp = check_input_symb(column);	//������� ��������� ����� ��������� � ����� 

		row -= 1;	//�������� -1 ��� ��� ���������� ����� ������� � 0


		//���� ������� ����� �������� ����������
		if (compOBJ.battle_field_arr[row][tmp] == hit)
		{
			cout << "The ship had been struck " << endl;	//������� ��� ��� �������
	//		Sleep(1500);		//�������� 1.5 ���
			cout << "Goes, " << player1OBJ.name << endl;
			Player_vs_COMP(player1OBJ, compOBJ);			//��� ������
			system("cls");				//������� ������
		}
		//���� ������� ����� ���� �������� ����
		else if (compOBJ.battle_field_arr[row][tmp] == bomb)
		{
			cout << "We have a shot at this place " << endl;	//�� ��� �������� � ��� �����
		//	Sleep(1500);			//�������� 1.5 ���
			cout << "Goes, " << player1OBJ.name << endl;
			system("cls");			//������� ������
			Player_vs_COMP(player1OBJ, compOBJ);				//��� ������
		}
		//���� ������� ����� �����
		else if (compOBJ.hiden_sea_battle[row][tmp] == tag_sea)
		{
			cout << "PAST! " << endl;				//����� "����"
			if (compOBJ.battle_field_arr[row][tmp] != ship){
			compOBJ.battle_field_arr[row][tmp] = bomb;			//������ ����� �� �������� ����
			compOBJ.hiden_sea_battle[row][tmp] = bomb;			//������ ����� �� �������� ����
			}
		//	Sleep(1500);			//�������� 1.5 ���
			cout << "Goes, " << compOBJ.name << endl;
			system("cls");			//������� ������
			COMP_vs_Player(compOBJ, player1OBJ);				//��� �����
		}
		//���� �� ������� ����� �������
		else if (compOBJ.hiden_sea_battle[row][tmp] == ship)
		{
			compOBJ.battle_field_arr[row][tmp] = hit;		//������ ����� ��������� �� �������� ���� 
			compOBJ.hiden_sea_battle[row][tmp] = hit;		//������ ����� ��������� �� �������� ���� 

			//�������� ��� �������� ������� �� �������� ������
			vector<SHIP>::iterator _itShips = find_if(compOBJ.ships.begin(), compOBJ.ships.end(), PREDICAT_downed_ship(row, tmp));
			
			//������� �������� �� ������ �� �������� ������ 
			if (_itShips != compOBJ.ships.end())
			{
				_itShips->num_shot++;			//+1 � ���������� ���������
				//���� ���������� ��������� �� ������� ��������� ���������� ����� 
				if (_itShips->num_shot == _itShips->num_deck_ship)
				{
					MyColor(LightRed, Black);		//������� ����
					cout << "KILL" << endl;			//����� "����"
					compOBJ.num_ship--;			//-1 �� ���������� �������� �����
					_itShips->alive = false;	//�������� �����
					_itShips->dead_zone_the_ship(compOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� ������� ���� ���
					_itShips->dead_zone_the_ship(compOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� �������� ���� ���
				}else
				{
					MyColor(Yellow, Black);			//������ ���� 
					cout << "STRUCK " << endl;		//����� "�����"
				}
			}

			Sleep(1500);			//�������� 1.5 ��� 
			system("cls");			//������� ������
			//�������� ��� ���� ���
			Player_vs_COMP(player1OBJ, compOBJ);			//��� ������
		}
	}
}
//������ ������ ���
void Game::timer_start_battle()
{
		system("cls");
		for (int i = 3; i >= 1; i--)
		{
			MyColor(LightGreen, Black);		//������ - ������� ����
			cout << "\t\t\t\t\t\t\t" << i;	
			Sleep(1000);
			system("cls");
		}
		cout << "\t\t\t\t\t\t  *-*-*[FIGHT]*-*-*" << endl;
		Sleep(1000);
		system("cls");

	}
//����������� � ����
void Game::designations_in_game()
	{
		//����������� � ����
		cout << "[The designations in game]" << endl << endl;
		cout << "\tBomb: ";
		MyColor(DarkGray, Black);
		cout << bomb << endl;				//�����
		MyColor(LightCyan, Black);
		cout << "\tHit : ";
		MyColor(LightRed, Black);
		cout << hit << endl;				//��������� �� �������
		MyColor(LightCyan, Black);
		cout << "\tShip: ";
		MyColor(LightGreen, Black);
		cout << ship << endl;				//�������
		MyColor(LightCyan, Black);
		cout << endl << endl << "Press any key to continue " << endl;		//������ ����� ������� ��� �����������
		_getch();			//��� ������� �������
		system("cls");
	}
//������ ����
void Game::start_game()
{
	system("cls");			//������� ������ 
	//**********����������**********
	Player human1("Player1");			//��������� ��� �����1
	Player human2("Player2");			//��������� ��� �����2
	SHIP obj_ship;						//��������� ������ �������
	Player comp("COMP");				//��������� ��� COMP
	Game game;							//��������� ������ ����

	MyColor(LightCyan, Black);			//������ - ���������
	game.designations_in_game();		//����� ����������� � ����
	

	int selection = 0;	//����� �� �������	

	do
	{
		system("cls");				//������� ������ 
		MyColor(LightCyan, Black);	//������ - ��������� ����
		cout << "[Select game mode] " << endl << endl;
		cout << "\t[1] Player vs Player " << endl;
		cout << "\t[2] Player vs Computer " << endl;
		cout << "\t\t[0] Exit " << endl;
		//cout << "Action: ";
		//���� �� ����� ������� ����� (����������)
		while (!(cin >> selection))
		{
			cin.clear();	
			while (cin.get() != '\n');
		}

		//**********������� ���������� ��� ������**********
			//����� 1
		if (selection == 1)
		{
			system("cls");			//������� ������ 
			cout << "[Select game mode] " << endl << endl;
			MyColor(Yellow, Black);		//������ ���� 
			cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
			cout << "[1] Player vs Player " << endl;
			cout << "\t[2] Player vs Computer " << endl;
			cout << "\t\t[0] Exit " << endl;
			Sleep(500);			//������� 0.5 ��� 
		}	
			//����� 2
		else if (selection == 2)
		{
			system("cls");			//������� ������ 
			cout << "[Select game mode] " << endl << endl;
			cout << "\t[1] Player vs Player " << endl;
			MyColor(Yellow, Black);			//������ ���� 
			cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
			cout << "[2] Player vs Computer " << endl;
			cout << "\t\t[0] Exit " << endl;
			Sleep(500);
		}
			//����� 0
		else if (selection == 0)
		{
			system("cls");			//������� ������ 
			cout << "[Select game mode] " << endl << endl;
			cout << "\t[1] Player vs Player " << endl;
			cout << "\t[2] Player vs Computer " << endl;
			MyColor(Yellow, Black);			//������ ����
			cout << "\t\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
			cout << "[0] Exit " << endl;
			Sleep(500);				//�������� 0.5 ���
		}
		//�������
		switch (selection)
		{
		case 0:
		{
			system("cls");			//������� ������
			MyColor(LightRed, Black);		//������ - ������� ����
				cout << "\t\t\t\t\t\t  *-*-*[GOODBYE]*-*-*" << endl;
			Sleep(2000);			//�������� 2 ��� 
			exit(1);			//����� �� ��������� 
		}
		case 1:
		{
			system("cls");			//������� ������
			//��� ������ �����������
			int tmp_action;

			do
			{
				system("cls");				//������� ������ 
				MyColor(LightCyan, Black);			//������ - ��������� 
				cout << "[Player vs Player] " << endl << endl;
				cout << "\t[1] Set ships rand, " << human1.name << endl;
				cout << "\t[2] Set ships manually, " << human1.name << endl;
				cout << "\t[3] Set ships rand, " << human2.name << endl;
				cout << "\t[4] Set ships manually, " << human2.name << endl;
				cout << "\t[5] Rename players " << endl;
				cout << "\t[6] Start BATTLE " << endl;
				cout << "\t\t[0] Back to main menu " << endl;
				//cout << "Action: ";
							//���� �� ����� ������� ����� (����������)
				while (!(cin >> tmp_action))
				{
					cin.clear();	
					while (cin.get() != '\n');
				}

				//**********������� ���������� ��� ������**********
					//����� 1
				if (tmp_action == 1)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Player] " << endl << endl;
					MyColor(Yellow, Black);				//������ ���� 
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 2
				else if (tmp_action == 2)
				{
					system("cls");				//������� ������ 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					MyColor(Yellow, Black);				//������ ���� 
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 3
				else if (tmp_action == 3)
				{
					system("cls");			//������� ������
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					MyColor(Yellow, Black);			//������ ����
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ���
				}
					//����� 4
				else if (tmp_action == 4)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					MyColor(Yellow, Black);			//������ ����
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ���
				}
					//����� 5
				else if (tmp_action == 5)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					MyColor(Yellow, Black);			//������ ����
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 6 
				else if (tmp_action == 6)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					MyColor(Yellow, Black);			//������ ���� 
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}

					//����� 0 
				else if (tmp_action == 0)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					MyColor(Yellow, Black);			//������ ���� 
					cout << "\t\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[0] Back to main menu " << endl;
					MyColor(LightCyan, Black);		//������ - ��������� ���� 
					Sleep(500);				//�������� 0.5 ��� 
				}
				//�������
				switch (tmp_action)
				{
					case 1:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� ����������� 
							if (human1.num_ship == 10){
								cout << "Ships have been installed, " << human1.name << endl;
								Sleep(1000);			//�������� 1 ��� 
								break;
							}

							human1.all_set_ships_rand();			//����� ��������� ��������
							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//�������� 1 ��� 
							break;
						}	//case 1
					case 2:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� ����������� 
							if (human1.num_ship == 10){
								cout << "Ships have been installed, " << human1.name << endl;
								Sleep(1000);			//�������� 1 ��� 
								break;
							}

							human1.all_set_ships_manually();		//����� ��������� ��������
							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//�������� 1 ��� 
							break;
						}	//case 2
					case 3:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����2 10, �� ����������� ��������� ����������� 
							if (human2.num_ship == 10){
								cout << "Ships have been installed, " << human2.name << endl;
								Sleep(1000);			//��������1 ��� 
								break;
							}

							human2.all_set_ships_rand();			//����� ��������� ��������	
							cout << human2.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//�������� 1 ��� 		
							break;
						}	//case 3
					case 4:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����2 10, �� ����������� ��������� ����������� 
							if (human2.num_ship == 10){
								cout << "Ships have been installed, " << human2.name << endl;
								Sleep(1000);			//�������� 1 ��� 
								break;
							}

							human2.all_set_ships_manually();		//����� ��������� ��������	
							cout << human2.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//�������� 1 ��� 
							break;
						}	//case 4
					case 5:
						{
							system("cls");			//������� ������ 
								//���� ����� �����1
							cout << "Entered new name, " << human1.name << endl;
							cin >> human1;
								//���� ����� �����2
							cout << "Entered new name, " << human2.name << endl;
							cin >> human2;

							Sleep(1000);			//�������� 1 ���
							break;
						}
					case 6:
						{
							system("cls");			//������� ������ 
							//���� ���������� �������� ������1 ������ 10
							if (human1.num_ship < 10 && human2.num_ship == 10){
								cout << "Ships not installed, " << human1.name << endl;			//������� �� �����������
								Sleep(1500);			//�������� 1.5 ��� 
								break;
							}
							//���� ��� ������ �� ���������� �������
							else if (human1.num_ship < 10 && human2.num_ship < 10)
							{
								cout << "The players set their ships! " << endl;				//������, ���������� ���� �������
								Sleep(1500);			//�������� 1.5 ��� 
								break;
							}
							//���� ���������� �������� ������2 ������ 10
							else if (human2.num_ship < 10 && human1.num_ship == 10){
								cout << "Ships not installed, " << human2.name << endl;			//������� �� �����������
								Sleep(1500);			//�������� 1.5 ���
								break;	
							}
								
							//**********START GAME**********
							//����������� "��� ������ �����"
							int determination = rand() % 2 + 1;
							//���� 1, �� ��� �����1
							if (determination == 1) {
								system("cls");			//������� ������
								cout << "The first goes, " << human1.name << endl << endl;
								Sleep(1500);			//�������� 1.5 ���
								//system("cls");
							}
							else {
								system("cls");			//������� ������
								cout << "The first goes, " << human2.name << endl << endl;
								Sleep(1500);		//�������� 1.5 ��� 
								//system("cls");
							}

							//3..2..1..FIGHT! - Start battle 
							game.timer_start_battle();	//������ �� ������ ��� 

							//**********BATTLE**********
							if (determination == 1)
								game.Player_vs_Player(human1, human2);
							else
								game.Player_vs_Player(human2, human1);
							break;
						}
				}	//switch

			} while (tmp_action);

			break;

		}	//case 1
		case 2:
		{
			int action;		//����� �� �������
			do
			{
				system("cls");			//������� ������ 
				MyColor(LightCyan, Black);			//������ - ��������� ���� 
				cout << "[Player vs Computer] " << endl << endl;
				cout << "\t[1] Set ships rand, " << human1.name << endl;
				cout << "\t[2] Set ships manually, " << human1.name << endl;
				cout << "\t[3] Rename players " << endl;
				cout << "\t[4] Start game " << endl;
				cout << "\t\t[0] Back to main menu " << endl;
				//cout << "Action: ";  
				//���� �� ����� ������� ����� (����������)
				while (!(cin >> action))
				{
					cin.clear();	
					while (cin.get() != '\n');
				}
					//����� 1
				if (action == 1)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Computer] " << endl << endl;
					MyColor(Yellow, Black);			//������ ���� 
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//������� 0.5 ��� 
				}
					//����� 2
				else if (action == 2)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					MyColor(Yellow, Black);				//������ ���� 
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[2] Set ships manually, " << human1.name << endl;	
					cout << "\t[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ���
				}
					//����� 3
				else if (action == 3)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					MyColor(Yellow, Black);			//������ ���� 
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 4
				else if (action == 4)
				{
					system("cls");			//������� ������ 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Rename players " << endl;
					MyColor(Yellow, Black);			//������ ���� 
					cout << "\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);		//�������� 0.5 ���
				}
					//����� 0
				else if (action == 0)
				{
					system("cls");		//������� ������ 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					MyColor(Yellow, Black);			//������ ����
					cout << "\t\t--> ";MyColor(LightCyan, Black);	//������ - ��������� ���� 
					cout << "[0] Back to main menu " << endl;
					Sleep(500);			//������� ������ 
				}
				//�������
				switch (action)
				{
					case 1:
						{
							system("cls");		//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� ����������� 
							if (human1.num_ship == 10){
								cout << "Ships have been installed " << endl;
								Sleep(1000);			//�������� 1 ���
								break;
							}

							human1.all_set_ships_rand();			//����� ��������� ��������

							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//�������� 1 ��� 
							break;
						}
					case 2:
						{
							system("cls");				//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� �����������
							if (human1.num_ship == 10){
								cout << "Ships have been installed " << endl;
								Sleep(1000);				//�������� 1 ��� 
								break;
							}

							human1.all_set_ships_manually();			//����� ��������� ��������
							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);				//�������� 1 ��� 
							break;
						}
					case 3:
						{
							system("cls");			//������� ������ 
								//���� ������ ����� �����1
							cout << "Entered new name, " << human1.name << endl;
							cin >> human1;	
								//���� ������ ����� COMP
							cout << "Entered new name, " << comp.name << endl;
							cin >> comp;
							Sleep(1500);		//������� ������
							break;
						}
					case 4:
						{
							system("cls");			//������� ������ 
							//���� ����� ����������� �������, �� ������������� ����� ������
							if (human1.num_ship == 10)
								comp.all_set_ships_rand();		//����� ��������� �������� 
								//���� �� ���������, �� ����� � ����
							else{
								cout << human1.name << ", set their ships " <<endl;
								Sleep(1000);			//�������� 1 ���
								break;
							}
							//**********START GAME**********
							//����������� "��� ������ �����"
							int determination = rand() % 2 + 1;

							if (determination == 1) {
								system("cls");			//������� ������ 
								cout << "The first goes, " << human1.name << endl << endl;
								Sleep(2000);			//�������� 2 ��� 
								//system("cls");			
							}
							else {
								system("cls");				//������� ������
								cout << "The first goes, " << comp.name << endl << endl;
								Sleep(2000);				//�������� 2 ��� 
								//system("cls");
							}

							//3..2..1..FIGHT! - Start battle (������ ���)
							game.timer_start_battle();	//������ �� ������ ��� 

							//**********BATTLE**********
							if (determination == 1)
								game.Player_vs_COMP(human1, comp);
							else
								game.COMP_vs_Player(comp, human1);

							break;
						}
				}
			} while (action);
			break;
		}
		}
	} while (selection);
}
