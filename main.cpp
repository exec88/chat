#include <iostream>
#include "Chat.h"
#include <Windows.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
		
	Chat chat;
	chat.run();

	while(chat.ChatOne()) {
		chat.showLoginMenu();
		while(chat.getCurrentUser())	
		{
			chat.showUserMenu();
		}
	}
	return 0;
}