#include "TrainingWindow.h"
#include <wx/stattext.h>

TrainingWindow::TrainingWindow(wxWindow* parent, Dictionary* dict)
    : wxFrame(parent, wxID_ANY, "Train", wxDefaultPosition, wxSize(300, 200), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER), dictionary(dict), currentIndex(0) {
    SetMinSize(wxSize(300, 200));
    SetMaxSize(wxSize(300, 200));
    Centre();
    wxPanel* panel = new wxPanel(this);

    wordLabel = new wxStaticText(panel, wxID_ANY, "", wxPoint(150, 50));
    translationLabel = new wxStaticText(panel, wxID_ANY, "", wxPoint(150, 80));

    checkButton = new wxButton(panel, wxID_ANY, "Check", wxPoint(125, 110), wxSize(50, 30));
    correctButton = new wxButton(panel, wxID_ANY, "Correct", wxPoint(100, 110), wxSize(50, 30));
    incorrectButton = new wxButton(panel, wxID_ANY, "Incorrect", wxPoint(150, 110), wxSize(50, 30));
    finishButton = new wxButton(panel, wxID_ANY, "Finish", wxPoint(125, 150), wxSize(50, 30));

    translationLabel->Hide();
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
    } catch (const std::exception& e) {
        wxMessageBox("Not availabe flashcards", "Error1", wxOK | wxICON_ERROR);
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
    wxMessageBox(stats, "Session statistics:", wxOK | wxICON_INFORMATION);
    Close(true);
}