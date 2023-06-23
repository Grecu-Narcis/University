#ifndef __CSV_WATCH_LIST_H__
#define __CSV_WATCH_LIST_H__


#include "FileWatchList.h"


class CSVWatchList : public FileWatchList
{
public:
    CSVWatchList(const std::string& pathToFile);

    void writeToFile() override;
    void displayFile() override;
};

#endif