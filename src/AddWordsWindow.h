#ifndef ADDWORDSWINDOW_H
#define ADDWORDSWINDOW_H

#include <wx/wx.h>
#include <wx/timer.h>
#include "Dictionary.h"

class AddWordsWindow : public wxDialog {
public:
    AddWordsWindow(wxWindow* parent, Dictionary* dict);
    ~AddWordsWindow() override;

private:
    Dictionary* dictionary;

    wxTextCtrl* unknownCtrl;
    wxTextCtrl* translationCtrl;

    wxStaticText* unknownError;
    wxStaticText* translationError;

    wxTimer* messageTimer;
    int timerId;

    void OnConfirm(wxCommandEvent& event);
    void OnDone(wxCommandEvent& event);
    void OnMaxLen(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
};

#endif