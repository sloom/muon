// Copyright (c) 2016 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef BRAVE_UTILITY_IMPORTER_CHROME_IMPORTER_H_
#define BRAVE_UTILITY_IMPORTER_CHROME_IMPORTER_H_

#include <stdint.h>

#include <map>
#include <set>
#include <vector>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/nix/xdg_util.h"
#include "build/build_config.h"
#include "chrome/utility/importer/importer.h"
#include "components/favicon_base/favicon_usage_data.h"

struct ImportedBookmarkEntry;

namespace base {
class DictionaryValue;
}

namespace sql {
class Connection;
}

class ChromeImporter : public Importer {
 public:
  ChromeImporter();

  // Importer:
  void StartImport(const importer::SourceProfile& source_profile,
                   uint16_t items,
                   ImporterBridge* bridge) override;

 private:
  ~ChromeImporter() override;

  static base::nix::DesktopEnvironment GetDesktopEnvironment();

  void ImportBookmarks();
  void ImportHistory();
  void ImportCookies();
  void ImportPasswords();

  // Multiple URLs can share the same favicon; this is a map
  // of URLs -> IconIDs that we load as a temporary step before
  // actually loading the icons.
  typedef std::map<int64_t, std::set<GURL>> FaviconMap;

  // Loads the urls associated with the favicons into favicon_map;
  void ImportFaviconURLs(
    sql::Connection* db,
    FaviconMap* favicon_map);

  // Loads and reencodes the individual favicons.
  void LoadFaviconData(sql::Connection* db,
                       const FaviconMap& favicon_map,
                       favicon_base::FaviconUsageDataList* favicons);

  void RecursiveReadBookmarksFolder(
    const base::DictionaryValue* folder,
    const std::vector<base::string16>& parent_path,
    bool is_in_toolbar,
    std::vector<ImportedBookmarkEntry>* bookmarks);

  double chromeTimeToDouble(int64_t time);

  base::FilePath source_path_;

  DISALLOW_COPY_AND_ASSIGN(ChromeImporter);
};

#endif  // BRAVE_UTILITY_IMPORTER_CHROME_IMPORTER_H_
