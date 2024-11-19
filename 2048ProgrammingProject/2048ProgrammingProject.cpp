#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <windows.h>
#include <ctime>

using namespace std;


bool Continuepage = false;
enum GameState {
	MAIN_MENU,
	PLAYING,
	PAUSED,
};

enum PreviousPage {
	MAIN_MENU_PAGE,
	MCONTINUE_PAGE,
};
PreviousPage previousPage = MAIN_MENU_PAGE;

struct GameStateData {
	int savedScore;
	int savedHighestScore;
	int savedTile[8][8];
	int savedSize;
};
GameStateData savedGameState;

struct player {
	int hscore = 0;
	string name = " ";
};


player players[10];

int np = 0;
int temptile[8][8] = { 0 };
int executioncount = 0;
void movement();
void ranklist();
void rand_generator();
void board();
void begin(char x);
void options();
bool GameOver();
void GOpage();
void pausepage();
void highest();
void levelup();
void Idata();
void sboard();;
bool isBoardChanged();
void FontSize(int size);
void MContinue();
void sMain();
void sPlay();
void Continue();
void players_();
void leaderboard();
GameState gameState = MAIN_MENU;
void sMain();
void sPlay();
void Continue();
void MContinue();

struct Scoreboard {
	int current_score;
	int highest_score;
};

struct Game {
	int tile[8][8] = { 0 };
	int size = 4;
	Scoreboard gamescoreboard;
};

Game thegame;
void slideup(Game& thegame);
void slidedown(Game& thegame);
void slideright(Game& thegame);
void slideleft(Game& thegame);
void right(Game& thegame);
void left(Game& thegame);
void down(Game& thegame);
void up(Game& thegame);

