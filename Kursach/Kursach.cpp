#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#pragma warning(disable:4996)


struct user {
	char login[20];
	char password[20];
	int role;
};

struct artist {
	char name[20];
	char sec_name[20];
	char patr[20];
	int exp;
	int solar = 0;
	char show[20];
	char role[20];
	int date[3];
};

struct show {
	char show[20];
	char role[20];
	int date[3];
	int payment;
};

int menu_navigation(int amount_of_func);                            
int menu_enter();
int enter_admin();
int admin();
int admin_menu();
int menu_art_or_show();
int menu_filtr_art();
int menu_filtr_show();
int filtr_art_exr();
int filtr_art_date();
int filtr_art_solar();
int filtr_show_date();
int filtr_show_solar();
int enter_user();
int user();
int user_menu();
void decrypt(char str[]);           
int new_user();              
int del_user();
void clear_stream();                 
int users_config();
int users_config_menu();
int users_output();
int artist_output();
int new_artist();
int del_artist();
int edit_artist();
int search();
int search_s();
int search_menu();
int search_show_menu();
int search_sec_name();
int search_patr();
int search_exp();
int search_name();
int new_show();
int show_output();
int del_show();
int edit_show();
int search_show();
int search_role();
int set_role();
char* enter_syb();
char* enter_syb_name();
int enter_num();
int sort();
int sort_menu();
int sort_solar();
int sort_date();


FILE* file_1, * file_2, * file_3;

