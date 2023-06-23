#include "UI.h"
#include <Windows.h>
#include "CSVPlayList.h"
#include "RepositoryExceptions.h"

using namespace std;

int main()
{
	system("color f4");

	try
	{
		Repository repo("Songs.txt");
		FilePlaylist* p = new CSVPlaylist{};
		Controller ctrl(repo, p, SongValidator{});
		UI ui(ctrl);
		ui.run();
		delete p;
	}
	catch (FileException&)
	{
		cout << "Repository file could not be opened! The application will terminate." << endl;
		return 1;
	}

	return 0;
}