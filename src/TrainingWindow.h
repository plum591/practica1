#ifndef TRAININGWINDOW_H
#define TRAININGWINDOW_H

#include <wx/wx.h>
#include "Dictionary.h"

class TrainingWindow : public wxFrame {
public:
    TrainingWindow(wxWindow* parent, Dictionary* dict);
private:
    Dictionary* dictionary;
    wxStaticText* wordLabel;
    wxStaticText* translationLabel;
    wxButton* checkButton;
    wxButton* correctButton;
    wxButton* incorrectButton;
    wxButton* finishButton;
    size_t currentIndex;
    int sessionCorrect = 0;
    int sessionIncorrect = 0;
    void OnCheck(wxCommandEvent& event);
    void OnCorrect(wxCommandEvent& event);
    void OnIncorrect(wxCommandEvent& event);
    void OnFinish(wxCommandEvent& event);
    void ShowNextCard();
};

#endif