int amount_admin = -1;                          //variable to create admin_user at first


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");
	printf("|             ���������              |\n");
	printf("|------------------------------------|\n");
	printf("|     'Arrow UP'     - �����         |\n");
	printf("|     'Arrow Down'   - ����          |\n");
	printf("|     'Enter'        - �����������   |\n");
	printf("|                                    |\n");
	printf("|                      �������       |\n");
	printf("|     'ESC'          -   ���         |\n");
	printf("|                       �����        |\n");
	printf("|____________________________________|\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	if (!(file_1 = fopen("users.txt", "r+b")))
		new_user();
	else {
		fseek(file_1, 0, SEEK_END);
		if (ftell(file_1) == 0) {
			printf("������������ �� ���� ����������, ����� ������ �����\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			new_user();
		}
	}
	int vvod = 0;
	while (vvod == 0) {
		switch (menu_enter()) {
		case 1: {
			system("cls");
			if (enter_admin() == 1)
				admin();
			break;
		}
		case 2: {
			system("cls");
			if (enter_user() == 1)
				user();
			break;
		}
		case 3: {
			system("cls");
			vvod = 1;
			break;
		}
		default: {
			system("cls");
			puts("��������� ��������� ������\n");
		}
		}
	}
	return 0;
}

int menu_navigation(int amount_of_func) {                         //function return value of menu point                   
	char word;
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 0;
	position.Y = 0;
	SetConsoleCursorPosition(hConsole, position);
	do {
		word = _getch();
		if (word == 80)
			if (position.Y < amount_of_func)
				if (position.Y == amount_of_func - 1) {
					SetConsoleCursorPosition(hConsole, position);
					puts("   ");
					position.Y = 0;
					SetConsoleCursorPosition(hConsole, position);
					puts("-> ");
				}
				else {
					SetConsoleCursorPosition(hConsole, position);
					puts("   ");
					position.Y++;
					SetConsoleCursorPosition(hConsole, position);
					puts("-> ");
				}
		if (word == 72)
			if (position.Y > 0) {
				SetConsoleCursorPosition(hConsole, position);
				puts("   ");
				position.Y--;
				SetConsoleCursorPosition(hConsole, position);
				puts("-> ");
			}
			else {
				SetConsoleCursorPosition(hConsole, position);
				puts("   ");
				position.Y = amount_of_func - 1;
				SetConsoleCursorPosition(hConsole, position);
				puts("-> ");
			}
		if (word == 13) {
			break;
		}
		if (word == 27)
			return amount_of_func;
	} while (1);
	system("cls");
	return position.Y + 1;
}                 

int menu_enter() {
	int choice;
	system("cls");
	puts("-> �������������");
	puts("   ������������");
	puts("   �����");
	choice = menu_navigation(3);
	return choice;
}

int new_user() {
	system("cls");
	if (!(file_1 = fopen("users.txt", "r+b"))) {
		printf("������������ �� ���� ����������, ����� ������ �����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		file_1 = fopen("users.txt", "w+b");
	}

	char key[127] = "                                nopqrstuvwxyz{|} !\"#$%&'()*+,-./0956732184:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklm";
	char *str;
	

	struct user new_user, vedro;
	while (1) {                                       
		puts("������� ����� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	fseek(file_1, 0, SEEK_END);
	if (ftell(file_1) > 0) {
		rewind(file_1);
		while (fread(&vedro, sizeof(struct user), 1, file_1) != 0) {      
			{
				decrypt(vedro.login);
				if (strcmp(str, vedro.login) == 0) {
					system("cls");
					puts("������ ����� �����\n");
					puts("\n������� ����� ������� ����� ����������...");
					_getch();
					system("cls");
					return 0;
				}
			}
		}
	}

	for (int i = 0; i < strlen(str); i++) 
		new_user.login[i] = key[str[i]];
	new_user.login[strlen(str)] = '\0';

	int amount_of_syb = 0;
	while (1) {                               
		puts("������� ������ (�������� 19 ��������)");
		while (1) {
			str[amount_of_syb] = _getch();
			if (str[amount_of_syb] == 8 && amount_of_syb != 0) {
				printf("\b \b");
				str[amount_of_syb] = NULL;
				amount_of_syb--;
				continue;
			}
			if (str[amount_of_syb] == 8 && amount_of_syb == 0)
				continue;
			if (str[amount_of_syb] == 13) {
				str[amount_of_syb] = '\0';
				break;
			}
			if (str[amount_of_syb] == 27)
				return 0;
			printf("*");
			amount_of_syb++;
		}
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	strcpy(new_user.password, str);
	for (int i = 0; i < strlen(new_user.password); i++) 
		new_user.password[i] = key[str[i]];
	new_user.password[strlen(str)] = '\0';
	while (1) {
		if (amount_admin == -1) {
			printf("�������������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			amount_admin++;
			new_user.role = 1;
			break;
		}
		else {
			int a;
			system("cls");
			puts("-> ������������");
			puts("   �������������");
			a = menu_navigation(2);
			if (a == 1 || a == 2) {
				if (a == 2)
				amount_admin++;
				new_user.role = a - 1;
				system("cls");
				break;
			}
			else {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
			}
		}
	}

	fwrite(&new_user, sizeof(struct user), 1, file_1); 

	fclose(file_1);  
}

int enter_admin() {
	if (!(file_1 = fopen("users.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	system("cls");
	char *str;
	struct user vedro;
	while (1) {
		puts("������� ����� (�������� 19 ��������)");           //���� ������
		if (!(str = enter_syb()))
		return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}

	int poisk = 0;
	fseek(file_1, 0, SEEK_END);
	if (ftell(file_1) > 0) {
		rewind(file_1);
		while (fread(&vedro, sizeof(struct user), 1, file_1) != 0) {      // //�������� ���� �� ������������ � ����� �������
			{
				if (vedro.role == 1) {
					decrypt(vedro.login);
					if (strcmp(str, vedro.login) == 0) {
						system("cls");
						poisk = 1;
						break;
					}
				}
			}
		}
	}

	int amount_of_syb = 0;
	if (poisk == 1) {
		while (1) {                               //���� ������
			puts("������� ������ (�������� 19 ��������)");
			while(1) {
				str[amount_of_syb] = _getch();
				if (str[amount_of_syb] == 8 && amount_of_syb != 0) {
					printf("\b \b");
					str[amount_of_syb] = NULL;
					amount_of_syb--;
					continue;
				}
				if (str[amount_of_syb] == 8 && amount_of_syb == 0)
					continue;
				if (str[amount_of_syb] == 13) {
					str[amount_of_syb] = '\0';
					break;
				}
				if (str[amount_of_syb] == 27)
					return 0;
				printf("*");
				amount_of_syb++;
			}
			if (strlen(str) < 20) {
				system("cls");
				decrypt(vedro.password);
				if (strcmp(str, vedro.password) == 0)
					return 1;
				else
				{
					system("cls");
					puts("��������� ��������� ������\n");
					puts("\n������� ����� ������� ����� ����������...");
					_getch();
					system("cls");
					break;
				}
			}
			else {
				system("cls");
				puts("������� ����� ��������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
			}
		}
	}
	else {
		system("cls");
		puts("��������� ��������� ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		fclose(file_1);
		return 0;
	}
}

int enter_user() {
	if (!(file_1 = fopen("users.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	system("cls");
	char *str;
	struct user vedro;
	while (1) {
		puts("������� ����� (�������� 19 ��������)");           //���� ������
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}


	int poisk = 0;
	fseek(file_1, 0, SEEK_END);
	if (ftell(file_1) > 0) {
		rewind(file_1);
		while (fread(&vedro, sizeof(struct user), 1, file_1) != 0) {      // //�������� ���� �� ������������ � ����� �������
			{
				if (vedro.role == 0) {
					decrypt(vedro.login);
					if (strcmp(str, vedro.login) == 0) {
						system("cls");
						poisk = 1;
						break;
					}
				}
			}
		}
	}

	int amount_of_syb = 0;
	if (poisk == 1) {
		while (1) {                               //���� ������
			puts("������� ������ (�������� 19 ��������)");
			while (1) {
				str[amount_of_syb] = _getch();
				if (str[amount_of_syb] == 8 && amount_of_syb != 0) {
					printf("\b \b");
					str[amount_of_syb] = NULL;
					amount_of_syb--;
					continue;
				}
				if (str[amount_of_syb] == 8 && amount_of_syb == 0)
					continue;
				if (str[amount_of_syb] == 13) {
					str[amount_of_syb] = '\0';
					break;
				}
				if (str[amount_of_syb] == 27)
					return 0;
				printf("*");
				amount_of_syb++;
			}
			if (strlen(str) < 20) {
				system("cls");
				decrypt(vedro.password);
				if (strcmp(str, vedro.password) == 0)
					return 1;
				else
				{
					system("cls");
					puts("��������� ��������� ������\n");
					puts("\n������� ����� ������� ����� ����������...");
					_getch();
					system("cls");
					break;
				}
			}
			else {
				system("cls");
				puts("������� ����� ��������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
			}
		}
	}
	else {
		system("cls");
		puts("��������� ��������� ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		fclose(file_1);
		return 0;
	}
}

void clear_stream() {
	while (getchar() != '\n');
}

void decrypt(char str[]) {
	char decrypt[20];
	char key[127] = "                                nopqrstuvwxyz{|} !\"#$%&'()*+,-./0956732184:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklm";
	for (int i = 0; i < strlen(str); i++)
	{
		for (int j = 0; j < strlen(key); j++)
			if (str[i] == key[j])
				decrypt[i] = (char)j;
	}
	decrypt[strlen(str)] = '\0';
	strcpy(str, decrypt);
}

int admin() {
	system("cls");
	while (1) {
		switch (admin_menu())
		{
		case 1: {
			system("cls");
			switch (menu_art_or_show()) {
			case 1: {
				system("cls");
				new_artist();
				break;
			}
			case 2: {
				system("cls");
				new_show();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
			break;
		}
		case 2: {
			system("cls");
			switch (menu_art_or_show()) {
			case 1: {
				system("cls");
				edit_artist();
				break;
			}
			case 2: {
				system("cls");
				edit_show();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
			break;
		}
		case 3: {
			system("cls");
			switch (menu_art_or_show()) {

			case 1: {
				system("cls");
				del_artist();
				break;
			}
			case 2: {
				system("cls");
				del_show();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
			break;
		}
		case 4: {
			system("cls");
			switch (menu_art_or_show()) {

			case 1: {
				system("cls");
				artist_output();
				break;
			}
			case 2: {
				system("cls");
				show_output();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
			break;
		}
		case 5: {
			system("cls");
			switch (menu_art_or_show()) {
			case 1: {
				system("cls");
				search();
				break;
			}
			case 2: {
				system("cls");
				search_s();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
			break;
		}
		case 6: {
			system("cls");
			users_config();
			break;
		}
		case 7: {
			system("cls");
			sort();
			break;
		}
		case 8: {
			system("cls");
			puts("-> ����������");
			puts("   ��������� ����");
			int choice;
			choice = menu_navigation(3);
			switch (choice) {
			case 1: {
				switch (menu_art_or_show()) {
				case 1: {
					system("cls");
					switch (menu_filtr_art()) {
					case 1: {
						system("cls");
						filtr_art_exr();
						break;
					}
					case 2: {
						system("cls");
						filtr_art_date();
						break;
					}
					case 3: {
						system("cls");
						filtr_art_solar();
						break;
					}
					case 4: {
						system("cls");
						break;
					}
					default: {
						system("cls");
						puts("��������� ��������� ������\n");
						puts("\n������� ����� ������� ����� ����������...");
						_getch();
						system("cls");
						break;
					}
					}
				}

				case 2: {
					switch (menu_filtr_show())
					{
					case 1: {
						system("cls");
						filtr_show_date();
						break;
					}
					case 2: {
						system("cls");
						filtr_show_solar();
						break;
					}
					case 3: {
						system("cls");
						break;
					}
					default: {
						system("cls");
						puts("��������� ��������� ������\n");
						puts("\n������� ����� ������� ����� ����������...");
						_getch();
						system("cls");
						break;
					}
					}
				}
				case 3: {
					system("cls");
					break;
				}
				default: {
					system("cls");
					puts("��������� ��������� ������\n");
					puts("\n������� ����� ������� ����� ����������...");
					_getch();
					system("cls");
					break;
				}
				}
			}
			case 2: {
				system("cls");
				set_role();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
		}
		case 9: {
			system("cls");
			return 0;
		}
		default: {
			system("cls");
			puts("��������� ��������� ������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			break;
		}
		}

		}
	}


int admin_menu() {
	int choice;
	system("cls");
	puts("-> �������� ������");
	puts("   ������������� ������");
	puts("   ������� ������");
	puts("   �������� ������");
	puts("   �����");
	puts("   ���������� ��������������");
	puts("   C��������� ������");
	puts("   �������");
	puts("   �����");
	choice = menu_navigation(9);
	return choice;
}

int menu_art_or_show() {
	int choice;
	system("cls");
	puts("-> �����");
	puts("   ���������");
	puts("   �����");
	choice = menu_navigation(3);
	return choice;
}

int menu_filtr_art() {
	int choice;
	system("cls");
	puts("-> �� �����");
	puts("   �� ����");
	puts("   �� ��������");
	puts("   �����");
	choice = menu_navigation(4);
	return choice;
}

int menu_filtr_show() {
	int choice;
	system("cls");
	puts("   �� ����");
	puts("   �� ������");
	puts("   �����");
	choice = menu_navigation(3);
	return choice;
}

int filtr_art_exr() {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);

	long int choice;
	puts("������� ���������� �����, ��������� ������ � ������� ��� ������\n");
	choice = enter_num();
	if (choice == NULL)
		return 0;

	system("cls");

	struct artist vedro;
	int i = 1;
	printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
	printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	while (fread(&vedro, sizeof(struct artist), 1, file_2) != 0) {
		if (choice >= vedro.exp) {
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
			i++;
		}
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_2);
	return 0;
}

int filtr_art_date() {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);

	long int choice[3];
	puts("������� ���� ��������\n");
	while (1) {
		puts("������� ����\n");
		choice[0] = enter_num();
		if (choice[0] == NULL)
			return 0;
		if (choice[0] >= 0 && choice[0] <= 31) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� �����\n");
		choice[1] = enter_num();
		if (choice[1] == NULL)
			return 0;
		if (choice[1] >= 0 && choice[1] <= 12) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ���\n");
		choice[2] = enter_num();
		if (choice[2] == NULL)
			return 0;
		if (choice[2] >= 2000 && choice[2] <= 3000) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	system("cls");

	system("cls");

	struct artist vedro;
	int i = 1;
	printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
	printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	while (fread(&vedro, sizeof(struct artist), 1, file_2) != 0) {
		if (choice[0] >= vedro.date[0] && choice[1] >= vedro.date[1] && choice[2] >= vedro.date[2]) {
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
			i++;
		}
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_2);
	return 0;
}

int filtr_art_solar() {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);

	long int choice;
	puts("������� ���������� ���������� �����, ��������� ������ � ������� ��� ������\n");
	choice = enter_num();
	if (choice == NULL)
		return 0;

	system("cls");

	struct artist vedro;
	int i = 1;
	printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
	printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	while (fread(&vedro, sizeof(struct artist), 1, file_2) != 0) {
		if (choice >= vedro.solar) {
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
			printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
			i++;
		}
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_2);
	return 0;
}

int filtr_show_date() {
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ���\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_3);

	long int choice[3];
	puts("������� ���� ��������\n");
	while (1) {
		puts("������� ����\n");
		choice[0] = enter_num();
		if (choice[0] == NULL)
			return 0;
		if (choice[0] >= 0 && choice[0] <= 31) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� �����\n");
		choice[1] = enter_num();
		if (choice[1] == NULL)
			return 0;
		if (choice[1] >= 0 && choice[1] <= 12) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ���\n");
		choice[2] = enter_num();
		if (choice[2] == NULL)
			return 0;
		if (choice[2] >= 2000 && choice[2] <= 3000) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	system("cls");

	system("cls");

	struct show vedro;
	int i = 1;
	printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
	printf("-----|-------------------|-------------------|----------------|------------\n");
	while (fread(&vedro, sizeof(struct show), 1, file_3) != 0) {
		if (choice[0] >= vedro.date[0] && choice[1] >= vedro.date[1] && choice[2] >= vedro.date[2]) {
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.%2d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| %2d.%2d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| %2d.0%1d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			printf("-----|-------------------|-------------------|----------------|------------\n");
			i++;
		}
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_3);
	return 0;
}

int filtr_show_solar() {
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_3);

	long int choice;
	puts("������� �������� ������ �� ����, ��������� ���� � ������� ��� ������\n");
	choice = enter_num();
	if (choice == NULL)
		return 0;

	system("cls");

	struct show vedro;
	int i = 1;
	printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
	printf("-----|-------------------|-------------------|----------------|------------\n");
	while (fread(&vedro, sizeof(struct show), 1, file_3) != 0) {
		if (choice >= vedro.payment) {
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.%2d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
				printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| %2d.%2d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| %2d.0%1d.000%1d\n", i, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
			printf("-----|-------------------|-------------------|----------------|------------\n");
			i++;
		}
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_3);
	return 0;
}

int user() {
	system("cls");
	while (1) {
		switch (user_menu())
		{
		case 1: {
			system("cls");
			switch (menu_art_or_show()) {

			case 1: {
				system("cls");
				artist_output();
				break;
			}
			case 2: {
				system("cls");
				show_output();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
			break;
		}
		case 2: {
			system("cls");
			sort();
			break;
		}
		case 3: {
			system("cls");
			switch (menu_art_or_show()) {
			case 1: {
				system("cls");
				search();
				break;
			}
			case 2: {
				system("cls");
				search_s();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
			break;
		}
		case 4: {
			system("cls");
			puts("-> ����������");
			puts("   ��������� ����");
			int choice;
			choice = menu_navigation(3);
			switch (choice) {
			case 1: {
				switch (menu_art_or_show()) {
				case 1: {
					system("cls");
					switch (menu_filtr_art()) {
					case 1: {
						system("cls");
						filtr_art_exr();
						break;
					}
					case 2: {
						system("cls");
						filtr_art_date();
						break;
					}
					case 3: {
						system("cls");
						filtr_art_solar();
						break;
					}
					case 4: {
						system("cls");
						break;
					}
					default: {
						system("cls");
						puts("��������� ��������� ������\n");
						puts("\n������� ����� ������� ����� ����������...");
						_getch();
						system("cls");
						break;
					}
					}
				}

				case 2: {
					switch (menu_filtr_show())
					{
					case 1: {
						system("cls");
						filtr_show_date();
						break;
					}
					case 2: {
						system("cls");
						filtr_show_solar();
						break;
					}
					case 3: {
						system("cls");
						break;
					}
					default: {
						system("cls");
						puts("��������� ��������� ������\n");
						puts("\n������� ����� ������� ����� ����������...");
						_getch();
						system("cls");
						break;
					}
					}

				case 3: {
					system("cls");
					break;
				}
				default: {
					system("cls");
					puts("��������� ��������� ������\n");
					puts("\n������� ����� ������� ����� ����������...");
					_getch();
					system("cls");
					break;
				}
				}
				}
			}
			case 2: {
				system("cls");
				set_role();
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			default: {
				system("cls");
				puts("��������� ��������� ������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
				break;
			}
			}
		}
		case 5: {
			system("cls");
			break;
		}
		default: {
			system("cls");
			puts("��������� ��������� ������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			break;
		}
		}
		return 0;
	}
}

int user_menu() {
	int choice;
	puts("-> �������� ������");
	puts("   ���������� ������");
	puts("   �����");
	puts("   �������");
	puts("   �����");
	choice = menu_navigation(5);
	return choice;
}

int users_output() {
	if (!(file_1 = fopen("users.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_1, 0, SEEK_END);
	if (ftell(file_1) <= 0)
	{
		fclose(file_1);
		puts("��� �� ������ ������������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	struct user vedro;
	rewind(file_1);
	int i = 1;
	printf("  �  |       �����       |  �����  \n");
	printf("-----|-------------------|---------\n");
	while (fread(&vedro, sizeof(struct user), 1, file_1) != 0)
	{
		decrypt(vedro.login);
		printf("%5d|%19s|%9s\n", i, vedro.login, (vedro.role) ? "admin" : "user");
		printf("-----|-------------------|---------\n");
		i++;
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_1);
	return 0;
}

int users_config() {
	while (1) {
		switch (users_config_menu()) {
		case 1: {
			system("cls");
			users_output();
			break;
		}
		case 2: {
			system("cls");
			new_user();
			break;
		}
		case 3: {
			system("cls");
			del_user();
			break;
		}
		case 4: {
			system("cls");
			return 0;
		}
		default: {
			system("cls");
			puts("��������� ��������� ������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			break;
		}
		}
	}
}

int users_config_menu() {
	int choice;
	system("cls");
	puts("-> �������� �������������");
	puts("   �������� �������������");
	puts("   ������� ������������");
	puts("   �����");
	choice = menu_navigation(4);
	return choice;
}

int del_user() {
	if (!(file_1 = fopen("users.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_1, 0, SEEK_END);
	if (ftell(file_1) <= 0)
	{
		fclose(file_1);
		puts("��� �� ������ ������������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_1);
	int choice;
	int	n = _filelength(_fileno(file_1)) / sizeof(struct user);
	struct user* spisok;
	spisok = (struct user*)malloc(n * sizeof(struct user));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct user), 1, file_1);
	fclose(file_1);
	printf("  �  |       �����       |  �����  \n");
	printf("-----|-------------------|---------\n");
	for (int i = 0; i < n; i++) {
		decrypt(spisok[i].login);
		printf("%5d|%19s|%9s\n", i + 1, spisok[i].login, (spisok[i].role) ? "admin" : "user");
		printf("-----|-------------------|---------\n");
	}
	while (1) {
		puts("������� ����� ������, ������� ���� �������\n");
		choice = enter_num();
		if (choice == NULL)
			return 0;
		if (choice >= 1 && choice <= n) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ � ����� ������� ���\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}

	if (!(file_1 = fopen("users.txt", "w+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	if (n != choice) {
		for (int i = choice - 1; i < n - 1; i++)
			spisok[i] = spisok[i + 1];
	}
	char key[127] = "                                nopqrstuvwxyz{|} !\"#$%&'()*+,-./0956732184:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklm";
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < strlen(spisok[i].login); j++) // �������� ������
			spisok[i].login[j] = key[spisok[i].login[j]];
		fwrite(&spisok[i], sizeof(struct user), 1, file_1);
	}

	fclose(file_1);
	free(spisok);
	puts("������\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	return 0;
}

int new_artist() {
	char *str;
	char s[20] = "                  ";
	char s1[20] = "                  ";
	system("cls");
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("����� �� ���� ����������\n����� ������ ����� ����\n");
		file_2 = fopen("artists.txt", "w+b");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	struct artist new_artist;
	while (1) {
		puts("������� ��� (�������� 19 ��������)");
		if (!(str = enter_syb_name()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(new_artist.name, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ������� (�������� 19 ��������)");
		if (!(str = enter_syb_name()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(new_artist.sec_name, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� �������� (�������� 19 ��������)");
		if (!(str = enter_syb_name()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(new_artist.patr, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ����\n");
		new_artist.exp = enter_num();
		if (new_artist.exp == NULL)
			return 0;
		if (new_artist.exp > 0 && new_artist.exp < 100) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ����\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	strcpy(new_artist.show, s);
	strcpy(new_artist.role, s1);
	new_artist.date[0] = 0;
	new_artist.date[1] = 0;
	new_artist.date[2] = 0;
	new_artist.solar = 0;
	system("cls");
	fseek(file_2, 0, SEEK_END);
	fwrite(&new_artist, sizeof(struct artist), 1, file_2); //������ ����� � ����
	fclose(file_2);    //�������� �����
	return 0;
}

int artist_output() {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);
	struct artist vedro;
	int i = 1;
	printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
	printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	while (fread(&vedro, sizeof(struct artist), 1, file_2) != 0) {
		if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
		printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
		i++;
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_2);
	return 0;
}

int del_artist()  {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);
	int choice, n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc(n * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	fclose(file_2);
	printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
	printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	for (int i = 0; i < n; i++) {
		if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i + 1,  spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	}
	while (1) {
		puts("������� ����� ������, ������� ���� �������\n");
		choice = enter_num();
		if (choice == NULL)
			return 0;
		if (choice >= 1 && choice <= n) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ � ����� ������� ���\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}



	if (!(file_2 = fopen("artists.txt", "w+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	if (n != choice) {
		for (int i = choice - 1; i < n - 1; i++)
			spisok[i] = spisok[i + 1];
	}
	for (int i = 0; i < n - 1; i++) {
		fwrite(&spisok[i], sizeof(struct artist), 1, file_2);
	}

	fclose(file_2);
	free(spisok);
	puts("������\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	return 0;
}

int edit_artist() {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);

	int choice, n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc(n * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	fclose(file_2);
	printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
	printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	for (int i = 0; i < n; i++) {
		if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	}
	while (1) {
		puts("������� ����� ������, ������� ���� ���������������\n");
		choice = enter_num();
		if (choice == NULL)
			return 0;
		if (choice >= 1 && choice <= n) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ � ����� ������� ���\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}

	system("cls");
	char* str;
	while (1) {
		puts("������� ��� (�������� 19 ��������)");
		if (!(str = enter_syb_name()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(spisok[choice - 1].name, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ������� (�������� 19 ��������)");
		if (!(str = enter_syb_name()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(spisok[choice - 1].sec_name, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� �������� (�������� 19 ��������)");
		if (!(str = enter_syb_name()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(spisok[choice - 1].patr, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ����\n");
		spisok[choice - 1].exp = enter_num();
		if (spisok[choice - 1].exp == NULL)
			return 0;
		if (spisok[choice - 1].exp > 0 && spisok[choice - 1].exp < 100) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ����\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	if (!(file_2 = fopen("artists.txt", "w+b"))) {
		puts("�� ������� ������� ����\n");
		_getch();
		return 0;
	}
	for (int i = 0; i < n; i++) {
		fwrite(&spisok[i], sizeof(struct artist), 1, file_2);
	}
	fclose(file_2);
	free(spisok);
	puts("������\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	return 0;
}

int search() {
	while (1) {
		switch (search_menu()) {
		case 1: {
			system("cls");
			search_sec_name();
			break;
		}
		case 2: {
			system("cls");
			search_name();
			break;
		}
		case 3: {
			system("cls");
			search_patr();
			break;
		}
		case 4: {
			system("cls");
			search_exp();
			break;
		}
		case 5: {
			system("cls");
			return 0;
		}
		default: {
			system("cls");
			puts("��������� ��������� ������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			break;
		}
		}
	}
}

int search_s() {
	while (1) {
		switch (search_show_menu()) {
		case 1: {
			system("cls");
			search_show();
			break;
		}
		case 2: {
			system("cls");
			search_role();
			break;
		}
		case 3: {
			system("cls");
			return 0;
		}
		default: {
			system("cls");
			puts("��������� ��������� ������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			break;
		}
		}
	}
}

int search_menu() {
	int choice;
	system("cls");
	puts("-> �������");
	puts("   ���");
	puts("   ��������");
	puts("   ����");
	puts("   �����");
	choice = menu_navigation(5);
	return choice;
}

int search_show_menu() {
	int choice;
	system("cls");
	puts("-> ���������");
	puts("   ����");
	puts("   �����");
	choice = menu_navigation(3);
	return choice;
}

int search_sec_name() {
	char *str;
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);
	int n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc(n * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	while (1) {
		puts("������� ������� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	int poisk = 1;
	for (int i = 0; i < n; i++) {
		if (strcmp(str, spisok[i].sec_name) == 0) {
			if (poisk == 1) {
				printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
				printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
				poisk--;
			}
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
		}
	}
	if (poisk == 0) {
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	else {
		puts("������ ������ �� �������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	fclose(file_2);
	return 0;
}

int search_name() {
	char *str;
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);
	int n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc(n * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	while (1) {
		puts("������� ��� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	int poisk = 1;
	for (int i = 0; i < n; i++) {
		if (strcmp(str, spisok[i].name) == 0) {
			if (poisk == 1) {
				printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
				printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
				poisk--;
			}
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
		}
	}
	if (poisk == 0) {
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	else {
		puts("������ ������ �� �������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	fclose(file_2);
	return 0;
}

int search_patr() {
	char *str;
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);
	int n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc(n * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	while (1) {
		puts("������� �������o (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	int poisk = 1;
	for (int i = 0; i < n; i++) {
		if (strcmp(str, spisok[i].patr) == 0) {
			if (poisk == 1) {
				printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
				printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
				poisk--;
			}
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
		}
	}
	if (poisk == 0) {
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	else {
		puts("������ ������ �� �������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	fclose(file_2);
	return 0;
}

int search_exp() {
	int chislo;
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);
	int n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc(n * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	while (1) {
		puts("������� ����\n");
		chislo = enter_num();
		if (chislo == NULL)
			return 0;
		if (chislo > 0 && chislo < 100) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ����\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	system("cls");
	int poisk = 1;
	for (int i = 0; i < n; i++) {
		if (chislo == spisok[i].exp) {
			if (poisk == 1) {
				printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
				printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
				poisk--;
			}
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i + 1, spisok[i].sec_name, spisok[i].name, spisok[i].patr, spisok[i].exp, spisok[i].solar, spisok[i].show, spisok[i].role, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
		}
	}
	if (poisk == 0) {
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	else {
		puts("������ ������ �� �������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	return 0;
}

int new_show() {
	char *str;
	system("cls");
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("����� �� ���� ����������\n����� ������ ����� ����\n");
		file_3 = fopen("shows.txt", "w+b");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	struct show new_show;
	while (1) {
		puts("������� �������� ��������� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(new_show.show, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ������� ���� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(new_show.role, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ����� �� ����\n");
		new_show.payment = enter_num();
		if (new_show.payment == NULL)
			return 0;

		if (new_show.payment >= 0) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	puts("������� ���� ��������\n");
	while (1) {
		puts("������� ����\n");
		new_show.date[0] = enter_num();
		if (new_show.date[0] == NULL)
			return 0;
			if (new_show.date[0] >= 0 && new_show.date[0] <= 31) {
				system("cls");
				break;
			}
			else {
				system("cls");
				puts("������ ������ ����� ��������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
			}
	}
	while (1) {
		puts("������� �����\n");
		new_show.date[1] = enter_num();
		if (new_show.date[1] == NULL)
			return 0;
		if (new_show.date[1] >= 0 && new_show.date[1] <= 12) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ���\n");
		new_show.date[2] = enter_num();
		if (new_show.date[2] == NULL)
			return 0;
		if (new_show.date[2] >= 2000 && new_show.date[2] <= 3000) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	system("cls");
	fseek(file_3, 0, SEEK_END);
	fwrite(&new_show, sizeof(struct show), 1, file_3); //������ ����� � ����
	fclose(file_3);    //�������� �����
	return 0;
}

int show_output() {
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ���������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_3);
	struct show vedro;
	int i = 1;
	printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
	printf("-----|-------------------|-------------------|----------------|------------\n");
	while (fread(&vedro, sizeof(struct show), 1, file_3) != 0) {
		if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.%2d.000%1d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.000%1d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| %2d.%2d.000%1d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| %2d.0%1d.000%1d\n", i + 1, vedro.show, vedro.role, vedro.payment, vedro.date[0], vedro.date[1], vedro.date[2]);
		printf("-----|-------------------|-------------------|----------------|------------\n");
		i++;

	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_3);
	return 0;
}

int del_show() {
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ���������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_3);
	int choice, n = _filelength(_fileno(file_3)) / sizeof(struct show);
	struct show* spisok;
	spisok = (struct show*)malloc(n * sizeof(struct show));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct show), 1, file_3);
	fclose(file_3);
	printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
	printf("-----|-------------------|-------------------|----------------|------------\n");
	for (int i = 0; i < n; i++) {
		if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9)
			printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[1] < 10 && spisok[i].date[0] > 9)
			printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[1] < 10 && spisok[i].date[0] < 10)
			printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[1] > 9 && spisok[i].date[0] > 9)
			printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| %2d.%2d.000%1d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		printf("-----|-------------------|-------------------|----------------|------------\n");
	}
	while (1) {
		puts("������� ����� ������, ������� ���� �������\n");
		choice = enter_num();
		if (choice == NULL)
			return 0;
		if (choice >= 1 && choice <= n) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ � ����� ������� ���\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}



	if (!(file_2 = fopen("shows.txt", "w+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	if (n != choice) {
		for (int i = choice - 1; i < n - 1; i++)
			spisok[i] = spisok[i + 1];
	}
	for (int i = 0; i < n - 1; i++) {
		fwrite(&spisok[i], sizeof(struct show), 1, file_3);
	}

	fclose(file_3);
	free(spisok);
	puts("������\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	return 0;
}

int edit_show() {
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_3);

	int choice, n = _filelength(_fileno(file_3)) / sizeof(struct show);
	struct show* spisok;
	spisok = (struct show*)malloc(n * sizeof(struct show));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct show), 1, file_3);
	fclose(file_3);
	printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
	printf("-----|-------------------|-------------------|----------------|------------\n");
	for (int i = 0; i < n; i++) {
		if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i  + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.%2d.000%1d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] < 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.000%1d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] >= 2000)
			printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] > 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| %2d.%2d.000%1d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		if (spisok[i].date[0] > 10 && spisok[i].date[1] < 9 && spisok[i].date[2] < 2000)
			printf("%5d|%19s|%19s|%16d| %2d.0%1d.000%1d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
		printf("-----|-------------------|-------------------|----------------|------------\n");
	}
	while (1) {
		puts("������� ����� ������, ������� ���� �������\n");
		choice = enter_num();
		if (choice == NULL)
			return 0;
		if (choice >= 1 && choice <= n) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ � ����� ������� ���\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}

	system("cls");
	char *str;
	while (1) {
		puts("������� �������� ��������� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(spisok[choice - 1].show, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� �������� ���� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			strcpy(spisok[choice - 1].role, str);
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� �������� �������\n");
		spisok[choice - 1].payment = enter_num();
		if (spisok[choice - 1].payment == NULL)
			return 0;
			if (spisok[choice - 1].payment > 0) {
				system("cls");
				break;
			}
			else {
				system("cls");
				puts("������ ������ ����� ��������\n");
				puts("\n������� ����� ������� ����� ����������...");
				_getch();
				system("cls");
			}
	}
	puts("������� ���� ��������\n");
	while (1) {
		puts("������� ����\n");
		spisok[choice - 1].date[0] = enter_num();
		if (spisok[choice - 1].date[0] == NULL)
			return 0;
		if (spisok[choice - 1].date[0] >= 0 && spisok[choice - 1].date[0] <= 31) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� �����\n");
		spisok[choice - 1].date[1] = enter_num();
		if (spisok[choice - 1].date[1] == NULL)
			return 0;
		if (spisok[choice - 1].date[1] >= 0 && spisok[choice - 1].date[1] <= 12) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	while (1) {
		puts("������� ���\n");
		spisok[choice - 1].date[2] = enter_num();
		if (spisok[choice - 1].date[2] == NULL)
			return 0;
		if (spisok[choice - 1].date[2] >= 2000 && spisok[choice - 1].date[2] <= 3000) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������ ������ ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	system("cls");
	if (!(file_3 = fopen("shows.txt", "w+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		fwrite(&spisok[i], sizeof(struct show), 1, file_3);
	}
	fclose(file_3);
	free(spisok);
	puts("������\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	return 0;
}

int search_show() {
	char* str;
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ���������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_3);
	int n = _filelength(_fileno(file_3)) / sizeof(struct show);
	struct show* spisok;
	spisok = (struct show*)malloc(n * sizeof(struct show));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct show), 1, file_3);
	while (1) {
		puts("������� �������� ��������� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	int poisk = 1;
	for (int i = 0; i < n; i++) {
		if (strcmp(str, spisok[i].show) == 0) {
			if (poisk == 1) {
				printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
				printf("-----|-------------------|-------------------|----------------|------------\n");
				poisk--;
			}
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9)
				printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[1] < 10 && spisok[i].date[0] > 9)
				printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[1] < 10 && spisok[i].date[0] < 10)
				printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[1] > 9 && spisok[i].date[0] > 9)
				printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[2] < 2000)
				printf("%5d|%19s|%19s|%16d| %2d.%2d.000%1d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			printf("-----|-------------------|-------------------|----------------|------------\n");
		}
	}
	if (poisk == 0) {
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	else {
		puts("������ ��������� �� �������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	fclose(file_2);
	return 0;
}

int search_role() {
	char* str;
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ���������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_3);
	int n = _filelength(_fileno(file_3)) / sizeof(struct show);
	struct show* spisok;
	spisok = (struct show*)malloc(n * sizeof(struct show));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct show), 1, file_3);
	while (1) {
		puts("������� �������� ���� (�������� 19 ��������)");
		if (!(str = enter_syb()))
			return 0;
		if (strlen(str) < 20) {
			system("cls");
			break;
		}
		else {
			system("cls");
			puts("������� ����� ��������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
		}
	}
	int poisk = 1;
	for (int i = 0; i < n; i++) {
		if (strcmp(str, spisok[i].role) == 0) {
			if (poisk == 1) {
				printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
				printf("-----|-------------------|-------------------|----------------|------------\n");
				poisk--;
			}
			if (spisok[i].date[0] < 10 && spisok[i].date[1] > 9)
				printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[1] < 10 && spisok[i].date[0] > 9)
				printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[1] < 10 && spisok[i].date[0] < 10)
				printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			if (spisok[i].date[1] > 9 && spisok[i].date[0] > 9)
				printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i + 1, spisok[i].show, spisok[i].role, spisok[i].payment, spisok[i].date[0], spisok[i].date[1], spisok[i].date[2]);
			printf("-----|-------------------|-------------------|----------------|------------\n");
		}
	}
	if (poisk == 0) {
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	else {
		puts("������ ��������� �� �������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
	}
	fclose(file_2);
	return 0;
}

int set_role() {
	int f_artist, f_show;
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		return 0;
	}
	rewind(file_2);
	struct artist vedro;
	int i = 1;
	
	printf("  �  |      �������      |        ���        |     ��������      | ���� | �������� |     ���������     |        ����       |     ����   \n");
	printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
	while (fread(&vedro, sizeof(struct artist), 1, file_2) != 0) {
		if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] < 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| 0%1d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] >= 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.%4d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] > 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.%2d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		if (vedro.date[0] > 10 && vedro.date[1] < 9 && vedro.date[2] < 2000)
			printf("%5d|%19s|%19s|%19s|%6d|%10d|%19s|%19s| %2d.0%1d.000%1d\n", i, vedro.sec_name, vedro.name, vedro.patr, vedro.exp, vedro.solar, vedro.show, vedro.role, vedro.date[0], vedro.date[1], vedro.date[2]);
		printf("-----|-------------------|-------------------|-------------------|------|----------|-------------------|-------------------|------------\n");
		i++;
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	fclose(file_2);


	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ���������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		return 0;
	}
	rewind(file_3);
	struct show bin;
	i = 1;
	printf("  �  |     ���������     |        ����       |     �����      |     ����   \n");
	printf("-----|-------------------|-------------------|----------------|------------\n");
	while (fread(&bin, sizeof(struct show), 1, file_3) != 0) {
		if (bin.date[0] < 10 && bin.date[1] > 9)
			printf("%5d|%19s|%19s|%16d| 0%1d.%2d.%4d\n", i, bin.show, bin.role, bin.payment, bin.date[0], bin.date[1], bin.date[2]);
		if (bin.date[1] < 10 && bin.date[0] > 9)
			printf("%5d|%19s|%19s|%16d| %2d.0%1d.%4d\n", i, bin.show, bin.role, bin.payment, bin.date[0], bin.date[1], bin.date[2]);
		if (bin.date[1] < 10 && bin.date[0] < 10)
			printf("%5d|%19s|%19s|%16d| 0%1d.0%1d.%4d\n", i, bin.show, bin.role, bin.payment, bin.date[0], bin.date[1], bin.date[2]);
		if (bin.date[1] > 9 && bin.date[0] > 9)
			printf("%5d|%19s|%19s|%16d| %2d.%2d.%4d\n", i, bin.show, bin.role, bin.payment, bin.date[0], bin.date[1], bin.date[2]);
		printf("-----|-------------------|-------------------|----------------|------------\n");
		i++;
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	fclose(file_3);


	int chislo;
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		return 0;
	}
	char str[20];
	rewind(file_2);
	int n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc(n * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	while (1) {
		puts("\n������� ����� �������\n");
		chislo = enter_num();
		if (chislo == NULL)
			return 0;
		if (chislo >= 1 && chislo <= n) {
		
			break;
		}
		else {
			system("cls");
			puts("������ � ����� ������� ���\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			
		}
	}

	int chislo1;
	if (!(file_3 = fopen("shows.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		return 0;
	}
	fseek(file_3, 0, SEEK_END);
	if (ftell(file_3) <= 0)
	{
		fclose(file_3);
		puts("��� �� ������ ���������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		return 0;
	}
	rewind(file_3);
	int m = _filelength(_fileno(file_3)) / sizeof(struct show);
	struct show* spisok1;
	spisok1 = (struct show*)malloc(m * sizeof(struct show));
	for (int j = 0; j < m; j++)
		fread(&spisok1[j], sizeof(struct show), 1, file_3);
	while (1) {
		puts("\n������� ����� ���������\n");
		chislo1 = enter_num();
		if (chislo1 == NULL)
			return 0;
		if (chislo1 >= 1 && chislo1 <= m) {
			break;
		}
		else {
			system("cls");
			puts("������ � ����� ������� ���\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
		}
	}

	strcpy(spisok[chislo - 1].show, spisok1[chislo1 - 1].show);
	strcpy(spisok[chislo - 1].role, spisok1[chislo1 - 1].role);
	spisok[chislo - 1].solar = spisok1[chislo1 - 1].payment;
	spisok[chislo - 1].date[0] = spisok1[chislo1 - 1].date[0];
	spisok[chislo - 1].date[1] = spisok1[chislo1 - 1].date[1];
	spisok[chislo - 1].date[2] = spisok1[chislo1 - 1].date[2];
	rewind(file_2);

	for (int i = 0; i < n; i++) {
		fwrite(&spisok[i], sizeof(struct artist), 1, file_2);
	}
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	fclose(file_2);
	fclose(file_3);
	free(spisok);
	free(spisok1);
	system("cls");
	return 0;
}

char* enter_syb() {
	static char string[3000];
	int amount_of_syb = 0;
	while (1) {
		string[amount_of_syb] = _getch();
		if (string[amount_of_syb] == 8 && amount_of_syb != 0) {
			printf("\b \b");
			string[amount_of_syb] = NULL;
			amount_of_syb--;
			continue;
		}
		if (string[amount_of_syb] == 8 && amount_of_syb == 0)
			continue;
		if (string[amount_of_syb] == 13) {
			string[amount_of_syb] = '\0';
			break;
		}
		if (string[amount_of_syb] == 27)
			return 0;
		printf("%c", string[amount_of_syb]);
		amount_of_syb++;
	}
	return string;
}

char* enter_syb_name() {
	
	static char string[3000];
	int amount_of_syb = 0;
	while (1) {
		string[amount_of_syb] = _getch();
		if (string[amount_of_syb] == 8 && amount_of_syb != 0) {
			printf("\b \b");
			string[amount_of_syb] = NULL;
			amount_of_syb--;
			continue;
		}
		if (string[amount_of_syb] == 8 && amount_of_syb == 0)
			continue;
		if (string[amount_of_syb] == 13) {
			string[amount_of_syb] = '\0';
			break;
		}
		if (string[amount_of_syb] == 27)
			return 0;
		if ((string[amount_of_syb] == 45) || (string[amount_of_syb] >= 65 && string[amount_of_syb] <= 90) || (string[amount_of_syb] >= 97 && string[amount_of_syb] <= 122) || (string[amount_of_syb] <= 0) || (string[amount_of_syb] == 168) || (string[amount_of_syb] == 184) || (string[amount_of_syb] == 46)) {
			printf("%c", string[amount_of_syb]);
			amount_of_syb++;
		}
	}
	return string;
}

int enter_num() {
	COORD position;
	POINT pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char syb;
	long int num;
	num = 0;
	do {
		syb = _getch();
		GetCursorPos(&pos);
		if (syb == 8 && pos.x != 1) {
			printf("\b \b");
			num = num / 10;
			continue;
		}
		if (syb == 8 && pos.x == 1)
			continue;
		if (syb == 27)
			return NULL;
		if (syb >= 48 && syb <= 57) {
				printf("%c", syb);
				num = (num * 10) + (syb - 48);
		}
	} while (syb != 13);
	return num;
}

int sort() {
	system("cls");
	while (1) {
		switch (sort_menu())
		{
		case 1: {
			system("cls");
			sort_solar();
			break;
		}
		case 2: {
			system("cls");
			sort_date();
			break;
		}
		case 3: {
			system("cls");
			return 0;
		}
		default: {
			system("cls");
			puts("��������� ��������� ������\n");
			puts("\n������� ����� ������� ����� ����������...");
			_getch();
			system("cls");
			break;
		}
		}
	}
	return 0;
}

int sort_menu() {
	int choice;
	system("cls");
	puts("-> ��������");
	puts("   ����");
	puts("   �����");
	choice = menu_navigation(3);
	return choice;
}

int sort_solar() {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	

	int choice, n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	rewind(file_2);
	spisok = (struct artist*)malloc((n + 1) * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	fclose(file_2);
	for (int counter = 0; counter < n - 1 ; counter++) {
		for (int counter_helper = 0; counter_helper < n - counter - 1; counter_helper++) {
			if (spisok[counter_helper].solar < spisok[counter_helper + 1].solar) {
				spisok[n] = spisok[counter_helper];
				spisok[counter_helper] = spisok[counter_helper + 1];
				spisok[counter_helper + 1] = spisok[n];
			}
		}
	}
	if (!(file_2 = fopen("artists.txt", "w+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		fwrite(&spisok[i], sizeof(struct artist), 1, file_2);
	}
	fclose(file_2);
	free(spisok);
	puts("������\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	return 0;
}

int sort_date() {
	if (!(file_2 = fopen("artists.txt", "r+b"))) {
		puts("�� ������� ������� ����\n");
		return 0;
	}
	fseek(file_2, 0, SEEK_END);
	if (ftell(file_2) <= 0)
	{
		fclose(file_2);
		puts("��� �� ������ ������\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	rewind(file_2);

	int choice, n = _filelength(_fileno(file_2)) / sizeof(struct artist);
	struct artist* spisok;
	spisok = (struct artist*)malloc((n + 1) * sizeof(struct artist));
	for (int i = 0; i < n; i++)
		fread(&spisok[i], sizeof(struct artist), 1, file_2);
	fclose(file_2);
	for (int counter = 0; counter < n - 1; counter++) {
		for (int counter_helper = 0; counter_helper < n - counter - 1; counter_helper++) {
			if (spisok[counter_helper].date[2] < spisok[counter_helper + 1].date[2]) {
				spisok[n] = spisok[counter_helper];
				spisok[counter_helper] = spisok[counter_helper + 1];
				spisok[counter_helper + 1] = spisok[n];
			}
		}
	}
	for (int counter = 0; counter < n - 1; counter++) {
		for (int counter_helper = 0; counter_helper < n - counter - 1; counter_helper++) {
			if ((spisok[counter_helper].date[1] < spisok[counter_helper + 1].date[1]) && (spisok[counter_helper].date[2] == spisok[counter_helper + 1].date[2])) {
				spisok[n] = spisok[counter_helper];
				spisok[counter_helper] = spisok[counter_helper + 1];
				spisok[counter_helper + 1] = spisok[n];
			}
		}
	}
	for (int counter = 0; counter < n - 1; counter++) {
		for (int counter_helper = 0; counter_helper < n - counter - 1; counter_helper++) {
			if ((spisok[counter_helper].date[0] < spisok[counter_helper + 1].date[0]) && (spisok[counter_helper].date[2] == spisok[counter_helper + 1].date[2]) && (spisok[counter_helper].date[1] == spisok[counter_helper + 1].date[1])) {
				spisok[n] = spisok[counter_helper];
				spisok[counter_helper] = spisok[counter_helper + 1];
				spisok[counter_helper + 1] = spisok[n];
			}
		}
	}
	if (!(file_2 = fopen("artists.txt", "w+b"))) {
		puts("�� ������� ������� ����\n");
		puts("\n������� ����� ������� ����� ����������...");
		_getch();
		system("cls");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		fwrite(&spisok[i], sizeof(struct artist), 1, file_2);
	}
	fclose(file_2);
	free(spisok);
	puts("������\n");
	puts("\n������� ����� ������� ����� ����������...");
	_getch();
	system("cls");
	return 0;
};








