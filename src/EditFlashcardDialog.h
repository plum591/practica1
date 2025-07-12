#ifndef EDITFLASHCARDDIALOG_H
#define EDITFLASHCARDDIALOG_H

#include <wx/wx.h>
#include "Flashcard.h"

class EditFlashcardDialog : public wxDialog {
public:
    EditFlashcardDialog(wxWindow* parent, Flashcard* card);
    wxString GetUnknown() const;
    wxString GetTranslation() const;
private:
    Flashcard* flashcard;
    wxTextCtrl* unknownCtrl;
    wxTextCtrl* translationCtrl;
};

#endif