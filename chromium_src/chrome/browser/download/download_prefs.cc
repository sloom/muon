// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/download/download_prefs.h"

// #include <stddef.h>

// #include <string>
// #include <vector>

#include "atom/browser/atom_download_manager_delegate.h"
#include "chrome/browser/download/trusted_sources_manager.h"

// #include "base/bind.h"
// #include "base/bind_helpers.h"
// #include "base/files/file_util.h"
// #include "base/lazy_instance.h"
// #include "base/logging.h"
// #include "base/macros.h"
// #include "base/path_service.h"
// #include "base/strings/string_split.h"
// #include "base/strings/string_util.h"
// #include "base/strings/sys_string_conversions.h"
// #include "base/strings/utf_string_conversions.h"
// #include "build/build_config.h"
#include "chrome/browser/profiles/profile.h"
// #include "chrome/browser/profiles/profile_manager.h"
// #include "chrome/common/chrome_paths.h"
#include "chrome/common/pref_names.h"
// #include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_service.h"
// #include "content/public/browser/browser_thread.h"
// #include "content/public/browser/download_item.h"
#include "content/public/browser/download_manager.h"
// #include "content/public/browser/save_page_type.h"

using content::BrowserContext;
// using content::BrowserThread;
using content::DownloadManager;

DownloadPrefs::DownloadPrefs(Profile* profile) : profile_(profile) {
  PrefService* prefs = profile->GetPrefs();
  download_path_.Init(prefs::kDownloadDefaultDirectory, prefs);
}

DownloadPrefs::~DownloadPrefs() {}

// static
DownloadPrefs* DownloadPrefs::FromDownloadManager(
    DownloadManager* download_manager) {
  atom::AtomDownloadManagerDelegate* delegate =
      static_cast<atom::AtomDownloadManagerDelegate*>(
          download_manager->GetDelegate());
  return delegate->download_prefs();
}

// static
DownloadPrefs* DownloadPrefs::FromBrowserContext(
    content::BrowserContext* context) {
  return FromDownloadManager(BrowserContext::GetDownloadManager(context));
}

base::FilePath DownloadPrefs::DownloadPath() const {
  return *download_path_;
}
