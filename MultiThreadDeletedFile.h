#pragma once
#include <thread>
#include <filesystem>
#include "iostream"
#include <string>
#include "ChoseCatalogDlg.h"
#include "MultiThreadDeletedFile.h"
using namespace std;
namespace fs = filesystem;

class MultiThreadDeletedFile
{
public:

	MultiThreadDeletedFile(CProgressCtrl* progressBarCtrl = nullptr);
	void make_threads_to_deleted_folders(
		string src, 
		string name_to_delete,
		int filterMod,
		COleDateTime startFilterTime /*= COleDateTime()*/,
		COleDateTime endFilterTime /*= COleDateTime()*/);
	static bool delet_catalog(
		string path, 
		string file_like_to_del, 
		int id, 
		int filterMod, 
		COleDateTime startFilterTime /*= COleDateTime()*/,
		COleDateTime endFilterTime /*= COleDateTime()*/);
	static bool choseTime(COleDateTime startFilterTime, COleDateTime endFilterTime, int filterMods, string path);
private:

	static string upper_case(string s);

	void print_folder_tree(string src);
	int get_count_catalog_in_main_folder(string src);
	CProgressCtrl* m_progressBarCtrl;

};

