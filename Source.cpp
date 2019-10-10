#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

bool gameOver;
const int winScore = 100;
const int width = 20;
const int height = 15;
int num = 1;
int fruitX, fruitY, frX, frY, score;
enum  eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

struct Snake {
	int x, y;
}snake[width * height];

void GenerateFruit(void);

void Setup() {
	int scr = 0;
	gameOver = false;
	dir = STOP;
	snake[0].x = width / 2 - 1;
	snake[0].y = height / 2 - 1;
	GenerateFruit();
	score = 0;
}
void Draw() {
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (j < width - 1) {
				if (i == snake[0].y && j == snake[0].x)
					cout << "0";
				else if (i == fruitY && j == fruitX)
					cout << "X";
				else {
					bool print = false;
					for (int k = 1; k < num; k++) {
						if (i == snake[k].y && j == snake[k].x) {
							print = true;
							cout << "o";
						}
					}
					if (!print) cout << " ";
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score;
}
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int scr = 0;
	for (int i = num; i > 0; --i) {
		snake[i].x = snake[i-1].x;	
		snake[i].y = snake[i-1].y;
	}
	switch (dir)
	{
	case LEFT:
		snake[0].x--;
		break; 
	case RIGHT:
		snake[0].x++;
		break;
	case UP:
		snake[0].y--;
		break;
	case DOWN:
		snake[0].y++;
		break;
	}
	
	if (snake[0].x > width-2) snake[0].x = 0;
	if (snake[0].x < 0) {
		snake[0].x = width-1;
		dir = LEFT;
	}
	if (snake[0].y > height-1) snake[0].y = 0;
	if (snake[0].y < 0) {
		snake[0].y = height-1;
		dir = UP;
	}

	for (int i = 1; i < num; i++) {
		if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
			gameOver = true;
	}


	if (snake[0].x == fruitX && snake[0].y == fruitY) {
		num++;
		GenerateFruit();
		score += 10;
	}

	if (score == winScore) {
		gameOver = true;
	}
}

void GenerateFruit() {
	/*srand(time(NULL));*/
	int scr = 0;
	frX = 1 + rand() % (width - 1);
	frY = 1 + rand() % (height - 1);
	for (int i = 0; i < num; i++) {
		if (frX != snake[i].x && frY != snake[i].y) scr++;
	}
	if (scr == num) {
		fruitX = frX;
		fruitY = frY;
	}
	else GenerateFruit();
}

int main() {
	cout << "\\\\\\\\\\  SNAKE  /////" << endl << endl;
	cout << "W,A,S,D - control keys" << endl << endl;
	cout << "Made by Dmitriy Starodubtsev" << endl;
	cout << "Press enter to continue...";
	if(getchar()){
		system("cls");
		Setup();
		while (!gameOver) {
			Draw();
			Input();
			Logic();
		}
		if (gameOver) {
			if (score == winScore) {
				system("cls");
				cout << "Your score: " << score << endl;
				cout << "YOU WIN!" << endl;
			}
			else {
				system("cls");
				cout << "Your score: " << score << endl;
				cout << "GAME OVER!" << endl;
			}
		}
		system("pause");
	}
	return 0;
}