int main()
{
	FontSize(15);
	options();
}
void options() {
	system("cls");
	system("color 1F");
	cout << setw(45) << "Welcome back!\n";
	char x;

	switch (gameState) {
	case MAIN_MENU:
		cout << setw(24) << "" << "--------------------------" << endl;
		cout << setw(26) << "| " << setw(16) << "Start Menu" << setw(8) << " |" << endl;
		cout << setw(26) << "| " << setw(8) << "Start" << setw(12) << "(N)" << setw(4) << "|" << endl;
		cout << setw(26) << "| " << setw(10) << "Ranking" << setw(10) << "(L)" << setw(4) << "|" << endl;
		cout << setw(26) << "| " << setw(7) << "Exit" << setw(15) << "(Esc)" << setw(2) << "|" << endl;
		cout << setw(24) << "" << "--------------------------" << endl;
		if (gameState == PLAYING || gameState == PAUSED || Continuepage) {
			cout << setw(26) << "| " << setw(8) << "Continue" << setw(12) << "(C)" << setw(4) << "|" << endl;
		}
		break;
	}
	do {
		x = _getch();
		switch (x) {
		case 27:
			if (previousPage == MCONTINUE_PAGE) {
				MContinue();
			}
			else {
				sMain();
			}
			sMain();
			break;
		case 'N':
		case 'n':
			Continuepage = true;
			begin(x);
			break;
		case 'C':
		case 'c':
			if (gameState == PAUSED) {
				Continue();
			}
			break;
		case 'L':
		case 'l':
			system("cls");
			ranklist();
			break;
		}
	} while (int(x) != 27 && x != 'n' && x != 'N' && x != 'R' && x != 'r');
}
void begin(char x)
{
	if (x == 'N' || x == 'n') {
		executioncount = 0;
		if (np == 0)
			Idata();
		else
			thegame.gamescoreboard.current_score = 0;
		for (int i = 0; i < thegame.size; i++)
			for (int j = 0; j < thegame.size; j++) {
				thegame.tile[i][j] = { 0 };
			}
		rand_generator();
		FontSize(20);
		thegame.size = 4;
	}
	do {
		rand_generator();
		highest();
		levelup();
		sboard();
		board();
		movement();
	} while (GameOver() == 0);
	GOpage();
}
void ranklist()
{
	char x;
	leaderboard();
	cout << setw(22) << "Ranking Page" << endl;
	cout << " Rank |" << setw(11) << "Name" << setw(15) << "| Score" << endl;
	cout << "----------------------------------" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "   " << (i + 1) << "  | " << setw(14) << players[i].name << setw(6) << " | " << players[i].hscore << endl;
	}
	cout << endl << "Press (ESC) to return to Main Menu\n";
	if (Continuepage) {
		cout << " Press (C) to Continue";
	}
	do {
		x = _getch();
		switch (x) {
		case 27:
			if (Continuepage) {
				MContinue();
			}
			else {
				sMain();
			}
		case 'C':
		case 'c':
			if (Continuepage) {
				Continue();
			}
			break;
		default:
			system("cls");
			ranklist();
		}
	} while (int(x) != 27);
}
void GOpage()
{
	system("cls");
	system("color 4F");
	players[9].hscore = thegame.gamescoreboard.current_score;
	int numDigits = static_cast<int>(log10(thegame.gamescoreboard.current_score));

	// Adjust the setw value based on the number of digits
	int width = 30 - numDigits;  // Adjust the base width (30) as needed

	cout << setw(width) << "" << "--------------------------" << endl;
	cout << setw(width + 2) << "| " << setw(16) << "Game Over" << setw(8) << " |" << endl;
	cout << setw(width + 2) << "| " << setw(8) << "score: " << thegame.gamescoreboard.current_score << setw(15 - numDigits) << "|" << endl;
	cout << setw(width + 2) << "| " << setw(11) << "Play again" << setw(9) << "(N)" << setw(4) << "|" << endl;
	cout << setw(width + 2) << "| " << setw(10) << "Main menu" << setw(12) << "(Esc)" << setw(2) << "|" << endl;
	cout << setw(width) << "" << "--------------------------" << endl;
	char x;
	do {
		x = _getch();
		switch (x) {
		case 27:
			Continuepage = false;
			options();
			break;
		case 'N':
		case 'n':
			begin(x);
			break;
		}
	} while (int(x) != 27 && x != 'n' && x != 'N');
}
void pausepage()
{
	leaderboard();
	savedGameState.savedScore = thegame.gamescoreboard.current_score;
	savedGameState.savedHighestScore = thegame.gamescoreboard.highest_score;
	savedGameState.savedSize = thegame.size;
	for (int i = 0; i < thegame.size; ++i) {
		for (int j = 0; j < thegame.size; ++j) {
			savedGameState.savedTile[i][j] = thegame.tile[i][j];
		}
	}
	system("cls");
	system("color 5F");
	cout << setw(22) << "" << "--------------------------" << endl;
	cout << setw(24) << "| " << setw(14) << "Paused" << setw(10) << " |" << endl;
	cout << setw(24) << "| " << setw(8) << "Resume" << setw(12) << "(R)" << setw(4) << "|" << endl;
	cout << setw(24) << "| " << setw(10) << "New game" << setw(10) << "(N)" << setw(4) << "|" << endl;
	cout << setw(24) << "| " << setw(11) << "Main menu" << setw(11) << "(Esc)" << setw(2) << "|" << endl;
	cout << setw(22) << "" << "--------------------------" << endl;
	char x;
	do {
		x = _getch();
		switch (x) {
		case 27:
			MContinue();
			break;
		case 'R':
		case 'r':
			Continue();
			break;
		case 'N':
		case 'n':
			begin(x);
			break;
		case 'C':
		case 'c':
			if (gameState == PAUSED) {
				Continue();
			}
			break;
		}
	} while (int(x) != 27 && x != 'n' && x != 'N');
}
void board()
{
	cout << setw(20) << "-";
	for (int k = 0; k < thegame.size; k++)
	{
		cout << "------";
	}
	cout << endl;
	for (int i = 0; i < thegame.size; i++)
	{
		cout << setw(20) << "|";
		for (int j = 0; j < thegame.size; j++)
		{
			if (thegame.tile[i][j] != 0)
				cout << setw(3) << (thegame.tile[i][j]);
			else
				cout << setw(3) << " ";
			cout << setw(3) << "|";
		}
		if (i != thegame.size - 1)
		{
			cout << endl << setw(20);
			for (int k = 0; k < thegame.size; k++)
			{
				cout << "|" << "-----";
			}
			cout << "|" << endl;
		}
	}
	cout << endl << setw(20) << "-";
	for (int k = 0; k < thegame.size; k++)
	{
		cout << "------";
	}
	cout << endl;
}
void sboard()
{
	system("cls");
	system("color 71");
	if (thegame.size == 4)
	{
		cout << setw(44) << "-------------------------" << endl;
		cout << setw(20) << "|" << setw(8) << "Score" << setw(4) << "|" << setw(9) << "Highest" << setw(3) << "|" << endl;
		cout << setw(20) << "|" << setw(7) << thegame.gamescoreboard.current_score << setw(5) << "|" << setw(7) << thegame.gamescoreboard.current_score << setw(5) << "|" << endl;
		cout << setw(44) << "-------------------------" << endl;
	}
	if (thegame.size == 6)
	{
		cout << setw(56) << "-------------------------------------" << endl;
		cout << setw(20) << "|" << setw(11) << "Score" << setw(7) << "|" << setw(12) << "Highest" << setw(6) << "|" << endl;
		cout << setw(20) << "|" << setw(10) << thegame.gamescoreboard.current_score << setw(8) << "|" << setw(10) << thegame.gamescoreboard.current_score << setw(8) << "|" << endl;
		cout << setw(56) << "-------------------------------------" << endl;
	}
	if (thegame.size == 8)
	{
		cout << setw(68) << "-------------------------------------------------" << endl;
		cout << setw(20) << "|" << setw(14) << "Score" << setw(10) << "|" << setw(15) << "Highest" << setw(9) << "|" << endl;
		cout << setw(20) << "|" << setw(14) << thegame.gamescoreboard.current_score << setw(10) << "|" << setw(14) << thegame.gamescoreboard.current_score << setw(10) << "|" << endl;
		cout << setw(68) << "-------------------------------------------------" << endl;
	}
}
bool GameOver()
{
	for (int i = 0; i < thegame.size; i++) {
		for (int j = 0; j < thegame.size; j++) {
			if (thegame.tile[i][j] == 0) {
				return false;
			}
			else if (j < thegame.size - 1 && thegame.tile[i][j] == thegame.tile[i][j + 1]) {
				return false;
			}
			else if (i < thegame.size - 1 && thegame.tile[i][j] == thegame.tile[i + 1][j]) {
				return false;
			}
		}
	}
	return true;
}
bool isBoardChanged()
{
	for (int j = 0; j < thegame.size; j++)
	{
		for (int i = 0; i < thegame.size; i++)
		{
			if (temptile[i][j] != thegame.tile[i][j])
			{
				return true; // Board has changed
			}
		}
	}
	return false; // Board is the same
}
void firsttwotiles() {
	srand(time(0));
	int row, col;
	do {
		row = rand() % thegame.size;
		col = rand() % thegame.size;
	} while (thegame.tile[row][col] != 0);

	thegame.tile[row][col] = (executioncount == 0) ? 2 : 4;

	executioncount++;
}
void generaterandomtile() {
	int RN = 0, r, c;
	srand(time(0));
	while (RN != 2 && RN != 4) {
		if (rand() % 5 == 2 || rand() % 5 == 4)
			RN = rand() % 5;
	}
	int n = 0;
	for (int i = 0; i < thegame.size; i++)
		for (int j = 0; j < thegame.size; j++)
			if (thegame.tile[i][j] == 0)
				n++;
	r = rand() % thegame.size;
	c = rand() % thegame.size;
	while (thegame.tile[r][c] != 0 && n > 0) {
		r = rand() % thegame.size;
		c = rand() % thegame.size;
	}
	if (n > 0)
		thegame.tile[r][c] = RN;
}
void saveoldboard() {
	for (int j = 0; j < thegame.size; j++)
		for (int i = 0; i < thegame.size; i++)
			temptile[i][j] = thegame.tile[i][j];
}
void rand_generator() {
	if (executioncount < 2) {
		firsttwotiles();
	}
	else
		if (isBoardChanged()) {
			generaterandomtile();
			saveoldboard();
		}
}

