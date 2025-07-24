#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <wx/string.h>

class Flashcard {
public:
    wxString unknown;
    wxString translation;
    
    int correct_count;
    int incorrect_count;

    Flashcard() : unknown(""), translation(""), correct_count(0), incorrect_count(0) {}
    Flashcard(const wxString& u, const wxString& t) : unknown(u), translation(t), correct_count(0), incorrect_count(0) {}
    Flashcard(const wxString& u, const wxString& t, int c, int i) : unknown(u), translation(t), correct_count(c), incorrect_count(i) {}
};

#endif