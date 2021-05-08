#include "HelloSDL.h"
#include "FileManager.h"
#include "Log.h"
#include "Stringify.h"

#ifndef _WIN32
#include <sys/param.h>
#include <dirent.h>
#else
#include <windows.h>
#endif

#include <stdio.h>

#include <Windows.h>
#include <tchar.h> 
#include <strsafe.h>
#pragma comment(lib, "User32.lib")


bool FileManager::SetContents(std::string Filename, std::string Content, bool Relative) {
	if (Filename == "") return false;

	if (Relative) Filename = GetCWD() + DIR_SEPARATOR + Filename;

	std::ofstream FileHandle;

	FileHandle.open(Filename.c_str());
	if (!FileHandle.is_open()) return false;

	FileHandle << Content;
	FileHandle.close();

	return true;
}


std::string FileManager::GetContents(std::string Filename, bool Relative) {
	if (Filename == "") return "";

	if (Relative) Filename = GetCWD() + DIR_SEPARATOR + Filename;

	std::string Content;
	std::ifstream FileHandle;

	FileHandle.open(Filename.c_str());

	if (FileHandle.is_open()) {
		while (FileHandle.good()) {
			std::string Buffer;
			getline(FileHandle, Buffer);
			if (Buffer == "") continue;

			Content += Buffer + "\n";
		}

		FileHandle.close();
	}

	return Content;
}


std::vector<std::string> FileManager::GetFilesInFolder(std::string Folder) {
	std::vector<std::string> List;

	std::string CWD = GetCWD();
	std::string Path = CWD;

	if (Folder != "") Path += DIR_SEPARATOR + Folder;

#ifdef __APPLE__
	NSError* Error;

	NSString* PathNS = [NSString stringWithUTF8String : Path.c_str()];
	NSArray* DirectoryContents = [[NSFileManager defaultManager]contentsOfDirectoryAtPath:PathNS error : &Error];

	for (id File in DirectoryContents) {
		std::string Filename = Path + DIR_SEPARATOR + [File cStringUsingEncoding : 1];

		List.push_back(Filename);
	}
#elif _WIN32
	HANDLE dirHandle = NULL;
	WIN32_FIND_DATAA FileHandle;
	
	std::string winPath(Path + DIR_SEPARATOR + std::string("*"));

	if ((dirHandle = FindFirstFileA(winPath.c_str(), &FileHandle)) != INVALID_HANDLE_VALUE) {
		do {
			if (std::string(FileHandle.cFileName) == ".") continue;
			if (std::string(FileHandle.cFileName) == "..") continue;

			std::string Filename = Path + DIR_SEPARATOR + FileHandle.cFileName;
			List.push_back(Filename);
		} while (FindNextFileA(dirHandle, &FileHandle) != false);
		FindClose(dirHandle);
	}
	else {
		Log("Unable to open directory: %s", Path.c_str());
	}
#else
	DIR* DirHandle = NULL;
	dirent* FileHandle = NULL;

	// Needs improvement
	if ((DirHandle = opendir(Folder.c_str())) != NULL) {
		while ((FileHandle = readdir(DirHandle)) != NULL) {
			if (std::string(FileHandle->d_name) == ".")  continue;
			if (std::string(FileHandle->d_name) == "..") continue;

			std::string Filename = Path + DIR_SEPARATOR + FileHandle->d_name;

			Log("Found File: %s", Filename.c_str());

			List.push_back(Filename);
		}

		closedir(DirHandle);
	}
	else {
		Log("Unable to open directory : %s", Path.c_str());
	}
#endif

	return List;
}


std::string FileManager::GetCWD() {
	std::string CWD;

#ifdef __APPLE__
	NSString* ResourcePath = [[NSBundle mainBundle]resourcePath];
	CWD = [ResourcePath cStringUsingEncoding : 1];
#elif defined(_WIN32)
	char buffer[MAX_PATH];
	CWD = ((GetCurrentDirectoryA(MAX_PATH, buffer) > 0) ? std::string(buffer) : std::string(""));
#else
	char Buffer[MAXPATHLEN];
	CWD = (getcwd(Buffer, MAXPATHLEN) ? std::string(Buffer) : std::string(""));
#endif

	return CWD;
}


std::string FileManager::GetFilenameWithoutExt(std::string Filename) {
	std::vector<std::string> Parts = Stringify::Explode(Filename, DIR_SEPARATOR);
	std::string NewFilename = Parts[Parts.size() - 1];

	// TODO: Filename could potentially have one or more dots
	Parts = Stringify::Explode(NewFilename, ".");
	NewFilename = Parts[0];

	return NewFilename;
}


std::string FileManager::GetFilenameExt(std::string Filename) {
	std::vector<std::string> Parts = Stringify::Explode(Filename, ".");

	return (Parts.size() <= 1 ? "" : Parts[Parts.size() - 1]);
}


std::string FileManager::ListFiles(std::wstring Folder) {
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	//Log("\nTarget directory is %ls\n\n", Folder);
	wcout << "Target directory is " << Folder.c_str() << endl;
	cout << "Current directory is " << GetCWD() << endl;

	// Prepare string for use with FindFile functions. 
	// First, copy the string to a buffer then append '\*' to the directory name.

	StringCchCopy(szDir, MAX_PATH, Folder.c_str());
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE == hFind) {
		Log("\nERROR: %s\n", "FindFirstFile");
	}

	// List all the files in the directory with some info about them
	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else {
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
		}
	}    while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) {
		Log("\nERROR: %s\n", "FindFirstFile");
	}

	FindClose(hFind);

	return "";
}