void Idata()
{
	system("cls");
	cout << "Enter Name: ";
	cin >> players[8].name;
	players[8].hscore = thegame.gamescoreboard.current_score;
}

void highest()
{
	if (thegame.gamescoreboard.current_score > thegame.gamescoreboard.highest_score)
	{
		thegame.gamescoreboard.highest_score = thegame.gamescoreboard.current_score;
		players[8].hscore = thegame.gamescoreboard.highest_score;
	}
}
void levelup()
{
	if (thegame.gamescoreboard.current_score >= 512)
		thegame.size = 6;
	if (thegame.gamescoreboard.current_score >= 1024)
		thegame.size = 8;
}
void movement()
{
	//function for choosing the movement using arrow keys
	char move;
	move = _getch();
	switch (move) {
	case 77:            // ASCII code for right key
		right(thegame);        //calls the right movement function
		break;
	case 75:           //ASCII code for left key
		left(thegame);        //calls the left movement fuction 
		break;
	case 72:           //ASCII code for up key
		up(thegame);          //calls the up movement function
		break;
	case 80:           //ASCII code for down key
		down(thegame);        //calls the down movement function
		break;
	case 27:
		pausepage();
		break;
	default:
		movement();
		break;
	}
}
void right(Game& thegame) {
	slideright(thegame);

	for (int i = 0; i < thegame.size; i++) {
		for (int j = thegame.size - 1; j > 0; j--) {
			if (thegame.tile[i][j] == thegame.tile[i][j - 1]) {
				thegame.tile[i][j] = thegame.tile[i][j] + thegame.tile[i][j - 1];
				thegame.tile[i][j - 1] = 0;
				thegame.gamescoreboard.current_score += thegame.tile[i][j];

			}
		}
	}

	slideright(thegame);
}
void slideright(Game& thegame) {
	for (int maxmoves = 0; maxmoves < thegame.size - 1; maxmoves++) {
		for (int i = 0; i < thegame.size; i++) {
			for (int j = thegame.size - 1; j > 0; j--) {
				if (thegame.tile[i][j] == 0 && thegame.tile[i][j - 1] != 0) {
					thegame.tile[i][j] = thegame.tile[i][j - 1];
					thegame.tile[i][j - 1] = 0;
				}
			}
		}
	}
}
void left(Game& thegame) {
	slideleft(thegame);

	for (int i = 0; i < thegame.size; i++) {
		for (int j = 0; j < thegame.size - 1; j++) {
			if (thegame.tile[i][j] == thegame.tile[i][j + 1]) {
				thegame.tile[i][j] = thegame.tile[i][j] + thegame.tile[i][j + 1];
				thegame.tile[i][j + 1] = 0;
				thegame.gamescoreboard.current_score += thegame.tile[i][j];

			}
		}
	}

	slideleft(thegame);
}
void slideleft(Game& thegame) {
	for (int maxmoves = 0; maxmoves < thegame.size - 1; maxmoves++) {
		for (int i = 0; i < thegame.size; i++) {
			for (int j = 0; j < thegame.size - 1; j++) {
				if (thegame.tile[i][j] == 0 && thegame.tile[i][j + 1] != 0) {
					thegame.tile[i][j] = thegame.tile[i][j + 1];
					thegame.tile[i][j + 1] = 0;
				}
			}
		}
	}
}
void down(Game& thegame) {
	slidedown(thegame);

	for (int j = 0; j < thegame.size; j++) {
		for (int i = thegame.size - 1; i > 0; i--) {
			if (thegame.tile[i][j] == thegame.tile[i - 1][j]) {
				thegame.tile[i][j] = thegame.tile[i][j] + thegame.tile[i - 1][j];
				thegame.tile[i - 1][j] = 0;
				thegame.gamescoreboard.current_score += thegame.tile[i][j];

			}
		}
	}

	slidedown(thegame);
}
void slidedown(Game& thegame) {
	for (int maxmoves = 0; maxmoves < thegame.size - 1; maxmoves++) {
		for (int j = 0; j < thegame.size; j++) {
			for (int i = thegame.size - 1; i > 0; i--) {
				if (thegame.tile[i][j] == 0 && thegame.tile[i - 1][j] != 0) {
					thegame.tile[i][j] = thegame.tile[i - 1][j];
					thegame.tile[i - 1][j] = 0;
				}
			}
		}
	}
}
void up(Game& thegame) {
	slideup(thegame);

	for (int j = 0; j < thegame.size; j++) {
		for (int i = 0; i < thegame.size - 1; i++) {
			if (thegame.tile[i][j] == thegame.tile[i + 1][j]) {
				thegame.tile[i][j] = thegame.tile[i][j] + thegame.tile[i + 1][j];
				thegame.tile[i + 1][j] = 0;
				thegame.gamescoreboard.current_score += thegame.tile[i][j];

			}
		}
	}

	slideup(thegame);

}
void slideup(Game& thegame) {
	for (int maxmoves = 0; maxmoves < thegame.size - 1; maxmoves++) {
		for (int j = 0; j < thegame.size; j++) {
			for (int i = 0; i < thegame.size - 1; i++) {
				if (thegame.tile[i][j] == 0 && thegame.tile[i + 1][j] != 0) {
					thegame.tile[i][j] = thegame.tile[i + 1][j];
					thegame.tile[i + 1][j] = 0;
				}
			}
		}
	}
}
void players_() {
	players[0] = { 550,"Renad" };
	players[1] = { 750, "Rawan" };
	players[2] = { 850,"Jimmy McGill" };
	players[3] = { 500,"Farrag" };
	players[4] = { 600 ,"Feras" };
	players[5] = { 450, "Fahmy" };
	players[6] = { 780,"Youssef" };
	players[7] = { 1000,"Kim Wexler" };
}
void leaderboard() {
	system("cls");
	players_();
	int scoretemp = 0;
	string nametemp = "";
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (players[k].hscore < players[i].hscore) {
				scoretemp = players[k].hscore;
				players[k].hscore = players[i].hscore;
				players[i].hscore = scoretemp;
				nametemp = players[k].name;
				players[k].name = players[i].name;
				players[i].name = nametemp;
			}
		}
	}
}
void FontSize(int size) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	fontInfo.dwFontSize.X = size;
	fontInfo.dwFontSize.Y = size * 2;  // Adjust the Y value for the desired font height
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}
void MContinue() {
	system("cls");
	system("color 1F");

	cout << setw(45) << "Welcome back!\n";
	char x;

	// Display the main menu with the additional option to continue
	cout << setw(24) << "" << "--------------------------" << endl;
	cout << setw(26) << "| " << setw(16) << "Start Menu" << setw(8) << " |" << endl;
	cout << setw(26) << "| " << setw(8) << "Start" << setw(12) << "(N)" << setw(4) << "|" << endl;
	cout << setw(26) << "| " << setw(10) << "Ranking" << setw(10) << "(L)" << setw(4) << "|" << endl;
	cout << setw(26) << "| " << setw(11) << "Continue" << setw(9) << "(C)" << setw(4) << "|" << endl;
	cout << setw(26) << "| " << setw(7) << "Exit" << setw(15) << "(Esc)" << setw(2) << "|" << endl;


	cout << setw(24) << "" << "--------------------------" << endl;

	do {
		x = _getch();
		switch (x) {
		case 27:
			exit(-1);
			return;
		case 'N':
		case 'n':
			begin(x);
			break;
		case 'C':
		case 'c':
			if (gameState == PAUSED) {
				Continue();  // Continue the game if it's paused
			}
			break;
		case 'L':
		case 'l':
			leaderboard();
			ranklist();
			break;
		}
	} while (int(x) != 27 && x != 'n' && x != 'N' && x != 'C' && x != 'c' && x != 'L' && x != 'l');
}
void sMain() {
	gameState = MAIN_MENU;
	options();
}
void sPlay() {
	gameState = PLAYING;
	begin(' ');
}
void Continue() {
	gameState = PLAYING;
	thegame.gamescoreboard.current_score = savedGameState.savedScore;
	thegame.gamescoreboard.highest_score = savedGameState.savedHighestScore;
	thegame.size = savedGameState.savedSize;
	for (int i = 0; i < thegame.size; ++i) {
		for (int j = 0; j < thegame.size; ++j) {
			thegame.tile[i][j] = savedGameState.savedTile[i][j];
		}
	}
	do {
		sboard();
		board();
		rand_generator();
		movement();
		highest();
		levelup();

	} while (GameOver() == 0);
	GOpage();

}