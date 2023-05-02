#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#include <string>
using namespace std;

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

	string toString() const
	{
		return to_string(minutes) + "," + to_string(seconds);
	}
};

class Tutorial
{
private:
	string title, presenter, link;
	int numberOfLikes;
	Duration duration = Duration(0, 0);

public:
	Tutorial();
	Tutorial(string title, string presenter, string link, int numberOfLikes, Duration duration);
	Tutorial(const Tutorial& other);
	Tutorial& operator=(const Tutorial& other);
	bool operator==(const Tutorial& other);

	string getTitle()  const;
	void setTitle(string newTitle);

	string getPresenter() const;
	void setPresenter(string newPresenter);

	string getLink() const;
	void setLink(string newLink);

	int getNumberOfLikes() const;
	void setNumberOfLikes(int newNumberOfLikes);

	Duration getDuration() const;
	void setDuration(Duration newDuration);

	string toString() const;

	bool isNull() const;

	friend ostream& operator<<(ostream& outputStream, const Tutorial& tutorialToPrint);
	friend istream& operator>>(istream& inputStream, Tutorial& tutorialRead);
};

#endif