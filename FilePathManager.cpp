#include "stdafx.h"
#include "FilePathManager.h"
#define MAX_PATH 256
//#include "shlwapi.h"
//#pragma comment(lib,"shlwapi.lib")

FilePathManager::FilePathManager(void)
{
}

FilePathManager::~FilePathManager(void)
{
}

bool FilePathManager::GetAbsolutePath(char * strRelativePath, char **strAbsolutePath)
{
	char path[MAX_PATH];

#ifdef JOSBUILD

	//GetCurrentDirectory(MAX_PATH, path);

	*strAbsolutePath = strRelativePath;

	//if(!PathFileExists(strAbsolutePath)) 
	//	return false;

	return true;
#else  // Linux
	

	getcwd(path, MAX_PATH/2);
	if(strRelativePath[0]!='/')
		strcat(path,"/");
	strncat(path, strRelativePath, MAX_PATH/2-1);
	// for check existence use access(returns 0 if OK)
	bool pathExists = !access(path, O_RDONLY);  
	if(!pathExists){
		getcwd(path, MAX_PATH/2);
		strcat(path, "/lib");
		if(strRelativePath[0]!='/')
			strcat(path,"/");
		strncat(path, strRelativePath, MAX_PATH/2 - 1);
		pathExists = !access(path, O_RDONLY);
	}
	if(pathExists){
		*strAbsolutePath = path;
		return true;
	}
	return false;
#endif

}
