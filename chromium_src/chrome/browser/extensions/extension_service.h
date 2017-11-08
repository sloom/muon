// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "extensions/common/extension.h"
#include "extensions/features/features.h"

#if !BUILDFLAG(ENABLE_EXTENSIONS)
#error "Extensions must be enabled"
#endif

class HostContentSettingsMap;

class ExtensionService {
 public:
  virtual bool IsExtensionEnabled(const std::string& extension_id) const = 0;
  virtual const extensions::Extension*
                        GetInstalledExtension(const std::string& id) const = 0;
  virtual void EnableExtension(const std::string& extension_id) = 0;
  void ReloadExtension(const std::string& extension_id);
  virtual void DisableExtension(const std::string& extension_id,
                        int disable_reasons) = 0;
  virtual void NotifyExtensionLoaded(
                                  const extensions::Extension* extension) = 0;
  virtual void NotifyExtensionUnloaded(
      const extensions::Extension* extension,
      extensions::UnloadedExtensionReason reason) = 0;
  virtual const extensions::Extension* AddExtension(
                                  const extensions::Extension* extension) = 0;
  virtual const extensions::Extension* GetExtensionById(
      const std::string& id,
      bool include_disabled) const = 0;

  virtual void RegisterContentSettings(
      HostContentSettingsMap* host_content_settings_map) = 0;

  virtual bool is_ready() = 0;
};

#endif  // CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_
