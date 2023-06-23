#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#include <string>

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

	std::string toString() const
	{
		return std::to_string(minutes) + "," + std::to_string(seconds);
	}
};

class Tutorial
{
private:
	std::string title, presenter, link;
	int numberOfLikes;
	Duration duration = Duration(0, 0);

public:
	Tutorial();
	Tutorial(std::string title, std::string presenter, std::string link, int numberOfLikes, Duration duration);
	Tutorial(const Tutorial& other);
	Tutorial& operator=(const Tutorial& other);
	bool operator==(const Tutorial& other);

	std::string getTitle()  const;
	void setTitle(std::string newTitle);

	std::string getPresenter() const;
	void setPresenter(std::string newPresenter);

	std::string getLink() const;
	void setLink(std::string newLink);

	int getNumberOfLikes() const;
	void setNumberOfLikes(int newNumberOfLikes);

	Duration getDuration() const;
	void setDuration(Duration newDuration);

	std::string toString() const;

	bool isNull() const;

	friend std::ostream& operator<<(std::ostream& outputStream, const Tutorial& tutorialToPrint);
	friend std::istream& operator>>(std::istream& inputStream, Tutorial& tutorialRead);
};

#endif