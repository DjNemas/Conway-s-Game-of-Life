#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>

using namespace std;


// User Choice
int user_Gamefield_Height(int gamefield_height);
int user_Gamefield_Width(int gamefield_width);
int user_Generation(int generation_user);
int user_Rnd_Seed(int user_seed);
bool user_Show_Grafik_Buffer();
int User_Fps_Input(int user_fps);
// Create Dynamic GameField Array
char*** Create_GameFieldDynArray(int grafik_buffer, int gamefield_height, int gamefield_width);
void Delete_GameFieldDynArray(char*** gameFieldDynArray, int grafik_buffer, int gamefield_height, int gamefield_width);
// For Field
int CurrentBuffer(int grafik_buffer);
void GenerateField(char*** gameFieldDynArray, int gamefield_height, int gamefield_width, int user_seed);
void ShowField(string gamefield, char*** gamefieldArray, int grafik_buffer, int show_buffer, int gamefield_height, int gamefield_width, int generation, int user_fps);
// Siumaltion Calculation
void Start_Simulation(int grafik_buffer, char*** gameFieldDynArray, int gamefield_height, int gamefield_width);


int main()
{	
	
	// Gamefield height and width
	int grafik_buffer = 2;
	bool show_buffer = false;
	int gamefield_height = 0;
	int gamefield_width = 0;
	int test = 0;
	int generation = 0;
	int user_seed = 0;
	int user_fps = 0;

	/// Ask User Inputs
	//
	cout << "Fuer das besste Spielerlebniss, stelle bei FHD Aufloesung die Konsole auf Schriftgroesse 14 und Schriftart Consolas und maximiere dein Fenster auf Vollbild.\n";
	gamefield_height = user_Gamefield_Height(gamefield_height);
	gamefield_width = user_Gamefield_Width(gamefield_width);
	show_buffer = user_Show_Grafik_Buffer();
	user_seed = user_Rnd_Seed(user_seed);
	user_fps = User_Fps_Input(user_fps);
	/// Init Dynamic GameField Array
	//
	char*** gameFieldDynArray = Create_GameFieldDynArray(grafik_buffer,gamefield_height,gamefield_width);
	/// Fill Char to GameArray
	//
	GenerateField(gameFieldDynArray, gamefield_height, gamefield_width, user_seed);
	/// Show Gamefield
	//
	string gamefield = "";
	grafik_buffer = CurrentBuffer(grafik_buffer);
	ShowField(gamefield, gameFieldDynArray, grafik_buffer, show_buffer, gamefield_height, gamefield_width, generation, user_fps);
	int generation_user = 0;
	generation_user = user_Generation(generation_user);
	char user_input = ' ';
	do
	{

		for (int i = 0; i < generation_user; i++)
		{
			generation++;
			grafik_buffer = CurrentBuffer(grafik_buffer);
			Start_Simulation(grafik_buffer, gameFieldDynArray, gamefield_height, gamefield_width);
			ShowField(gamefield, gameFieldDynArray, grafik_buffer, show_buffer, gamefield_height, gamefield_width, generation, user_fps);
		}

		cout << "\n Moechtest du noch mehr Generationen sehen oder das Spiel beenden? (j/n)";
		cin >> user_input;
		if (user_input == 'j' || user_input == 'y')
		{
			cout << "\n Wie viele Generationen willst du sehen? ";
			cin >> generation_user;
		}

	} while (user_input == 'j' || user_input == 'y');
	
	/// Delete Dynamic Array
	//
	Delete_GameFieldDynArray( gameFieldDynArray, 2, gamefield_height, gamefield_width);
	return 0;

}
int CurrentBuffer(int grafik_buffer)
{
	grafik_buffer = (grafik_buffer + 1) % 2;
	return grafik_buffer;

}

char*** Create_GameFieldDynArray(int grafik_buffer, int gamefield_height, int gamefield_width)
{
	char*** gameFieldDynArray = new char** [grafik_buffer];
	for (int i = 0; i < grafik_buffer; i++)
	{
		gameFieldDynArray[i] = new char* [gamefield_height];
		for (int j = 0; j < gamefield_height; j++)
		{
			gameFieldDynArray[i][j] = new char[gamefield_width];
		}
	}
	return gameFieldDynArray;
}

void Delete_GameFieldDynArray(char*** gameFieldDynArray, int grafik_buffer, int gamefield_height, int gamefield_width)
{
	for (int i = 0; i < grafik_buffer; i++)
	{
		for (int j = 0; j < gamefield_height; j++)
		{
			delete[] gameFieldDynArray[i][j];
		}
		delete[] gameFieldDynArray[i];
	}
	delete[] gameFieldDynArray;
}

void GenerateField(char*** gameFieldDynArray, int gamefield_height, int gamefield_width, int user_seed)
{
	int rnd = 0;

	for (int i = 0; i < gamefield_height; i++)
	{
		for (int j = 0; j < gamefield_width; j++)
		{
			if (i == 0 || i == gamefield_height - 1 || j == 0 && i > 0 && i < gamefield_height - 1 || j == gamefield_width - 1 && i > 0 && i < gamefield_height - 1)
			{
				gameFieldDynArray[0][i][j] = '#';
				gameFieldDynArray[1][i][j] = '#';
			}
			else
			{
				rnd = rand() % 1000;
				if (rnd < user_seed)
				{
					gameFieldDynArray[0][i][j] = 'O';
					gameFieldDynArray[1][i][j] = 'O';
				}
				else
				{
					gameFieldDynArray[0][i][j] = '-';
					gameFieldDynArray[1][i][j] = '-';
				}
			}
		}
	}
}

