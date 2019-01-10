#include <fstream>
#include <vector>
#include <typeinfo>
#include "userContainer.h"

userContainer::userContainer() {
	ifstream user_file;
	user_file.open("users.txt");
	string user_type, temp;
	int subscription;
	vector<string> user_data;
	while (!(user_file.eof())) {
		getline(user_file, temp, ':');
		if (temp.size()>0 && temp.at(0) == '\n')
			temp.erase(temp.begin());
		user_data.push_back(temp);
		if (temp == "endl") {
			user_type = user_data.at(0);
			if (user_type == "customer") {
				user_data.at(5) == "subscribed" ? subscription = 0 : subscription = 1;
				Customer* c = new Customer(user_data.at(1), user_data.at(2), user_data.at(3), user_data.at(4), subscription);
				(*c).setCreditCard(user_data.at(6), user_data.at(7));
				user_db.insert(user_db.begin(), c);
				user_type.clear();
			}
			else if (user_type == "admin") {
				Admin* a = new Admin(user_data.at(1), user_data.at(2), user_data.at(3), user_data.at(4));
				user_db.insert(user_db.begin(), a);
				user_type.clear();
			}
			else {
				Broadcaster* b = new Broadcaster(user_data.at(1), user_data.at(2), user_data.at(3), user_data.at(4), user_data.at(5));
				user_db.insert(user_db.begin(), b);
				user_type.clear();
			}
			user_data.clear();
		}
	}
	user_file.close();
}

void userContainer::showUserList() {
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); it++) {
		(**it).show();
		cout << endl << "-----------------------" << endl;
	}
}

void userContainer::addUser(User & u) {
	user_db.insert(user_db.begin(), &u);
	ofstream user_file;
	user_file.open("users.txt", fstream::app);
	if (!(user_file.is_open())) {
		cout << "Can't open users' data file\n";
		return;
	}
	string user_type;
	typeid(u) == typeid(Customer) ? user_type = "customer" : (typeid(u) == typeid(Admin) ? user_type = "admin" : user_type = "broadcaster");
	user_file << user_type << ":" << u.getFName() << ":" << u.getLName() << ":" << u.getEmail()
		<< ":" << u.getPassword() << ":";
	if (user_type == "broadcaster") {
		Broadcaster* b = dynamic_cast<Broadcaster*>(&u);
		user_file << b->getCompany() << ":";
	}
	u.getSubscription() == 0 ? user_file << "subscribed:" : user_file << "unsubscribed:";
	if (user_type == "customer") {
		Customer* c = dynamic_cast<Customer*>(&u);
		user_file << c->getCreditCard().first << ":" << c->getCreditCard().second;
	}
	user_file << ":endl:";
	user_file << "\n";
	user_file.close();
}

void userContainer::deleteUser(User & u) {
	user_db.erase(&(this->getUser(u)));
	ofstream user_file;
	user_file.open("users.txt", ofstream::trunc);
	user_file.close();
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		this->addUser((**it));
	}
}

bool userContainer::findUser(string email)
{
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		if ((**it).getEmail() == email)
			return true;
	}
	return false;
}

User * userContainer::getUser(string email) {
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		if ((**it).getEmail() == email) {
			return *it;
		}
	}
}

void userContainer::modifyEmail(User & u, string newmail) {
	u.changeEmail(newmail);
	ofstream user_file;
	user_file.open("users.txt", ofstream::trunc);
	user_file.close();
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		this->addUser((**it));
	}
}

void userContainer::deleteCreditCard(Customer & c)
{
	c.deleteCreditCard();
	ofstream user_file;
	user_file.open("users.txt", ofstream::trunc);
	user_file.close();
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		this->addUser((**it));
	}
}

void userContainer::changeCreditCard(Customer & c, string credit, string csc)
{
	c.setCreditCard(credit, csc);
	ofstream user_file;
	user_file.open("users.txt", ofstream::trunc);
	user_file.close();
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		this->addUser((**it));
	}
}

void userContainer::modifySubscription(User & u)
{
	u.manageSubscription();
	if (typeid(Admin) == typeid(u) || typeid(Broadcaster) == typeid(u))
		return;
	ofstream user_file;
	user_file.open("users.txt", ofstream::trunc);
	user_file.close();
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		this->addUser((**it));
	}
}

bool userContainer::findUser(User & u) {
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		if ((**it) == u)
			return true;
	}
	return false;
}


User & userContainer::getUser(User & u) {
	for (set<User*>::iterator it = user_db.begin(); it != user_db.end(); ++it) {
		if ((**it) == u) {
			return **it;
		}
	}
	
}