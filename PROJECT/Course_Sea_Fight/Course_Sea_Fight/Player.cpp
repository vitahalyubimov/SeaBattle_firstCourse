#include "stdafx.h"

//���������� ������ ����
ostream& operator <<(ostream&stream, Player& obj)
{
	//����� ���� ���
	battlefield(cout, obj.battle_field_arr, const_cast<char *>(obj.name.c_str()));
	return stream;
}
//���������� ����� ����� ������
istream& operator >> (istream&stream, Player& obj)
{
	//���� ����� ������
	stream >> obj.name;
	return stream;
}
//����� ������ �������� ���� ��� �� ������� ����������� �������
void Player::show_sea_battle_hidden_player()
{
	//system("cls");
	battlefield(cout, hiden_sea_battle, const_cast<char *>(name.c_str()));
}
//*****RAND*****
//��� ��������� ������ �������
vector<SHIP> Player::set_ship_rand(int size_deck)
{
	int LengthSetShip = size_deck - 1;		//����� ���������������� �������
	bool touchShip, okSet_ship = false;		//������� ������� � ��������� ��������� �������
	direction dir;		//��������� ������� ���������/�����������
	int x, y, r;	//���������� � ���������
	int x1, y1, x2, y2;	//����������� ������ � ����� �������

	//���� ��������� ������� �������
	while (okSet_ship == false)
	{
		touchShip = false;
		r = rand() % 2;
		//���������� ��� ��������� ������� �����������/���������
		if (r == 0)
			dir = HORIZONTAL;
		else
			dir = VERTICAL;

		//���� ������� �������� ������� ������� 
		while (touchShip == false)
		{
			x = rand() % 10;
			y = rand() % 10;
			if (hiden_sea_battle[x][y] == tag_sea)
				touchShip = true;
			//�������� ������������� ������� �� ������� ������� �������
			if (dir == VERTICAL)
			{
				for (int i = x;i < x + size_deck;i++)
				{
					if (hiden_sea_battle[i][y] == ship)
						touchShip = false;
				}
			}
			//�������� ��������������� ������� �� ������� ������� �������
			else if (dir == HORIZONTAL)
			{
				for (int i = y;i < y + size_deck;i++)
				{
					if (hiden_sea_battle[x][i] == ship)
						touchShip = false;
				}
			}
		}
		//��������� �������� ������� �������
		bool resCheck_touchShip = false;


		switch (dir)
		{
		case HORIZONTAL:
			if (hiden_sea_battle[x][y + LengthSetShip] == tag_sea)
			{
				if ((y + LengthSetShip) >= 10)
					break;
				resCheck_touchShip = inspection_of_the_ship_at_the_touch(x, y, dir, size_deck); // �������� ������� ������
				if (resCheck_touchShip == false)
				{
					for (int i = 0; i < size_deck; i++)
					{
						//��������� �������
						hiden_sea_battle[x][y + i] = ship;
						//����������� ������ � ����� �������
						x1 = x;
						y1 = y;
						x2 = x;
						y2 = y + i;
					}
					okSet_ship = true;
				}
			}
			break;

		case VERTICAL:
			if (hiden_sea_battle[x + LengthSetShip][y] == tag_sea)
			{
				resCheck_touchShip = inspection_of_the_ship_at_the_touch(x, y, dir, size_deck);
				if (resCheck_touchShip == false)
				{
					for (int i = 0; i < size_deck; i++)
					{
						//��������� �������
						hiden_sea_battle[x + i][y] = ship;
						//����������� ������ � ����� �������
						x1 = x;
						y1 = y;
						x2 = x + i;
						y2 = y;
					}
					okSet_ship = true;
				}
			}
			break;
		}
	}
	//��������� ������� � ������ ���� �������� ������
	SHIP add_ship(x1, y1, x2, y2, size_deck, false, dir);
	ships.push_back(add_ship);
	return ships;
}
//��������� �������� �� ������� ������� + 1 ������
bool Player::inspection_of_the_ship_at_the_touch(int x, int y, direction dir, int size_deck)
{
	//���������� ��� �������� ���� (tag sea)
	bool check_tag_sea = false;

	switch (dir)
	{
		//���� �������������� ���������
	case HORIZONTAL:
		if (y == 0)
			if (x == 0)
			{
				for (int i = 0; i <= size_deck; i++)
					if (hiden_sea_battle[x + 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x][y + size_deck] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else if (x == 9)
			{
				for (int i = 0; i <= size_deck; i++)
					if (hiden_sea_battle[x - 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x][y + size_deck] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else
			{
				for (int i = 0; i <= size_deck; i++)
				{
					if (hiden_sea_battle[x + 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
					if (hiden_sea_battle[x - 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				}
				if (hiden_sea_battle[x][y + size_deck] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
		else if (y == (10 - size_deck))
			if (x == 0)
			{
				for (int i = -1; i < size_deck; i++)
					if (hiden_sea_battle[x + 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x][y - 1] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else if (x == 9)
			{
				for (int i = -1; i < size_deck; i++)
					if (hiden_sea_battle[x - 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x][y - 1] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else
			{
				for (int i = -1; i < size_deck; i++)
				{
					if (hiden_sea_battle[x + 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
					if (hiden_sea_battle[x - 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				}
				if (hiden_sea_battle[x][y - 1] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
		else
			if (x == 0)
			{
				for (int i = -1; i <= size_deck; i++)
					if (hiden_sea_battle[x + 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x][y - 1] != tag_sea)
				{
					check_tag_sea = true;
					break;
				}
				if (hiden_sea_battle[x][y + size_deck] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else if (x == 9)
			{
				for (int i = -1; i <= size_deck; i++)
					if (hiden_sea_battle[x - 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x][y - 1] != tag_sea)
				{
					check_tag_sea = true;
					break;
				}
				if (hiden_sea_battle[x][y + size_deck] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else
			{
				for (int i = -1; i <= size_deck; i++)
				{
					if (hiden_sea_battle[x + 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
					if (hiden_sea_battle[x - 1][y + i] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				}
				if (hiden_sea_battle[x][y - 1] != tag_sea)
				{
					check_tag_sea = true;
					break;
				}
				if (hiden_sea_battle[x][y + size_deck] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}

	case VERTICAL: //������������ ��������� �������
		if (x == 0)
			if (y == 0)
			{
				for (int i = 0; i <= size_deck; i++)
					if (hiden_sea_battle[x + i][y + 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x + size_deck][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else if (y == 9)
			{
				for (int i = 0; i <= size_deck; i++)
					if (hiden_sea_battle[x + i][y - 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x + size_deck][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else
			{
				for (int i = 0; i <= size_deck; i++)
				{
					if (hiden_sea_battle[x + i][y + 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
					if (hiden_sea_battle[x + i][y - 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				}
				if (hiden_sea_battle[x + size_deck][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
		else if (x == (10 - size_deck))
			if (y == 0)
			{
				for (int i = -1; i < size_deck; i++)
					if (hiden_sea_battle[x + i][y + 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x - 1][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else if (y == 9)
			{
				for (int i = -1; i < size_deck; i++)
					if (hiden_sea_battle[x + i][y - 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x - 1][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else
			{
				for (int i = -1; i < size_deck; i++)
				{
					if (hiden_sea_battle[x + i][y + 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
					if (hiden_sea_battle[x + i][y - 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				}
				if (hiden_sea_battle[x - 1][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
		else
			if (y == 0)
			{
				for (int i = -1; i <= size_deck; i++)
					if (hiden_sea_battle[x + i][y + 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x - 1][y] != tag_sea)
				{
					check_tag_sea = true;
					break;
				}
				if (hiden_sea_battle[x + size_deck][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else if (y == 9)
			{
				for (int i = -1; i <= size_deck; i++)
					if (hiden_sea_battle[x + i][y - 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				if (hiden_sea_battle[x - 1][y] != tag_sea)
				{
					check_tag_sea = true;
					break;
				}
				if (hiden_sea_battle[x + size_deck][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
			else
			{
				for (int i = -1; i <= size_deck; i++)
				{
					if (hiden_sea_battle[x + i][y + 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
					if (hiden_sea_battle[x + i][y - 1] != tag_sea)
					{
						check_tag_sea = true;
						break;
					}
				}
				if (hiden_sea_battle[x - 1][y] != tag_sea)
				{
					check_tag_sea = true;
					break;
				}
				if (hiden_sea_battle[x + size_deck][y] != tag_sea)
				{
					check_tag_sea = true;
				}
				break;
			}
	}
	return check_tag_sea;
}
//���������� ��� �������
void Player::all_set_ships_rand()
{
	//1-� �������� (4)
	for (int i = 0; i < 4; i++) {
		set_ship_rand(1);
		num_ship++;
	}
	//2-� �������� (3)
	for (int i = 0; i < 3; i++) {
		set_ship_rand(2);
		num_ship++;
	}
	//3-� �������� (2)
	for (int i = 0; i < 2; i++) {
		set_ship_rand(3);
		num_ship++;
	}
	//4-� �������� (1)
	set_ship_rand(4);
	num_ship++;

	show_sea_battle_hidden_player();
}
//*****MANUALLY*****
//��������� ���� �������
vector<SHIP> Player::set_ship_manually(int size_deck)
{
	int LengthSetShip = size_deck - 1;					//����� ���������������� �������
	bool touchShip, okSet_ship = false;					//������� ������� � ��������� ��������� �������
	direction dir_on;				//��������� ������� ���������/�����������		
	int x, y, generate_direction;	//���������� � ���������
	int x1, y1, x2, y2;				//����������� ������ � ����� �������
	char symb;						//��� ����� ���������� �����

	//���� ��������� ������� �������
	while (okSet_ship == false)
	{
		touchShip = false;
		while (touchShip == false)
		{
			system("cls");
			show_sea_battle_hidden_player();

			cout << "Entered the coordinates " << size_deck << " deck ship " << endl;
			cout << "A1 - J10: ";
			//���� �� ����� ������ ������, ���� ����� �����������
			do
			{
				cin >> symb;		//���� ����� (����������)
			} while (isdigit(symb));
			cout << "1 - 10: ";
			//���� �� ����� ������� �����, ��������� ����
			while (!(cin >> x))
			{
				cin.clear();	
				while (cin.get() != '\n');
			}
			//��� ��� ��������� ����� � 0, �������� - 1
			x -= 1;
			y = check_input_symb(symb);

			if (hiden_sea_battle[x][y] == tag_sea)
				touchShip = true;
		}
		//���� ����� ������ ��� 1, �� �������� ����������� �������
		if (size_deck > 1)
		{
			do {
				//system("cls");
				cout << endl;
				cout << "Select direction ship " << endl;
				cout << "[1] HORIZONTAL " << endl;
				cout << "[2] VERTICAL " << endl;
				cin >> generate_direction;
			} while (generate_direction < 1 || generate_direction > 2);
			//���������� ��� ��������� ������� �����������/���������
			if (generate_direction == 1)
				dir_on = HORIZONTAL;
			else
				dir_on = VERTICAL;
		}
		else
			dir_on = HORIZONTAL;

		bool resCheck_touchShip = false;

		switch (dir_on)
		{
		case HORIZONTAL:
			if (hiden_sea_battle[x][y + LengthSetShip] == tag_sea)
			{
				if ((y + LengthSetShip) >= 10)
					break;
				resCheck_touchShip = inspection_of_the_ship_at_the_touch(x, y, dir_on, size_deck); // �������� ������� ������
				if (resCheck_touchShip == false)
				{
					for (int i = 0; i < size_deck; i++)
					{
						//��������� ������� 
						hiden_sea_battle[x][y + i] = ship;
						//����������� ������ � ����� �������
						x1 = x;
						y1 = y;
						x2 = x;
						y2 = y + i;
					}
					okSet_ship = true;
				}
			}
			break;

		case VERTICAL:
			if (hiden_sea_battle[x + LengthSetShip][y] == tag_sea)
			{
				resCheck_touchShip = inspection_of_the_ship_at_the_touch(x, y, dir_on, size_deck);
				if (resCheck_touchShip == false)
				{
					for (int i = 0; i < size_deck; i++)
					{
						//��������� �������
						hiden_sea_battle[x + i][y] = ship;
						//����������� ������ � ����� �������
						x1 = x;
						y1 = y;
						x2 = x + i;
						y2 = y;
					}
					okSet_ship = true;
				}
			}
			break;
		}
	}
	//��������� ������� � ������ ���� �������� ������
	SHIP new_ship(x1, y1, x2, y2, size_deck, false, dir_on);
	ships.push_back(new_ship);
	system("cls");
	show_sea_battle_hidden_player();
	return ships;
}
//������ ����������� ���� �������� ��������
void Player::all_set_ships_manually()
{
	//4-x ��������
	set_ship_manually(4);
	num_ship++;
	//3-� ��������
	for (int i = 0; i < 2; i++) {
		set_ship_manually(3);
		num_ship++;
	}
	//2-� ��������
	for (int i = 0; i < 3; i++) {
		set_ship_manually(2);
		num_ship++;
	}
	//1-� ��������
	for (int i = 0; i < 4; i++) {
		set_ship_manually(1);
		num_ship++;
	}
}
