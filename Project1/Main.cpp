#include <iostream>
#include <conio.h>
#include "windows.h"

/*
About: A simple non-object oriented snake game that prints directly
to the console for windows.

Rules: The player must eat the fruit to gains points. If player crosses 
self OR hits the wall, game over.

Author: Zev Yirmiyahu
Personal Site: www.zevyirmiyahu.com

*/


bool gameOver;
const int width = 25;
const int height = 15;

int x, y; // head position of snake
int tailX[100], tailY[100]; // tail position held in arrays
int tailLength;
int fruitX, fruitY; // coordinates of fruit
int score = 0;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;

void init() {
	score = 0;
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width; //creates random number from 0 to width - 1
	fruitY = rand() % height;
}

void render() {
	system("cls"); // clear console
	
	// system("clear"); // clears console for linux


	 // RENDER GAME MAP

	// top
	for (int i = 0; i < width + 2; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;

	// left and right
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) std::cout << "#";

			if (i == y && j == x) std::cout << "O"; // prints snakes head
			
			else if (i == fruitY && j == fruitX) std::cout << "F";
			
			else {
				// draws the tail
				bool printedTail = false; // keeps track of tail printing
				for (int k = 0; k < tailLength; k++) {
					
					if (tailX[k] == j && tailY[k] == i) {
						std::cout << "o"; // if true print tail
						printedTail = true;
					}
				}
				if(!printedTail) std::cout << " ";
			}
			if (j == width - 1) std::cout << "#";
		}
		std::cout << std::endl;
	}

	// bottom
	for (int i = 0; i < width + 2; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;
	std::cout << "Score: ";
	std::cout << score;


}
void input() {
	if (_kbhit()) {
		switch (_getch()) {
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
		default: break;
		}
	}
}

void logic() {

	// tail follow logic
	int prevTailX = tailX[0];
	int prevTailY = tailY[0];
	int prevTail2X, prevTail2Y;
	tailX[0] = x; // set first piece of tail to follow head
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++) {
		prevTail2X = tailX[i];
		prevTail2Y = tailY[i];
		tailX[i] = prevTailX;
		tailY[i] = prevTailY;
		prevTailX = prevTail2X;
		prevTailY = prevTail2Y;

	}
	// players movement
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	// out of bounds
	if (x < 0 || x > width || y < 0 || y > height) gameOver = true;

	// player passes through tail...dies
	for (int i = 0; i < tailLength; i++) {
		if (tailX[i] == x && tailY[i] == y) gameOver = true;
	}
	// player's score
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		tailLength++; // tail grows if player eats fruit
	}
}

int main()
{
	std::cout << "**** SNAKE GAME ****" << std::endl;
	std::cout << "Controls: 'w' = up, 's' = down, 'a' = left, 'd' = right" << std::endl;
	std::cout << "Press 'enter' to play." << std::endl;
	std::cin.get();

	init();
	while (!gameOver) {
		render();
		input();
		logic();
		Sleep(50);
	}
	system("cls"); // clear console
	std::cout << "GAME OVER" << std::endl;
	std::cout << "Final Score: ";
	std::cout << score;
	std::cin.get();
}
