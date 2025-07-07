#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Flashcard.h"
#include <vector>
#include <string>

class Dictionary {
private:
    std::vector<Flashcard> flashcards;
    std::string filename = "flashcards.txt";

public:
    void load();
    void save();
    void add(const Flashcard& card);
    void remove(size_t index);
    void edit(size_t index, const Flashcard& card);
    Flashcard& get(size_t index);
    size_t size() const;
    Flashcard getRandom() const;

    size_t getRandomIndex() const;
    Flashcard& getFlashcard(size_t index); // Ensure get is public and returns reference
    void incrementCorrect(size_t index);
    void incrementIncorrect(size_t index);
};

#endif