#pragma once
#include <set>
#include "user.h"

/*
userContainer handles the "user database", meaning its task is to store, display, add and remove users from the platform's
database.
*/
class userContainer {
private:
	set<User*> user_db;
public:
	userContainer();
	~userContainer() {}

	void showUserList();
	void addUser(User & u);
	void deleteUser(User & u);
	bool findUser(string email);
	User * getUser(string email);
	void modifyEmail(User & u, string newmail);
	void deleteCreditCard(Customer & c);
	void changeCreditCard(Customer & c, string credit, string csc);
	void modifySubscription(User & u);
	
	bool findUser(User & u);
	User & getUser(User & u);	
};