#pragma once
#include <iostream>
#include <vector>
#include <string>

/* Channels represent the streaming platform's offer; each channel consists of no more than 5 different programs which
make the palimpsest. Each channel is linked to a company, which is the broadcasting company that distributes said
channel
*/
using namespace std;

class Show {
private:
	string show_name;
	double duration;
public:
	Show() : show_name("Dummy show"), duration(0.0) {}
	Show(string & sname, double & d) : show_name(sname), duration(d) {}
	~Show() {}
	void changeSName(string & newname) { show_name = newname; }
	void changeDuration(double & newd) { duration = newd; }
	string getSName() { return show_name; }
	double getDuration() { return duration; }
	void show() const;
	bool operator==(const Show & s);
};
class Channel {
private:
	int num_shows;
	string channel_name, company;
	vector<Show> channel_shows;
	bool airing;
public:
	static const int MAX_SHOWS = 5;
	static const bool ON_AIR = true;
	static const bool OFF_AIR = false;
	Channel(string & cname, string & c, const bool air = OFF_AIR) : channel_name(cname), company(c),
		airing(air), num_shows(0) {}
	~Channel() {}
	void show() const;
	string getCName() const { return channel_name; }
	string getCompany() const { return company; }
	int getShowsNumber() const { return num_shows; }
	bool getAiringStatus() const { return airing; }
	vector<Show> getShows() const { return channel_shows; }
	void changeAiringStatus() { (airing == ON_AIR) ? airing = OFF_AIR : airing = ON_AIR; }
	void changeCName(string & newname) { channel_name = newname; }
	void addShow(Show & s);
	void removeShow(Show & s);
	Show & getShow(string & show_name);
	bool findShow(string & show_name);
	bool operator==(const Channel & c);
};