void ShowField(string gamefield, char*** gameFieldDynArray, int grafik_buffer,int show_buffer, int gamefield_height, int gamefield_width, int generation, int user_fps)
{	
	grafik_buffer = CurrentBuffer(grafik_buffer);
	system("CLS");
	if (grafik_buffer == 0)
	{
		if (show_buffer == true)
		{
			cout << "Generation_Buffer 1\t";
		}
	}
	else
	{
		if (show_buffer == true)
		{
			cout << "Generation_Buffer 2\t";
		}
	}
	for (int i = 0; i < gamefield_height; i++)
	{
		for (int j = 0; j < gamefield_width; j++)
		{
			
			gamefield += gameFieldDynArray[grafik_buffer][i][j];
		}
		gamefield += "\n";
	}
	cout << "Generation " << generation << endl;
	cout << gamefield;
	Sleep(user_fps);
}

int user_Gamefield_Height(int gamefield_height)
{
	cout << "Wie hoch soll das Spielfeld sein? (1-70) ";
	do
	{
		cin >> gamefield_height;
		if (gamefield_height <= 0 || gamefield_height > 70)
		{
			cout << "Die hoehe muss zwischen 1 und 70 liegen ";
		}

	} while (gamefield_height <= 0 || gamefield_height > 70);
	return gamefield_height;
}

int user_Gamefield_Width(int gamefield_width)
{
	cout << "Wie breit soll das Spielfeld sein? (1-270) ";
	do
	{
		cin >> gamefield_width;
		if (gamefield_width <= 0 || gamefield_width > 270)
		{
			cout << "Die breite muss zwischen 1 und 270 liegen ";
		}

	} while (gamefield_width <= 0 || gamefield_width > 270);
	return gamefield_width;
}

int user_Generation(int generation_user)
{
	do
	{
		cout << "Wie viele Generationen moechtest du Sehen? ";
		cin >> generation_user;
		if (generation_user == 0)
		{
			cout << "Du siehst die Aktuelle Generation doch schon o.O ..." << endl;
		}
		else if (generation_user < 0)
		{
			cout << "Sry aber bis wir in die Vergangenheit reisen koennen dauert es wohl noch etwas. ;)" << endl;
		}

	} while (generation_user <= 0);
	return generation_user;
}

bool user_Show_Grafik_Buffer()
{
	char user_input = ' ';
	cout << "Buffer Anzeigen? (j/n)" << endl;
	cin >> user_input;
	
	if (user_input == 'y' || user_input == 'j')
	{
		return true;
	}else
	return false;
	
}

int user_Rnd_Seed(int user_seed)
{
	cout << "Wähle eine start Populationsgroesse Zwischen 1 und 999 (Je hoeher desto mehr start Population hast du): ";
	do
	{
		cin >> user_seed;
		if (user_seed < 1 || user_seed > 999)
		{
			cout << "Bitte einen Zahl von 1 bis 999 Waehlen!";
		}
	} while(user_seed < 1 || user_seed > 999);
	cout << endl;
	return user_seed;
}

int User_Fps_Input(int user_fps)
{
	cout << "Wie schnell sollen die Generationen angezeigt werden (0 - 1000ms)? 0 = unlimitierte FPS (Je schneller dein PC desto schneller die FPS ;D): " ;
	do
	{
		cin >> user_fps;
		if (user_fps < 0 || user_fps > 1000)
		{
			cout << "Bitte einen Zahl von 0 bis 1000 Waehlen!";
		}
	} while (user_fps < 0 || user_fps > 1000);
	cout << endl;
	return user_fps;
}

void Start_Simulation(int grafik_buffer, char*** gameFieldDynArray,int gamefield_height,int gamefield_width)
{	
	
	for (int i = 1; i < gamefield_height-1; i++)
	{
		for (int j = 1; j < gamefield_width-1; j++)
		{
			int count = 0;
			if (gameFieldDynArray[grafik_buffer][i - 1][j - 1] == 'O')
			{
				count++;
			}
			if (gameFieldDynArray[grafik_buffer][i - 1][j] == 'O')
			{
				count++;
			}
			if (gameFieldDynArray[grafik_buffer][i - 1][j + 1] == 'O')
			{
				count++;
			}
			if (gameFieldDynArray[grafik_buffer][i][j - 1] == 'O')
			{
				count++;
			}
			if (gameFieldDynArray[grafik_buffer][i][j + 1] == 'O')
			{
				count++;
			}
			if (gameFieldDynArray[grafik_buffer][i + 1][j - 1] == 'O')
			{
				count++;
			}
			if (gameFieldDynArray[grafik_buffer][i + 1][j] == 'O')
			{
				count++;
			}
			if (gameFieldDynArray[grafik_buffer][i + 1][j + 1] == 'O')
			{
				count++;
			}

			if (count < 2)
			{
				if (grafik_buffer == 0)
				{
					gameFieldDynArray[1][i][j] = '-';
				}
				else
					gameFieldDynArray[0][i][j] = '-';
				
			}
			else if (count > 3)
			{
				if (grafik_buffer == 0)
				{
					gameFieldDynArray[1][i][j] = '-';
				}
				else
					gameFieldDynArray[0][i][j] = '-';
			}
			else if (count == 3)
			{
				if (grafik_buffer == 0)
				{
					gameFieldDynArray[1][i][j] = 'O';
				}
				else
					gameFieldDynArray[0][i][j] = 'O';
			}
		}
	}

	if (grafik_buffer == 0)
	{
		for (int i = 0; i < gamefield_height; i++)
		{
			for (int j = 0; j < gamefield_width; j++)
			{
				gameFieldDynArray[0][i][j] = gameFieldDynArray[1][i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < gamefield_height; i++)
		{
			for (int j = 0; j < gamefield_width; j++)
			{
				gameFieldDynArray[1][i][j] = gameFieldDynArray[0][i][j];
			}
		}
	}
}