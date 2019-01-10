#include "channel.h"

void Show::show() const {
	cout << "\tShow title: " << show_name << endl;
	cout << "\tDuration: " << duration << " minutes" << endl;
}

bool Show::operator==(const Show & s) {
	if (show_name == s.show_name && duration == s.duration)
		return true;
	else return false;
}

void Channel::show() const {
	cout << "Channel name: " << channel_name << endl
		<< "Broadcasted by: " << company << endl
		<< "Airing status: ";
	airing == ON_AIR ? cout << "ON AIR" : cout << "OFF AIR";
	cout << endl << "Current shows avaiable:\n";
	if (channel_shows.size() == 0) {
		cout << "No shows registered for this channel\n";
	}
	else {
		for (int i = 0; i<channel_shows.size(); i++)
			channel_shows.at(i).show();
	}
}
void Channel::addShow(Show & s) {
	if (num_shows == MAX_SHOWS)
		cout << "Can't add more shows" << endl;
	else {
		++num_shows;
		channel_shows.push_back(s);
	}
}

void Channel::removeShow(Show & s) {
	for (vector<Show>::iterator it = channel_shows.begin(); it != channel_shows.end(); ++it) {
		if ((*it) == s) {
			channel_shows.erase(it);
			num_shows--;
			return;
		}
		if (it == channel_shows.end())
			cout << "Error: show not found\n";
	}
}

Show & Channel::getShow(string & show_name) {
	for (vector<Show>::iterator it = channel_shows.begin(); it != channel_shows.end(); ++it) {
		if ((*it).getSName() == show_name) {
			return *it;
		}
	}
}

bool Channel::findShow(string & show_name) {
	for (vector<Show>::iterator it = channel_shows.begin(); it != channel_shows.end(); ++it) {
		if ((*it).getSName() == show_name) {
			return true;
		}
	}
	return false;
}

bool Channel::operator==(const Channel & c)
{
	if (this->getCName() != c.getCName() || this->getCompany() != c.getCompany() || this->getShowsNumber() != c.getShowsNumber())
		return false;
	vector<Show> this_shows = channel_shows;
	vector<Show> c_shows = c.getShows();
	for (int i = 0; i < this_shows.size(); i++) {
		if (!(this_shows[i] == c_shows[i]))
			return false;
	}
	return true;
}
