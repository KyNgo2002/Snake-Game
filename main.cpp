/*
*First real c++ project: C++ rendition of snake game.
*
*Made by: Ky Ngo
*Finished on: 8/11/2021
*Inspired by: NVitanovic on youtube
*/


#include <iostream>
#include <conio.h>
#include<windows.h>
using namespace std;
bool gameOver = false;
int x, y, fruitX, fruitY, score;
int tailX[50], tailY[50];
int lengthTail;
enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;
int width = 20;
int height = 20;
string difficulty;


//Draws the playing board and displays controls, difficulty and score.
void draw() {
	system("cls");
	cout << "Use WASD to control the snake" << endl << "Difficulty: " << difficulty << endl;

	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 1; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "#";
			}
			if (x == j && y == i) {
				cout << "O";
			}
			else if (fruitX == j && fruitY == i) {
				cout << "F";
			}
			else {
				bool thing = false;
				for (int k = 0; k < lengthTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						thing = true;
					}
				}
				if(!thing)
					cout << " ";
			}
			if (j == width - 1) {
				cout << "#" << endl;
			}
			
		}
	}
	for (int k = 0; k < width + 2; k++) {
		cout << "#";
	}
	cout << endl << "Score: " << score << endl;
}

//Takes in user input for snake movement
void Input() {
	if (_kbhit()) {
		switch(_getch()){
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

//Logic for player movement and remembering tail elements
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prevsX, prevsY;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < lengthTail; i++) {
		prevsX = tailX[i];
		prevsY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevsX;
		prevY = prevsY;
	}
	switch (dir) {
		case RIGHT:
			x++;
			break;
		case LEFT:
			x--;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	if (x < 0 || x >= width || y <= 0 || y >= height) {
		gameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		lengthTail++;
		score += 10;
		fruitX = rand() % (width - 1) + 1;
		fruitY = rand() % (height - 1) + 1;
	}
	for (int j = 0; j < lengthTail; j++) {
		if (x == tailX[j] && y == tailY[j]) {
			gameOver = true;
		}
	}

}

//Setup the game
void setup() {
	lengthTail = 0;
	srand(time(0));
	x = width / 2;
	y = height / 2;
	dir = STOP;
	score = 0;
	fruitX = rand() % (width - 1) + 1;
	fruitY = rand() % (height - 1) + 1;
	while (!gameOver) {

		draw();
		Input();
		Logic();
		if (dir == UP || dir == DOWN) {
			Sleep(100);
		}
		else {
			Sleep(50);
		}
	}
}

//Prompts user for difficulty and checks for game over.
int main() {
	int difficulty1 = 0;
	int difficulty2 = 0;
	while (true) {
		cout << "Please enter a difficulty(easy, medium, hard) and press enter!" << endl;
		cin >> difficulty;
		if (difficulty == "easy") {
			difficulty1 = 500;
			difficulty2 = 250;
			break;
		}
		else if (difficulty == "medium") {
			difficulty1 = 250;
			difficulty2 = 125;
			break;
		}
		else if (difficulty == "hard") {
			difficulty1 = 100;
			difficulty2 = 50;
			break;
		}
		else {
			cout << "Invalid Input. Please try again." << endl;
		}
	}
	system("cls");
	setup();
	
	if (gameOver) {
		cout << endl << "Game Over!" << endl;
		cout << "Play again?(yes/no)" << endl;
		cin >> difficulty;
		if (difficulty == "yes") {
			gameOver = false;
			setup();
		}
		else {
			cout << "Thanks for playing!" << endl << endl << endl;
		}
	}

	return 0;
}