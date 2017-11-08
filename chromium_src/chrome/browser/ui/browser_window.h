// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_BROWSER_WINDOW_H_
#define CHROME_BROWSER_UI_BROWSER_WINDOW_H_

#include "ui/base/base_window.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/exclusive_access/exclusive_access_context.h"
#include "content/public/browser/keyboard_event_processing_result.h"
#include "content/public/browser/native_web_keyboard_event.h"

class BrowserWindow : public ui::BaseWindow {
 public:
  enum AvatarBubbleMode {
    AVATAR_BUBBLE_MODE_DEFAULT,
    AVATAR_BUBBLE_MODE_ACCOUNT_MANAGEMENT,
    AVATAR_BUBBLE_MODE_SIGNIN,
    AVATAR_BUBBLE_MODE_ADD_ACCOUNT,
    AVATAR_BUBBLE_MODE_REAUTH,
    AVATAR_BUBBLE_MODE_CONFIRM_SIGNIN,
    AVATAR_BUBBLE_MODE_SHOW_ERROR,
  };

  virtual ~BrowserWindow() {}
  virtual bool IsVisibleOnAllWorkspaces() { return false; }
  virtual std::string GetWorkspace() { return std::string(); }

  virtual content::KeyboardEventProcessingResult PreHandleKeyboardEvent(
      const content::NativeWebKeyboardEvent& event) {
    return content::KeyboardEventProcessingResult::NOT_HANDLED;
  }
  virtual void HandleKeyboardEvent(
      const content::NativeWebKeyboardEvent& event) {}
  virtual void UpdateDevTools() {}
  virtual void UpdateToolbar(content::WebContents* contents) {}
  virtual ExclusiveAccessContext* GetExclusiveAccessContext() { return nullptr; }
};

#endif  // CHROME_BROWSER_UI_BROWSER_WINDOW_H_
