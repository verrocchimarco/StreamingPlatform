#include "channel.h"
#include "user.h"
#include "userContainer.h"
#include "channelContainer.h"
#include "main.h"
int main() {
	cout << "\t\tWelcome to Broflix\n";
	userContainer cont;
	cout << endl << endl << "Press 1 to login, 2 to create a new user";
	char c;
	do
	{
		cin >> c;
	} while (c!='1' && c!='2');

	system("PAUSE");
}