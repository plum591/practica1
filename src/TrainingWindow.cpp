#include "TrainingWindow.h"
#include <wx/stattext.h>

TrainingWindow::TrainingWindow(wxWindow* parent, Dictionary* dict)
    : wxFrame(parent, wxID_ANY, "Train", wxDefaultPosition, wxSize(300, 300), wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER), dictionary(dict), currentIndex(0) {
    Centre();
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wordLabel = new wxStaticText(panel, wxID_ANY, "");
    translationLabel = new wxStaticText(panel, wxID_ANY, "");
    translationLabel->Hide(); // Исправлено: удалён параметр true

    checkButton = new wxButton(panel, wxID_ANY, "Check");
    correctButton = new wxButton(panel, wxID_ANY, "Correct");
    incorrectButton = new wxButton(panel, wxID_ANY, "Incorrect");
    finishButton = new wxButton(panel, wxID_ANY, "Finish");

    wxBoxSizer* answerSizer = new wxBoxSizer(wxHORIZONTAL);
    answerSizer->Add(correctButton, 0, wxALL, 5);
    answerSizer->AddStretchSpacer(1);
    answerSizer->Add(incorrectButton, 0, wxALL, 5);

    mainSizer->Add(wordLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    mainSizer->Add(translationLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    mainSizer->Add(checkButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    mainSizer->Add(answerSizer, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(finishButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    correctButton->Hide();
    incorrectButton->Hide();

    panel->SetSizer(mainSizer);

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
        Layout();
    } catch (const std::exception& e) {
        wxMessageBox("No flashcards available", "Error1", wxOK | wxICON_ERROR);
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
    Layout();
}

void TrainingWindow::OnCorrect(wxCommandEvent& event) {
    try {
        dictionary->incrementCorrect(currentIndex);
        sessionCorrect++;
        dictionary->save();
        ShowNextCard();
    } catch (const std::exception& e) {
        wxMessageBox("Error when updating cor statistics", "Error2", wxOK | wxICON_ERROR);
    }
}

void TrainingWindow::OnIncorrect(wxCommandEvent& event) {
    try {
        dictionary->incrementIncorrect(currentIndex);
        sessionIncorrect++;
        dictionary->save();
        ShowNextCard();
    } catch (const std::exception& e) {
        wxMessageBox("Error when updating inc statistics", "Error3", wxOK | wxICON_ERROR);
    }
}

void TrainingWindow::OnFinish(wxCommandEvent& event) {
    wxString stats = wxString::Format("Correct answers: %d\n Incorrect answers: %d", sessionCorrect, sessionIncorrect);
    wxMessageBox(stats, "Session statistics", wxOK | wxICON_INFORMATION);
    Close(true);
}