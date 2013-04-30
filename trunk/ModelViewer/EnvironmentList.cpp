#include "EnvironmentList.h"

#include "ModelViewer.h"
#include <cavelib/Components/Button.h>
#include <cavelib/Components/Panel.h>
#include <cavelib/LayoutManagers/TableLayout.h>

#include <gmtl/Generate.h>

class EnvironmentListButton : public Button
{
	ModelViewer* modelViewer;
	std::string environment;
public:
	EnvironmentListButton(ModelViewer* modelViewer, std::string txt, std::string environment) : Button(txt)
	{
		this->modelViewer = modelViewer;
		this->environment = environment;
	}
	void click()
	{
		modelViewer->setEnvironment(environment);
		modelViewer->environmentList = NULL;//TODO: clean memory
	}
};


EnvironmentList::EnvironmentList(ModelViewer* modelViewer) : GUIPanel("")
{
	rootPanel = new Panel(new TableLayoutManager(1));
	rootPanel->add(new EnvironmentListButton(modelViewer, "None", ""));


	int count = 1;

	WIN32_FIND_DATA FileData;													// thingy for searching through a directory
	HANDLE hSearch;	
	hSearch = FindFirstFile("data/CubeMaps/*.*", &FileData);
	if (hSearch != INVALID_HANDLE_VALUE)										// if there are results...
	{
		while (true)														// loop through all the files
		{ 
			if((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			{
				if(FileData.cFileName[0] != '.')
				{
					rootPanel->add(new EnvironmentListButton(modelViewer, FileData.cFileName, FileData.cFileName));
					count++;
				}
			}

			if (!FindNextFile(hSearch, &FileData))								// find next file in the resultset
			{
				if (GetLastError() == ERROR_NO_MORE_FILES)						// we're finished when there are no more files
					break;
				else 
					return;													// wow, something really weird happened
			}
		}
		FindClose(hSearch);
	}


	rootPanel->reposition(0,0,2,count*0.4f);
	rootPanel->setFont(font);

	renderMatrix = gmtl::makeTrans<gmtl::Matrix44f>(gmtl::Vec3f(-1,-count*0.2f,-4));
}


EnvironmentList::~EnvironmentList(void)
{
}
