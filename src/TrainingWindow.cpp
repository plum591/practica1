#include "TrainingWindow.h"
#include <wx/stattext.h>

TrainingWindow::TrainingWindow(wxWindow* parent, Dictionary* dict)
    : wxFrame(parent, wxID_ANY, "Training", wxDefaultPosition, wxSize(300, 200), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX), dictionary(dict), currentIndex(0) {
    SetMinSize(wxSize(300, 200));
    SetMaxSize(wxSize(300, 200));
    Centre();
    wxPanel* panel = new wxPanel(this);

    wordLabel = new wxStaticText(panel, wxID_ANY, "", wxPoint(25, 30), wxSize(250, -1), wxALIGN_CENTRE_HORIZONTAL);
    wordLabel->Wrap(250);
    translationLabel = new wxStaticText(panel, wxID_ANY, "", wxPoint(25, 60), wxSize(250, -1), wxALIGN_CENTRE_HORIZONTAL);
    translationLabel->Wrap(250);
    translationLabel->Hide();

    checkButton = new wxButton(panel, wxID_ANY, "Check", wxPoint(125, 90), wxSize(50, 30));
    correctButton = new wxButton(panel, wxID_ANY, "Correct", wxPoint(100, 90), wxSize(50, 30));
    incorrectButton = new wxButton(panel, wxID_ANY, "Incorrect", wxPoint(150, 90), wxSize(50, 30));
    finishButton = new wxButton(panel, wxID_ANY, "Finish", wxPoint(125, 120), wxSize(50, 30));

    correctButton->Hide();
    incorrectButton->Hide();

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
        wxMessageBox("No available flashcards", "Error", wxOK | wxICON_ERROR);
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
        wxMessageBox("Error updating correct statistics", "Error", wxOK | wxICON_ERROR);
    }
}

void TrainingWindow::OnIncorrect(wxCommandEvent& event) {
    try {
        dictionary->incrementIncorrect(currentIndex);
        sessionIncorrect++;
        dictionary->save();
        ShowNextCard();
    } catch (const std::exception& e) {
        wxMessageBox("Error updating incorrect statistics", "Error", wxOK | wxICON_ERROR);
    }
}

void TrainingWindow::OnFinish(wxCommandEvent& event) {
    wxString stats = wxString::Format("Correct answers: %d\nIncorrect answers: %d", sessionCorrect, sessionIncorrect);
    wxMessageBox(stats, "Session Statistics", wxOK | wxICON_INFORMATION);
    Close(true);
}