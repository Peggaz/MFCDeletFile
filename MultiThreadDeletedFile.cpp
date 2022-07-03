
#include "pch.h"
#include "MultiThreadDeletedFile.h"
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

MultiThreadDeletedFile::MultiThreadDeletedFile(CProgressCtrl* progressBarCtrl /*= nullptr*/) {
    const fs::path pathToShow{ fs::current_path() };
    m_progressBarCtrl = progressBarCtrl;
    
}

string  MultiThreadDeletedFile::upper_case(string s) {
    for_each(s.begin(), s.end(), [](char& c) {
        c = ::toupper(c);
        });
    return s;
}

bool MultiThreadDeletedFile::delet_catalog(
    string path, 
    string file_like_to_del, 
    int id,
    int filterMod,
    COleDateTime startFilterTime /*= COleDateTime()*/,
    COleDateTime endFilterTime /*= COleDateTime()*/) {
    bool ret = false;
    for (const auto& entry : fs::directory_iterator(path)) {
        const auto file_name_str = entry.path().filename().string();
        error_code ec;
        if (entry.is_directory()) {
            if (!delet_catalog(path + "/" + file_name_str, file_like_to_del, id, filterMod, startFilterTime, endFilterTime)) {
                fs::remove(path + "/" + file_name_str, ec);
            }
        }
        else if (entry.is_regular_file()) {
            bool help_ret = true;
            if (upper_case(file_name_str).find(upper_case(file_like_to_del)) != string::npos) {
                string local_path = path + "/" + file_name_str;
                if (startFilterTime == COleDateTime() && endFilterTime == COleDateTime()) {
                    fs::remove(local_path);
                    help_ret = false;
                } else if (choseTime(startFilterTime, endFilterTime, filterMod, local_path)) {
                    fs::remove(local_path);
                    help_ret = false;
                }
                ret |= help_ret;
            }
            else {
                ret = true;
            }
        }
        //else
          //  cout << "??    " << file_name_str << '\n';
    }
    return ret;
}

bool MultiThreadDeletedFile::choseTime(
    COleDateTime startFilterTime,
    COleDateTime endFilterTime,
    int filterMod,
    string path) {

    bool ret = false;
    time_t  file_time;
    struct stat filestat;
    stat(path.c_str(), &filestat);
    if (filterMod == 2) {
        file_time = filestat.st_atime;//ostatni dostêp
    } else if (filterMod == 1) {
        file_time = filestat.st_mtime;//ostatnia modyfikacja
    } else {
        file_time = filestat.st_ctime;//data powstania
    }

    COleDateTime compmpareTime(file_time);

    if (startFilterTime != COleDateTime()) {
        if(startFilterTime > compmpareTime) {
            ret = true;
        } else {
            return false;
        }
    }
    if (endFilterTime != COleDateTime()) {
        if (endFilterTime < compmpareTime) {
            ret = true;
        } else {
            return false;
        }
    }
    return ret;
}


void  MultiThreadDeletedFile::print_folder_tree(string src) {

    /*for (const auto& entry : fs::directory_iterator(src)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_directory()) {
            cout << "dir:  " << filenameStr << '\n';
        }
        else if (entry.is_regular_file()) {
            cout << "file: " << filenameStr << '\n';
        }
        else
            cout << "??    " << filenameStr << '\n';
    }

    cout << "======================\n";
    */
}

int  MultiThreadDeletedFile::get_count_catalog_in_main_folder(string src) {
    int ret = 0;
    for (const auto& entry : fs::directory_iterator(src))
        if (entry.is_directory())
            ret++;
    return ret;
}

void  MultiThreadDeletedFile::make_threads_to_deleted_folders(
    string src, 
    string name_to_delete,
    int filterMod,
    COleDateTime startFilterTime,
    COleDateTime endFilterTime) {
    /* NIe mia³em pomys³u jak ustawiæ w¹tki w tym zadaniu, mog³em to zrobiæ na kilka sposobów:
    * 1 policzyæ w¹tki procesora i ustawiæ iloœæ w¹tków zale¿n¹ od niego a nastêpnie po koleii dodawaæ katalogi
    * 2 tak jak wykona³em tzn: dla ka¿dego katalogu w œcie¿ce docelowej rozpocz¹æ nowy w¹tek
    * 3 dla ka¿dego pojedyñczego katalogu rekurencyjnie rozpocz¹æ nowy w¹tek co wyadawa³o mi siê bez sensu
    * 4 rozpisaæ klasê dziedzicz¹c¹ po w¹tkach ale to zbyt du¿y przerost formy nad treœci¹
    *
    * u¿y³em opcji 2
    */
    vector<thread> threads;
    int id_thread = 0;
    for (const auto& entry : fs::directory_iterator(src)) {
        string file_name = entry.path().filename().string();
        if (entry.is_directory()) {
            string new_src = src + "/" + file_name;
            threads.push_back(thread(delet_catalog, new_src, name_to_delete, id_thread, filterMod, startFilterTime, endFilterTime));
            id_thread++;
        }
        else if (entry.is_regular_file()) {
            if (upper_case(file_name).find(upper_case(name_to_delete)) != string::npos) {
                // cout << "usunieteo plik: " << file_name << '\n';
                fs::remove(src + "/" + file_name);
            }
        }

    }
    if (m_progressBarCtrl) {
        m_progressBarCtrl->SetRange(0, threads.size());
    }
    for (auto& th : threads) {
        th.join();
        if (m_progressBarCtrl) {
            m_progressBarCtrl->OffsetPos(1);
        }
    }
}