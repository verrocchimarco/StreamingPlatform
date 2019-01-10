#include <typeinfo>
#include "user.h"

// User methods
void User::show() const {
	cout << "Name: " << first_name << " " << last_name << endl
		<< "Email: " << email << endl;
}

bool User::operator==(const User & u) {
	if (typeid(*this) != typeid(u))
		return false;
	if (this->getFName() != u.getFName() || this->getLName() != u.getLName() || this->getEmail() != u.getEmail()
		|| this->getPassword() != u.getPassword())
		return false;
	return true;
}

//Customer methods
Customer::Customer(string f, string l, string email, string psw, int s) :
	User(f, l, email, psw) {
	sub = s;
	card_registered = false;
	credit_card = "NO_CARD_REGISTERED";
	csc_code = "NO_CARD_REGISTERED";
}
void Customer::setCreditCard(string cc, string csc) {
	credit_card = cc;
	csc_code = csc;
	cc=="NO_CARD_REGISTERED" ? card_registered = false : card_registered=true;
}

void Customer::deleteCreditCard() {
		credit_card = "NO_CARD_REGISTERED";
		csc_code = "NO_CARD_REGISTERED";
		card_registered = false;
}
void Customer::show() const {
	cout << "Customer account." << endl;
	User::show();
	(card_registered) ? cout << "Credit card number: " << credit_card :
		cout << "Credit card unregistered";
	cout << endl << "Subscription status: ";
	(sub == Subscribed) ? cout << "Active" : cout << "Inactive";
}

Customer & Customer::operator=(const Customer & c)
{
	if (*this == c)
		return *this;
	first_name = c.getFName();
	last_name = c.getLName();
	email = c.getEmail();
	password = c.getPassword();
	sub = c.getSubscription();
	pair<string, string> card = c.getCreditCard();
	credit_card = card.first;
	csc_code = card.second;
	return *this;
}

//Admin methods
Admin::Admin(string f, string l, string email, string psw) :
	User(f, l, email, psw) {
	sub = Subscribed;
}

void Admin::show() const {
	cout << "Admin account." << endl;
	User::show();
	cout << "Admins are entitled to a free subscription";
}

void Admin::manageSubscription() {
	cout << "Admins are entitled to a free subscription";
}

Admin & Admin::operator=(const Admin & a)
{
	if (*this == a)
		return *this;
	first_name = a.getFName();
	last_name = a.getLName();
	email = a.getEmail();
	password = a.getPassword();
	sub = a.getSubscription();
	return *this;
}

// Broadcaster methods

Broadcaster::Broadcaster(string f, string l, string email, string psw, string c) :
	User(f, l, email, psw) {
	sub = Subscribed;
	company = c;
}

void Broadcaster::show() const {
	cout << "Broadcaster account." << endl;
	User::show();
	cout << "Company: " << company << endl
		<< "Executive accounts are entitled to a free subscription";
}

void Broadcaster::manageSubscription() {
	cout << "Executive accounts are entitled to a free subscription" << endl;
}

Broadcaster & Broadcaster::operator=(const Broadcaster b)
{
	if (*this == b)
		return *this;
	first_name = b.getFName();
	last_name = b.getLName();
	email = b.getEmail();
	password = b.getPassword();
	sub = b.getSubscription();
	company = b.getCompany();
}
