#include "TrainingWindow.h"
#include <wx/stattext.h>
#include <wx/dcbuffer.h>

wxBEGIN_EVENT_TABLE(TrainingWindow, wxFrame)
    EVT_SIZE(TrainingWindow::OnResize)
wxEND_EVENT_TABLE()

TrainingWindow::TrainingWindow(wxWindow* parent, Dictionary* dict)
    : wxFrame(parent, wxID_ANY, "Training", wxDefaultPosition, wxSize(300, 200),
            wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX | wxFRAME_SHAPED),
      dictionary(dict), currentIndex(0), isTransparent(false) {
    SetMinSize(wxSize(300, 200));
    SetMaxSize(wxSize(300, 200));
    Centre();

    SetTransparent(255);

    panel = new wxPanel(this);
    panel->SetBackgroundStyle(wxBG_STYLE_PAINT);
    panel->Bind(wxEVT_PAINT, [this](wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(panel);
        dc.Clear();
        wxColour bgCol(255, 255, 255, 150);
        dc.SetBrush(wxBrush(bgCol));
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(panel->GetClientRect());
    });

    wordLabel = new wxStaticText(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, -1), wxALIGN_CENTRE_HORIZONTAL);
    wordLabel->Wrap(250);
    wordLabel->SetBackgroundColour(*wxWHITE);
    wordLabel->SetForegroundColour(*wxBLACK);

    translationLabel = new wxStaticText(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, -1), wxALIGN_CENTRE_HORIZONTAL);
    translationLabel->Wrap(250);
    translationLabel->SetBackgroundColour(*wxWHITE);
    translationLabel->SetForegroundColour(*wxBLACK);
    translationLabel->Hide();

    checkButton = new wxButton(panel, wxID_ANY, "Check", wxDefaultPosition, wxSize(50, 30));
    correctButton = new wxButton(panel, wxID_ANY, "Correct", wxDefaultPosition, wxSize(50, 30));
    incorrectButton = new wxButton(panel, wxID_ANY, "Incorrect", wxDefaultPosition, wxSize(50, 30));
    finishButton = new wxButton(panel, wxID_ANY, "Finish", wxDefaultPosition, wxSize(50, 30));
    correctButton->Hide(); incorrectButton->Hide();

    toggleButton = new wxButton(panel, wxID_ANY, "#", wxDefaultPosition, wxSize(20, 20));
    toggleButton->SetToolTip("Toggle transparency");
    toggleButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnToggle, this);

    checkButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnCheck, this);
    correctButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnCorrect, this);
    incorrectButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnIncorrect, this);
    finishButton->Bind(wxEVT_BUTTON, &TrainingWindow::OnFinish, this);

    ShowNextCard();
}

void TrainingWindow::OnResize(wxSizeEvent& event) {
    wxSize sz = GetClientSize();
    panel->SetSize(sz);

    int w = sz.GetWidth();
    int h = sz.GetHeight();
    wordLabel->Move((w - 250) / 2, 30);
    translationLabel->Move((w - 250) / 2, 60);
    checkButton->Move((w - 50) / 2, 90);
    correctButton->Move((w - (50*2 + 10)) / 2, 90);
    incorrectButton->Move((w - (50*2 + 10)) / 2 + 60, 90);
    finishButton->Move((w - 50) / 2, 130);

    int tw = toggleButton->GetSize().GetWidth();
    int th = toggleButton->GetSize().GetHeight();
    toggleButton->Move(w - tw - 5, h - th - 5);

    event.Skip();
}

void TrainingWindow::ShowNextCard() {
    try {
        currentIndex = dictionary->getRandomIndex();
        const Flashcard& card = dictionary->get(currentIndex);
        wordLabel->SetLabel(card.unknown);
        translationLabel->SetLabel(wxEmptyString);
        translationLabel->Hide();
        checkButton->Show();
        correctButton->Hide(); incorrectButton->Hide();
        Layout();
    } catch (const std::exception&) {
        wxMessageBox("No available flashcards", "Error", wxOK | wxICON_ERROR);
        Close(true);
    }
}

void TrainingWindow::OnCheck(wxCommandEvent& event) {
    const Flashcard& card = dictionary->get(currentIndex);
    translationLabel->SetLabel(card.translation);
    translationLabel->Show();
    checkButton->Hide();
    correctButton->Show(); incorrectButton->Show();
    Layout();
}

void TrainingWindow::OnCorrect(wxCommandEvent& event) {
    dictionary->incrementCorrect(currentIndex);
    sessionCorrect++;
    dictionary->save();
    ShowNextCard();
}

void TrainingWindow::OnIncorrect(wxCommandEvent& event) {
    dictionary->incrementIncorrect(currentIndex);
    sessionIncorrect++;
    dictionary->save();
    ShowNextCard();
}

void TrainingWindow::OnFinish(wxCommandEvent& event) {
    wxString stats = wxString::Format("Correct answers: %d\nIncorrect answers: %d", sessionCorrect, sessionIncorrect);
    wxMessageBox(stats, "Session Statistics", wxOK | wxICON_INFORMATION);
    Close(true);
}

void TrainingWindow::OnToggle(wxCommandEvent& event) {
    isTransparent = !isTransparent;
    SetTransparent(isTransparent ? 175 : 255);
}
