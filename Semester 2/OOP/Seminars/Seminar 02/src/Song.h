#pragma once
#include <string>

class Song
{
private:
	std::string artist;
	std::string title;
	int duration;

public:
	Song(const std::string& _artist, 
		const std::string& _title,
		int _duration);

	std::string getTitle() const;
	void setTitle(const std::string& title);
};