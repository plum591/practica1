#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <string>

class Flashcard {
public:
    std::string unknown;
    std::string translation;
    int correct_count = 0;
    int incorrect_count = 0;

    Flashcard(const std::string& u, const std::string& t) : unknown(u), translation(t) {}
};

#endif