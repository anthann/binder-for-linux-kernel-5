#include "clipboard_manager.h"

std::string ClipboardManager::getText() {
  return data_;
}

void ClipboardManager::setText(const std::string &text) {
  data_ = text;
}

