#ifndef EDITWORDSWINDOW_H
#define EDITWORDSWINDOW_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Dictionary.h"

class EditWordsWindow : public wxDialog {
public:
    EditWordsWindow(wxWindow* parent, Dictionary* dict);
    
private:
    Dictionary* dictionary;
    wxListCtrl* listCtrl;

    void OnEdit(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
    void OnDone(wxCommandEvent& event);
};

#endif