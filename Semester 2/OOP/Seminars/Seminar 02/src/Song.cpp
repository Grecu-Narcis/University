#include "Song.h"

using namespace std;

Song::Song(const std::string& _artist, 
	const std::string& _title, 
	int _duration): artist{_artist}, title{_title}, duration{_duration}
{
	/*this->artist = _artist;
	this->title = _title;
	this->duration = _duration;*/
}

std::string Song::getTitle() const
{
	return this->title;
}

void Song::setTitle(const std::string& title)
{
	this->title = title;
}
