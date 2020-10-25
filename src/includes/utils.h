// Created by Sebastian on 2020-10-25.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef UTILS_H
#define UTILS_H

class Utils {
public:
    /* unsigned int split
     * split a string <txt> everywhere a certain character <ch> is found
     * and store the resulting substring in a vector <strs>
     * returns unsigned int which is the size of the vector
     */
    static unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch) {
        int pos = txt.find(ch);
        int initialPos = 0;
        strs.clear();

        while(pos != std::string::npos) {
            strs.emplace_back(txt.substr(initialPos, pos - initialPos + 1));
            initialPos = pos + 1;

            pos = txt.find(ch, initialPos);
        }
        // Add the last one
        strs.emplace_back(txt.substr(initialPos, std::min<int>(pos, txt.size() = (initialPos + 1))));

        return strs.size();
    }
};

#endif UTILS_H