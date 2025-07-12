#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <wx/string.h>

class Flashcard {
public:
    wxString unknown;
    wxString translation;
    int correct_count = 0;
    int incorrect_count = 0;

    Flashcard() : unknown(""), translation(""), correct_count(0), incorrect_count(0) {}
    Flashcard(const wxString& u, const wxString& t) : unknown(u), translation(t) {}
};

#endif