#include "stdafx.h"

//����������� ������� ���� �������
void SHIP::dead_zone_the_ship(char arr[][COLUMNS], bool _is_dead, direction dir_n)
{
	if (!_is_dead)
	{
		//VERTICAL
		if (dir_n == VERTICAL)
		{
			//���� ������� � ����� ������� ����
			if (x_begin == 0 && y_begin == 0)
			{
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
				}
				//under(���)
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
			//���� ������� � ������ ����
			else if (y_begin == 0 && x_begin - 1 >= 0)
			{
				//above(���)
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
				}
				//under(���)
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
			//���� ������� � ����� ������ ����
			else if (x_end == ROWS - 1 && x_begin + 1 >= ROWS - 1 && x_begin - 1 < 0)
			{
				//above(���)
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
				}
			}
			//���� ������� � �������� ���� ����
			else if (x_begin == 0 && y_begin - 1 >= 0 && y_begin + 1 <= COLUMNS - 1)
			{
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
					arr[i][y_begin - 1] = bomb;
				}
				//under(���)
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
			//���� ������� � ������� ���� ����
			else if (x_end == ROWS - 1 && y_end - 1 >= 0 && y_end + 1 <= COLUMNS - 1)
			{
				//above(���)
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
					arr[i][y_begin + 1] = bomb;
				}
			}
			//���� ������� � ������ ������� ����
			else if (x_begin == 0 && y_begin == COLUMNS - 1)
			{
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
				}
				//under
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
			}
			//���� ������� � ������� ����
			else if (y_begin == COLUMNS - 1 && x_begin - 1 >= 0 && x_end + 1 <= ROWS - 1)
			{
				//above
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
				}
				//under
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
			}
			//���� ������� � ������ ������ ����
			else if (y_end == COLUMNS - 1 && x_end == ROWS - 1)
			{
				//above
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
				}
			}
			//���� ������� �� �������� ���� ����
			else if (y_begin - 1 >= 0 && y_begin + 1 <= COLUMNS - 1 && x_begin - 1 >= 0 && x_end + 1 <= ROWS - 1)
			{
				//above
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
					arr[i][y_begin + 1] = bomb;
				}
				//under
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
		}
		//HORIZONTAL
		else if (dir_n == HORIZONTAL)
		{
			//������ ������� ����
			if (y_end == COLUMNS - 1 && x_end == 0)
			{
				//after
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
				}
			}
			//�������, ������� �� �������� ���� ����
			else if (x_begin - 1 >= 0 && y_begin - 1 >= 0 && x_end + 1 <= ROWS - 1 && y_end + 1 <= COLUMNS - 1)
			{
				//before(�����)
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
					arr[x_begin + 1][i] = bomb;
				}
				//after(�����)
				arr[x_end - 1][y_end + 1] = bomb;
				arr[x_end][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;

			}
			//�������, ������� ��������� � ������ ����
			else if (x_begin - 1 >= 0 && x_begin + 1 <= ROWS - 1 && y_end == COLUMNS - 1)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
					arr[x_begin + 1][i] = bomb;
				}
			}
			//������ ������ ����
			else if (x_end == ROWS - 1 && y_end == COLUMNS - 1)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
				}
			}
			//���� ������� ��������� � ������ ����� ����
			else if (y_end + 1 <= COLUMNS - 1 && y_end - 1 >= 0 && x_end == ROWS - 1)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end - 1][y_end + 1] = bomb;
			}
			//���� ������� ��������� � ������� ����� ����
			else if (y_begin - 1 > 0 && y_end + 1 < COLUMNS - 1 && x_begin - 1 <= 0)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;
			}
			//���� ������� ��������� � ����� ������� ����
			else if (y_begin == 0 && x_begin == 0 && x_begin + 1 < ROWS - 1)
			{
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;
			}
			//���� ������� ��������� � ����� ����
			else if (y_begin == 0 && x_begin - 1 >= 0 && x_begin + 1 <= ROWS - 1)
			{
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
					arr[x_begin - 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end - 1][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;
			}
			//���� ������� � ����� ������ ����
			else if (y_begin == 0 && x_begin + 1 > ROWS - 1 && x_begin - 1 > 0)
			{
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end - 1][y_end + 1] = bomb;
			}
		}
	}

}

//���������� ������ ������ �� 1-�� �������
ostream& operator <<(ostream&stream, const SHIP& obj)
{
	cout.setf(ios::boolalpha);				//���� ��� ������ true/false ������
	stream << "Koordinats: begin: " << obj.x_begin + 1 << " " << obj.y_begin + 1
		<< " end: " << obj.x_end + 1 << " " << obj.y_end + 1 << endl;
	stream << "State: " << obj.alive << endl
		<< "Num deck: " << obj.num_deck_ship << endl
		<< "Num shot: " << obj.num_shot << endl;

	if (obj.dir_n == VERTICAL)
		stream << "Direction: VERTICAL" << endl;
	else
		stream << "Direction: HORIZONTAL" << endl;
	for (int i = 0; i < obj.num_deck_ship; i++)
	{
		stream << obj.new_ship[i];		//����� �������
	}
	stream << endl;
	return stream;
}