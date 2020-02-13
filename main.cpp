// "main.cpp"

#include <iostream>
#include "board.h"
#include "connectfour.h"

using namespace std;

int main()
{
	ConnectFour gameManager;
	gameManager.Play();

	system("pause");
	return EXIT_SUCCESS;
}
