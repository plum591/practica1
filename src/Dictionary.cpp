#include "Dictionary.h"
#include <fstream>
#include <sstream>

void Dictionary::load() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string unknown, translation;
        int correct, incorrect;
        std::getline(ss, unknown, '|');
        std::getline(ss, translation, '|');
        ss >> correct >> incorrect;
        flashcards.emplace_back(unknown, translation);
        flashcards.back().correct_count = correct;
        flashcards.back().incorrect_count = incorrect;
    }
    file.close();
}

void Dictionary::save() {
    std::ofstream file(filename);
    for (const auto& card : flashcards) {
        file << card.unknown << "|" << card.translation << "|"
             << card.correct_count << " " << card.incorrect_count << "\n";
    }
    file.close();
}

void Dictionary::add(const Flashcard& card) {
    flashcards.push_back(card);
}

void Dictionary::remove(size_t index) {
    if (index < flashcards.size()) {
        flashcards.erase(flashcards.begin() + index);
    }
}

void Dictionary::edit(size_t index, const Flashcard& card) {
    if (index < flashcards.size()) {
        flashcards[index] = card;
    }
}

Flashcard& Dictionary::get(size_t index) {
    if (index >= flashcards.size()) {
        throw std::out_of_range("Index out of range");
    }
    return flashcards[index];
}

size_t Dictionary::size() const {
    return flashcards.size();
}

Flashcard Dictionary::getRandom() const {
    if (flashcards.empty()) {
        throw std::runtime_error("No flashcards available");
    }
    int total_weight = 0;
    for (const auto& card : flashcards) {
        total_weight += card.incorrect_count + 1;
    }
    int r = rand() % total_weight;
    int cumulative = 0;
    for (const auto& card : flashcards) {
        cumulative += card.incorrect_count + 1;
        if (r < cumulative) {
            return card;
        }
    }
    return flashcards.back();
}

size_t Dictionary::getRandomIndex() const {
    if (flashcards.empty()) {
        throw std::runtime_error("No flashcards available");
    }
    int total_weight = 0;
    for (const auto& card : flashcards) {
        total_weight += card.incorrect_count + 1;
    }
    int r = rand() % total_weight;
    int cumulative = 0;
    for (size_t i = 0; i < flashcards.size(); ++i) {
        cumulative += flashcards[i].incorrect_count + 1;
        if (r < cumulative) {
            return i;
        }
    }
    return flashcards.size() - 1;
}

void Dictionary::incrementCorrect(size_t index) {
    if (index < flashcards.size()) {
        flashcards[index].correct_count++;
        save();
    }
}

void Dictionary::incrementIncorrect(size_t index) {
    if (index < flashcards.size()) {
        flashcards[index].incorrect_count++;
        save();
    }
}