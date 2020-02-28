// Game Of 15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#include "Tile.h"


enum class Direction { up, down, left, right };


std::vector<std::vector<Tile>> board = {
	{Tile(1), Tile(2), Tile(3), Tile(4)},
	{Tile(5), Tile(6), Tile(7), Tile(8)},
	{Tile(9), Tile(10), Tile(11), Tile(12)},
	{Tile(13), Tile(14), Tile(15), Tile(-1)}
};
Direction dir;


void render();
void shuffle();
void swap(int firstX, int firstY, int secondX, int secondY);
void askMove();
std::vector<unsigned int> findVoidTile();
bool checkValidMove(std::vector<unsigned int> voidTile, Direction direction);
void checkCompletion();

int main()
{
	srand((unsigned int)time(NULL));

	shuffle();

	render();

}

void render()
{
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 0; j < board[i].size(); j++)
		{
			if (board[i][j].getNumber() > 0) {
				std::cout << board[i][j].getNumber();
				if (board[i][j].getNumber() < 10) {
					std::cout << "  ";
				}
				else {
					std::cout << " ";
				}
			}
			else {
				std::cout << "   ";
			}
		}

		std::cout << std::endl;
	}

	askMove();
}

void shuffle()
{

	for (size_t i = 0; i < 30; i++)
	{
		int x1 = rand() % 4;
		int y1 = rand() % 4;
		int x2 = rand() % 4;
		int y2 = rand() % 4;
		swap(x1,y1,x2,y2);
	}
}

void swap(int x1, int y1, int x2, int y2)
{
	Tile tmpTile = board[x1][y1];

	board[x1][y1] = board[x2][y2];

	board[x2][y2] = tmpTile;
}

void askMove()
{
	std::string direction;
	std::cout << "What direction do you want to move into? [up/down/left/right]" << std::endl;
	std::cin >> direction;

	std::vector<unsigned int> tileLoc = findVoidTile();

	if (direction == "up") {
		if (checkValidMove(tileLoc, Direction::up)) {
			swap(tileLoc[0], tileLoc[1], tileLoc[0] - 1, tileLoc[1]);
		}
		else {
			std::cout << "Invalid move! please try agian." << std::endl;
		}
	}
	else if (direction == "down") {

		if (checkValidMove(tileLoc, Direction::down)) {
			swap(tileLoc[0], tileLoc[1], tileLoc[0] + 1, tileLoc[1]);
		}
		else {
			std::cout << "Invalid move! please try agian." << std::endl;
		}
	}
	else if (direction == "left") {
		if (checkValidMove(tileLoc, Direction::left)) {
			swap(tileLoc[0], tileLoc[1], tileLoc[0], tileLoc[1] - 1);
		}
		else {
			std::cout << "Invalid move! please try agian." << std::endl;
		}
	}
	else if (direction == "right") {
		if (checkValidMove(tileLoc, Direction::right)) {
			swap(tileLoc[0], tileLoc[1], tileLoc[0], tileLoc[1] + 1);
		}
		else {
			std::cout << "Invalid move! please try agian." << std::endl;
		}
	}
	else {
		std::cout << "Direction not recognized, try again." << std::endl;
	}
	render();
}

std::vector<unsigned int> findVoidTile()
{
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 0; j < board[i].size(); j++)
		{
			if (board[i][j].getNumber() == -1) {
				 return { i,j };
			}
		}
	}
	return {};
}

bool checkValidMove(std::vector<unsigned int> voidTile, Direction direction)
{
	switch (direction)
	{
	case Direction::up:
		return voidTile[0] > 0;
	case Direction::down:
		return voidTile[0] < board.size()-1;
	case Direction::left:
		return voidTile[1] > 0;
	case Direction::right:
		return voidTile[1] < board[voidTile[0]].size()-1;
	default:
		return false;
	}
}

void checkCompletion()
{
	bool completed = true;
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 1; j <= board[i].size(); j++)
		{
			Tile tile = board[i][j-1];

			if (((i * 4) + j) == 16)
			{
				if (tile.getNumber() != -1) {
					completed = false;
				}
				
			}
			else {
				if (tile.getNumber() != ((i * 4) + j))
				{
					completed = false;
				}
			}

			
		}
	}

	if (completed == true) {
		char answer;
		std::cout << "Congratulations you have completed The Game of 15! Would you like to play again? [Y/N]" << std::endl;
		std::cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			system("cls");
			main();
		}
	}
}
