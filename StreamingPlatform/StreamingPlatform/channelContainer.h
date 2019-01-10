#pragma once
#include "channel.h"
#include <set>

/*
Works in the same way of userContainer, storing channels (and their related palimpsest)
*/

class channelContainer {
private:
	set<Channel*> channel_db;
public:
	channelContainer();
	~channelContainer() {}
	void addChannel(Channel & c);
	void deleteChannel(Channel & c);
	void showChannelList();
	bool findChannel(Channel & c);
	//Channel & getChannel(Channel & c);
	//Channel & getChannel(string & cname);
	void modifyChannelName(Channel & c, string newname);
	void modifyAiring(Channel & c);
	void addChannelShow(Channel & c, Show & s);
	void removeChannelShow(Channel & c, Show & s);
	void renameChannelShow(Channel & c, Show & s, string newname);
};