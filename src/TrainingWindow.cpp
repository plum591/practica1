#include "TrainingWindow.h"
#include <wx/stattext.h>

TrainingWindow::TrainingWindow(wxWindow* parent, Dictionary* dict)
    : wxFrame(parent, wxID_ANY, "Train", wxDefaultPosition, wxSize(300, 200), wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE) {
    dictionary = dict;
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wordLabel = new wxStaticText(panel, wxID_ANY, "");
    translationLabel = new wxStaticText(panel, wxID_ANY, "");
    checkButton = new wxButton(panel, wxID_ANY, "Check");
    correctButton = new wxButton(panel, wxID_ANY, "Correct");
    incorrectButton = new wxButton(panel, wxID_ANY, "Incorrect");
    finishButton = new wxButton(panel, wxID_ANY, "Finish");

    sizer->Add(wordLabel, 0, wxALL, 10);
    sizer->Add(translationLabel, 0, wxALL, 10);
    sizer->Add(checkButton, 0, wxALL, 5);
    sizer->Add(correctButton, 0, wxALL, 5);
    sizer->Add(incorrectButton, 0, wxALL, 5);
    sizer->Add(finishButton, 0, wxALL, 5);

    correctButton->Hide();
    incorrectButton->Hide();
    translationLabel->Hide();

    panel->SetSizer(sizer);

    checkButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnCheck, this);
    correctButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnCorrect, this);
    incorrectButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnIncorrect, this);
    finishButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnFinish, this);

    ShowNextCard();
}

void TrainingWindow::ShowNextCard() {
    try {
        currentIndex = dictionary->getRandomIndex();
        const Flashcard& card = dictionary->get(currentIndex);
        wordLabel->SetLabel(card.unknown);
        translationLabel->SetLabel("");
        translationLabel->Hide();
        checkButton->Show();
        correctButton->Hide();
        incorrectButton->Hide();
    } catch (const std::exception& e) {
        wxMessageBox("No flashcards available", "Error", wxOK | wxICON_ERROR);
        Close(true);
    }
}

void TrainingWindow::OnCheck(wxCommandEvent& event) {
    const Flashcard& card = dictionary->get(currentIndex);
    translationLabel->SetLabel(card.translation);
    translationLabel->Show();
    checkButton->Hide();
    correctButton->Show();
    incorrectButton->Show();
}

void TrainingWindow::OnCorrect(wxCommandEvent& event) {
    try {
        dictionary->incrementCorrect(currentIndex);
        sessionCorrect++;
        dictionary->save();
        ShowNextCard();
    } catch (const std::exception& e) {
        // Handle error, e.g., wxMessageBox
    }
}

void TrainingWindow::OnIncorrect(wxCommandEvent& event) {
    try {
        dictionary->incrementIncorrect(currentIndex);
        sessionIncorrect++;
        dictionary->save();
        ShowNextCard();
    } catch (const std::exception& e) {
        // Handle error
    }
}

void TrainingWindow::OnFinish(wxCommandEvent& event) {
    wxString stats = wxString::Format("Correct answers: %d\n Incorrect answers: %d", sessionCorrect, sessionIncorrect);
    wxMessageBox(stats, "Statistics session", wxOK | wxICON_INFORMATION);
    Close(true);
}