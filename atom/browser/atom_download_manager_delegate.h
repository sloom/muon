// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_ATOM_DOWNLOAD_MANAGER_DELEGATE_H_
#define ATOM_BROWSER_ATOM_DOWNLOAD_MANAGER_DELEGATE_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "chrome/browser/download/download_path_reservation_tracker.h"
#include "content/public/browser/download_manager_delegate.h"

class DownloadPrefs;
class Profile;

namespace content {
class DownloadManager;
}

namespace atom {

class AtomDownloadManagerDelegate : public content::DownloadManagerDelegate {
 public:
  explicit AtomDownloadManagerDelegate(content::DownloadManager* manager,
      Profile* profile);
  virtual ~AtomDownloadManagerDelegate();

  void OnDownloadPathGenerated(
    int32_t download_id,
    const content::DownloadTargetCallback& callback,
    PathValidationResult result,
    const base::FilePath& target_path);

  // content::DownloadManagerDelegate:
  void Shutdown() override;
  bool DetermineDownloadTarget(
      content::DownloadItem* download,
      const content::DownloadTargetCallback& callback) override;
  bool ShouldOpenDownload(
      content::DownloadItem* download,
      const content::DownloadOpenDelayedCallback& callback) override;
  void GetNextId(const content::DownloadIdCallback& callback) override;

  DownloadPrefs* download_prefs() { return download_prefs_.get(); }

 private:
  // Get the save path set on the associated api::DownloadItem object
  void GetItemSavePath(content::DownloadItem* item, base::FilePath* path);

  content::DownloadManager* download_manager_;
  Profile* profile_;
  std::unique_ptr<DownloadPrefs> download_prefs_;

  base::WeakPtrFactory<AtomDownloadManagerDelegate> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(AtomDownloadManagerDelegate);
};

}  // namespace atom

#endif  // ATOM_BROWSER_ATOM_DOWNLOAD_MANAGER_DELEGATE_H_
