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
    bool SaveDataItem(const DataItem& item, const wxString& directory);
    std::vector<DataItem> SearchItemsByTags(const std::vector<DataItem>& items, const std::set<wxString>& searchTags);
    bool SaveDataItemsAsBundle(const std::vector<DataItem>& items, const wxString& directory);
};

#endif // DATA_MANAGER_H
