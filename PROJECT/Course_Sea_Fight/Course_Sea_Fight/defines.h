#pragma once
//****************��������� �������****************
enum direction { HORIZONTAL, VERTICAL };


//**********DEFINES**********
	//������ ����
#define COLUMNS 10
#define ROWS 10
	//����������� � ����
#define ship char(251)		//�������
#define bomb char(253)		//�����
#define hit char(229)		//���������
#define tag_sea char(177)	//����

//**********�����**********
enum ConsoleColor
{
	Black = 0,				//������
	Blue = 1,				//�����
	Green = 2,				//�������
	Cyan = 3,				//����� - ���������
	Red = 4,				//�������
	Magenta = 5,			//���������
	Brown = 6,				//����������
	LightGray = 7,			//������ - �����
	DarkGray = 8,			//����� - �����
	LightBlue = 9,			//������ - �����
	LightGreen = 10,		//������ - �������
	LightCyan = 11,			//������ - ���������
	LightRed = 12,			//������ - �������
	LightMagenta = 13,		//������ - ���������
	Yellow = 14,			//������
	White = 15				//�����
};
