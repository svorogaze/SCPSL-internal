#pragma once
#include "../resolver/Unity/Structures/System_String.hpp"
#include <string>
namespace helper {

    Unity::System_String to_unity_string(std::string s) {
        Unity::System_String str;
        str.m_iLength = s.length();
        for (int i = 0; i < s.size(); ++i) {
            str.m_wString[i] = s[i];
        }
        return str;
    }

};