#pragma once
#include<string>
#include <iostream>

using namespace std;

/*Abstract Base Class defining an user. Users can be:
1) Customers, default users who need to pay for a monthly subscription in order to use the platform
2) Admins, who can access platform's functions like deleting ("banning") users or setting a channel on/off air
3) Broadcasters, executives who can create new channels and add them to the platform

Both admins and broadcasters have a free subscription
*/
class User {
protected:
	string first_name, last_name, password;
	int sub;
	string email;
public:
	enum { Subscribed, Unsubscribed };
	User() {}
	User(string f, string l, string email, string psw)
		: first_name(f), last_name(l), email(email), password(psw) {}
	virtual ~User() {}
	string getFName() const { return first_name; }
	string getLName() const { return last_name; }
	string getEmail() const { return email; }
	string getPassword() const { return password; }
	virtual void show() const;
	virtual void manageSubscription() = 0;
	void changeEmail(string & newMail) { email = newMail; }
	virtual bool operator==(const User & u);
	int getSubscription() const { return sub; }
};

//Default user, gets access to the Streaming Platform and needs to add a credit card to start a membership
//Customers start with no paid subscription by default
class Customer : public User {
private:
	bool card_registered;
	string credit_card, csc_code;
public:
	Customer() {}
	Customer(string f, string l, string email, string psw, int s = Unsubscribed);
	virtual ~Customer() {}
	void setCreditCard(string cc, string csc);
	void deleteCreditCard();
	bool hasCard() { return card_registered;  }
	virtual void show() const;
	virtual void manageSubscription() { sub = (sub == Subscribed) ? Unsubscribed : Subscribed; }
	pair<string, string> getCreditCard() const { return make_pair(credit_card, csc_code); }
	Customer & operator=(const Customer & c);
};

//Both admins and broadcasters have a "free subscription" (Subscribed is default and unchangeable parameter)
//No credit card is required
class Admin : public User {
public:
	Admin() {}
	Admin(string f, string l, string email, string psw);
	virtual ~Admin() {}
	virtual void show() const;
	virtual void manageSubscription();
	Admin & operator=(const Admin & a);
};

//Broadcasters work for a company and are in charge of creating new channels
class Broadcaster : public User {
private:
	string company;
public:
	Broadcaster(){}
	Broadcaster(string f, string l, string email, string psw, string c);
	virtual ~Broadcaster() {}
	virtual void show() const;
	string getCompany() const { return company; }
	virtual void manageSubscription();
	Broadcaster & operator=(const Broadcaster b);
};
