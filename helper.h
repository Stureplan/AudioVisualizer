#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <winsock.h>



std::string WCHAR_TO_STRING(const wchar_t *wchar)
{
	std::string str = "";
	int index = 0;
	while (wchar[index] != 0)
	{
		str += (char)wchar[index];
		++index;
	}
	return str;
}

wchar_t* STRING_TO_WCHAR(const std::string &str)
{
	wchar_t wchar[260];
	unsigned int index = 0;
	while (index < str.size())
	{
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}

std::vector<std::string> ListFiles(std::string directoryName, std::string extensionName)
{
	directoryName.append(extensionName);

	WIN32_FIND_DATA FindFileData;
	wchar_t* FileName = STRING_TO_WCHAR(directoryName);
	HANDLE hFind = FindFirstFile(FileName, &FindFileData);

	std::vector<std::string> listFileNames;
	listFileNames.push_back(WCHAR_TO_STRING(FindFileData.cFileName));

	while (FindNextFile(hFind, &FindFileData))
	{
		listFileNames.push_back(WCHAR_TO_STRING(FindFileData.cFileName));
	}

	//Insert "Data/Textures" at the beginning of each string
	for (unsigned int i = 0; i < listFileNames.size(); i++)
	{
		listFileNames[i].insert(0, std::string("Music/"));
	}


	return listFileNames;
}

#endif
