#ifndef EDITFLASHCARDDIALOG_H
#define EDITFLASHCARDDIALOG_H

#include <wx/wx.h>
#include <wx/timer.h>
#include "Flashcard.h"

class EditFlashcardDialog : public wxDialog {
public:
    EditFlashcardDialog(wxWindow* parent, Flashcard* card);
    ~EditFlashcardDialog() override;

    wxString GetUnknown() const;
    wxString GetTranslation() const;

private:
    Flashcard* flashcard;
    wxTextCtrl* unknownCtrl;
    wxTextCtrl* translationCtrl;
    wxStaticText* unknownError;
    wxStaticText* translationError;
    wxTimer* messageTimer;
    int timerId;

    void OnMaxLen(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
};

#endif