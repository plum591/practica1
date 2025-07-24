#include "Dictionary.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h> 

void Dictionary::load() {
    if (wxFile::Exists(filename)) {
        wxFileInputStream input(filename);
        if (input.IsOk()) {
            wxTextInputStream text(input, "\t\n\r", wxConvUTF8);
            while (!input.Eof()) {
                wxString line = text.ReadLine();
                wxArrayString parts = wxSplit(line, '|');
                if (parts.size() >= 2) {
                    wxString unknown = parts[0];
                    wxString translation = parts[1];
                    int correct = 0, incorrect = 0;
                    if (parts.size() >= 3) {
                        wxArrayString stats = wxSplit(parts[2], ' ');
                        if (stats.size() == 2) {
                            long tempCorrect, tempIncorrect;
                            stats[0].ToLong(&tempCorrect);
                            stats[1].ToLong(&tempIncorrect);
                            correct = static_cast<int>(tempCorrect);
                            incorrect = static_cast<int>(tempIncorrect);
                        }
                    }
                    Flashcard card(unknown, translation);
                    card.correct_count = correct;
                    card.incorrect_count = incorrect;
                    flashcards.push_back(card);
                }
            }
        }
    }
}

void Dictionary::save() {
    wxFileOutputStream output(filename);
    if (output.IsOk()) {
        wxTextOutputStream text(output, wxEOL_NATIVE, wxConvUTF8);
        for (const auto& card : flashcards) {
            text << card.unknown << "|" << card.translation << "|" << card.correct_count << " " << card.incorrect_count << "\n";
        }
    }
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

size_t Dictionary::getRandomIndex() const {
    if (flashcards.empty()) {
        throw std::runtime_error("No flashcards available");
    }
    int total_weight = 0;
    for (const auto& card : flashcards) {
        int weight = std::max(1, card.incorrect_count + 1 - card.correct_count);
        total_weight += weight;
    }
    int r = rand() % total_weight;
    int cumulative = 0;
    for (size_t i = 0; i < flashcards.size(); ++i) {
        int weight = std::max(1, flashcards[i].incorrect_count + 1 - flashcards[i].correct_count);
        cumulative += weight;
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