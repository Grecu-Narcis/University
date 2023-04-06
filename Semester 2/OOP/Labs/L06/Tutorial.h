#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#include <string>
using std::string;

struct Duration 
{
	int minutes, seconds;

	Duration(int minutes, int seconds)
	{
		this->minutes = minutes;
		this->seconds = seconds;
	}

	Duration()
	{
		this->minutes = 0;
		this->seconds = 0;
	}
};

class Tutorial
{
private:
	/*char *title, *presenter, *link;*/
	string title, presenter, link;
	int numberOfLikes;
	Duration duration = Duration(0, 0);

public:
	Tutorial();
	Tutorial(string title, string presenter, string link, int numberOfLikes, Duration duration);
	Tutorial(const Tutorial& other);
	Tutorial& operator=(const Tutorial& other);
	bool operator==(const Tutorial& other);

	string getTitle();
	void setTitle(string newTitle);

	string getPresenter();
	void setPresenter(string newPresenter);

	string getLink();
	void setLink(string newLink);

	int getNumberOfLikes();
	void setNumberOfLikes(int newNumberOfLikes);

	Duration getDuration();
	void setDuration(Duration newDuration);
};

#endif