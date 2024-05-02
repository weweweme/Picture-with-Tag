#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "../data/DataItem.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <fstream>
#include <vector>
#include <set>

class DataManager {
public:
    static std::vector<DataItem> LoadDataItems();
    static void OpenDataDirectory();
};

#endif // DATA_MANAGER_H
