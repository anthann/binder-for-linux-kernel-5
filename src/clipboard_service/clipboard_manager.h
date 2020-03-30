#pragma once

#include <string>

class ClipboardManager
{
    std::string data_;

public:
    static ClipboardManager& getInstance() {
        static ClipboardManager instance;
        return instance;
    }
    std::string getText();
    void setText(const std::string &text);
};

