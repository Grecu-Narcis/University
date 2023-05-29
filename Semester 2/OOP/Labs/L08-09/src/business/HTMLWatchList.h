#ifndef __HTML_WATCH_LIST_H__
#define __HTML_WATCH_LIST_H__


#include "FileWatchList.h"


class HTMLWatchList : public FileWatchList
{
private:
    std::ostream& writeTutorialToFile(std::ostream& outputStream, const Tutorial& tutorialToWrite);

public:
    HTMLWatchList(const std::string& pathToFile);

    void writeToFile() override;
    void displayFile() override;
};

#endif