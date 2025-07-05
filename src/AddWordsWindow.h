#ifndef ADDWORDSWINDOW_H
#define ADDWORDSWINDOW_H

#include <wx/wx.h>
#include "Dictionary.h"

class AddWordsWindow : public wxDialog {
public:
    AddWordsWindow(wxWindow* parent, Dictionary* dict);
private:
    Dictionary* dictionary;
    wxTextCtrl* unknownCtrl;
    wxTextCtrl* translationCtrl;
    void OnConfirm(wxCommandEvent& event);
    void OnDone(wxCommandEvent& event);
};

#endif