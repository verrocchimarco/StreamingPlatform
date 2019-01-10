#include "channelContainer.h"
#include <fstream>
#include <vector>

channelContainer::channelContainer() {
	ifstream channel_file;
	string temp;
	vector<string> channel_data;
	channel_file.open("channels.txt");
	while (!(channel_file.eof())) {
		getline(channel_file, temp, ':');
		if (temp.size()>0 && temp.at(0) == '\n')
			temp.erase(temp.begin());
		channel_data.push_back(temp);
		if (temp == "endl") {
			//Create channel
			string cname, cmp;
			vector<Show*> vector_shows;
			bool airingStatus;
			//entering channel data
			cname = channel_data.at(0);
			cmp = channel_data.at(1);
			channel_data.at(2) == "ON_AIR" ? airingStatus = Channel::ON_AIR : airingStatus = Channel::OFF_AIR;
			//store shows inside vector
			for (vector<string>::iterator it = channel_data.begin() + 3; it != channel_data.end(); it++) {
				if ((*it) == "{}" || (*it) == "endl") // if there's no show available or end of line is reached
					continue;
				string sname, sduration;
				double duration;
				sname = "";
				sduration = "";
				int i = 0;
				string show_details = *it;
				while (show_details.at(i) != '|' && i<show_details.size())
					sname += show_details.at(i++);
				i++;//skip '|' char
				while (i < show_details.size())
					sduration += show_details.at(i++);
				double dur = stod(sduration);
				Show* s = new Show(sname, dur); //create show and add to vector
				vector_shows.push_back(s);
			}
			//creating channel and adding shows to it
			Channel* c = new Channel(cname, cmp, airingStatus);
			channel_db.insert(channel_db.begin(), c);
			for (vector<Show*>::iterator it = vector_shows.begin(); it != vector_shows.end(); it++)
				(*c).addShow(**it);
			channel_data.clear();
			vector_shows.clear();
		}
	}
	channel_file.close();
}

void channelContainer::addChannel(Channel & c){
	channel_db.insert(channel_db.begin(), &c);
	ofstream channel_file;
	channel_file.open("channels.txt", fstream::app);
	if (!(channel_file.is_open())) {
		cout << "Can't open users' data file\n";
		return;
	}
	//print channel details
	channel_file << c.getCName() << ":" << c.getCompany() << ":";
	c.getAiringStatus() == Channel::OFF_AIR ? (channel_file << "OFF_AIR") : (channel_file << "ON_AIR");
	channel_file << ":";
	//add shows
	if (c.getShowsNumber() > 0) {
		vector<Show> shows = c.getShows();
		for (vector<Show>::iterator it = shows.begin(); it != shows.end(); it++)
			channel_file << (*it).getSName() << "|" << (*it).getDuration() << ":";
	}
	channel_file << "endl:\n";
	channel_file.close();
}

void channelContainer::deleteChannel(Channel & c){
	channel_db.erase(&c);
	ofstream channel_file;
	channel_file.open("channels.txt", ofstream::trunc);
	for (set<Channel*>::iterator it = channel_db.begin(); it != channel_db.end(); it++)
		this->addChannel(**it);
	channel_file.close();
}

void channelContainer::showChannelList() {
	for (set<Channel*>::iterator it = channel_db.begin(); it != channel_db.end(); it++) {
		(**it).show();
		cout << endl << "-----------------------" << endl;
	}
}

bool channelContainer::findChannel(Channel & c)
{
	for (set<Channel*>::iterator it = channel_db.begin(); it != channel_db.end(); it++) {
		if ((**it) == c)
			return true;
	}
	return false;
}

void channelContainer::modifyChannelName(Channel & c, string newname){
	c.changeCName(newname);
	ofstream channel_file;
	channel_file.open("channels.txt", ofstream::trunc);
	for (set<Channel*>::iterator it = channel_db.begin(); it != channel_db.end(); it++)
		this->addChannel(**it);
	channel_file.close();
}

void channelContainer::modifyAiring(Channel & c){
	c.changeAiringStatus();
	ofstream channel_file;
	channel_file.open("channels.txt", ofstream::trunc);
	for (set<Channel*>::iterator it = channel_db.begin(); it != channel_db.end(); it++)
		this->addChannel(**it);
	channel_file.close();
}

void channelContainer::addChannelShow(Channel & c, Show & s){
	channel_db.erase(&c);
	c.addShow(s);
	this->addChannel(c);
}

void channelContainer::removeChannelShow(Channel & c, Show & s){
	channel_db.erase(&c);
	c.removeShow(s);
	this->addChannel(c);
}

void channelContainer::renameChannelShow(Channel & c, Show & s, string newname){
	channel_db.erase(&c);
	s.changeSName(newname);
	this->addChannel(c);
}
