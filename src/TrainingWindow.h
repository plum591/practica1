#ifndef TRAININGWINDOW_H
#define TRAININGWINDOW_H

#include <wx/wx.h>
#include "Dictionary.h"

class TrainingWindow : public wxFrame {
public:
    TrainingWindow(wxWindow* parent, Dictionary* dict);
private:
    Dictionary* dictionary;
    wxPanel* panel;
    wxStaticText* wordLabel;
    wxStaticText* translationLabel;
    wxButton* checkButton;
    wxButton* correctButton;
    wxButton* incorrectButton;
    wxButton* finishButton;
    wxButton* toggleButton;
    size_t currentIndex;
    int sessionCorrect = 0;
    int sessionIncorrect = 0;
    bool isTransparent;

    void OnCheck(wxCommandEvent& event);
    void OnCorrect(wxCommandEvent& event);
    void OnIncorrect(wxCommandEvent& event);
    void OnFinish(wxCommandEvent& event);
    void OnToggle(wxCommandEvent& event);
    void OnResize(wxSizeEvent& event);
    void ShowNextCard();

    wxDECLARE_EVENT_TABLE();
};

#endif