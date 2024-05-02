#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <fstream>
#include <vector>
#include <set>
#include <wx/listbox.h>  // 변경: wx/osx/listbox.h -> wx/listbox.h
#include <boost/archive/text_iarchive.hpp>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include "DataItem.h"

class DataManager {
public:
    static std::vector<DataItem> LoadDataItems();
    static void OpenDataDirectory();
    static void SaveDataItems(wxListBox* articleList, const std::vector<DataItem>& searchResults);
    static void SaveDataItem(const DataItem& item);
};

#endif // DATA_MANAGER_H
