#include "AddWordsWindow.h"

AddWordsWindow::AddWordsWindow(wxWindow* parent, Dictionary* dict)
    : wxDialog(parent, wxID_ANY, "Add Words",
               wxDefaultPosition, wxDefaultSize,
               wxDEFAULT_DIALOG_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX),
      dictionary(dict)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    unknownCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    unknownCtrl->SetMaxLength(20);
    unknownError = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

    translationCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    translationCtrl->SetMaxLength(20);
    translationError = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

    wxButton* confirmButton = new wxButton(panel, wxID_OK, "Confirm");
    wxButton* doneButton = new wxButton(panel, wxID_CANCEL, "Done");

    wxStdDialogButtonSizer* buttonSizer = new wxStdDialogButtonSizer();
    buttonSizer->AddButton(confirmButton);
    buttonSizer->AddButton(doneButton);
    buttonSizer->Realize();

    sizer->AddStretchSpacer();
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Unknown Word:"), 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(unknownCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(unknownError, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Translation:"), 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(translationCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(translationError, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(panel, 1, wxEXPAND | wxALL, 0);
    SetSizer(mainSizer);
    Layout();

    const wxSize fixedSize(300, 250);
    SetSize(fixedSize);
    SetMinSize(fixedSize);
    SetMaxSize(fixedSize);
    CentreOnScreen();

    confirmButton->Bind(wxEVT_BUTTON, &AddWordsWindow::OnConfirm, this);
    doneButton->Bind(wxEVT_BUTTON, &AddWordsWindow::OnDone, this);
    unknownCtrl->Bind(wxEVT_TEXT_MAXLEN, &AddWordsWindow::OnMaxLen, this);
    translationCtrl->Bind(wxEVT_TEXT_MAXLEN, &AddWordsWindow::OnMaxLen, this);

    timerId = wxID_HIGHEST + 2;
    messageTimer = new wxTimer(this, timerId);
    Bind(wxEVT_TIMER, &AddWordsWindow::OnTimer, this, timerId);
}

AddWordsWindow::~AddWordsWindow() {
    if (messageTimer && messageTimer->IsRunning())
        messageTimer->Stop();
    delete messageTimer;
}

void AddWordsWindow::OnConfirm(wxCommandEvent& event) {
    wxString unknown = unknownCtrl->GetValue();
    wxString translation = translationCtrl->GetValue();

    if (!unknown.IsEmpty() && !translation.IsEmpty()) {
        if (unknown.Length() > 20 || translation.Length() > 20) {
            wxMessageBox("Words must not exceed 20 characters.", "Error", wxOK | wxICON_ERROR);
            return;
        }

        Flashcard card(unknown, translation);
        dictionary->add(card);
        dictionary->save();

        unknownCtrl->Clear();
        translationCtrl->Clear();
    }
}

void AddWordsWindow::OnDone(wxCommandEvent& event) {
    EndModal(wxID_OK);
}

void AddWordsWindow::OnMaxLen(wxCommandEvent& event) {
    wxTextCtrl* ctrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());

    if (ctrl == unknownCtrl) {
        unknownError->SetLabel("Max 20 symbols");
        unknownError->SetForegroundColour(*wxRED);
    } else if (ctrl == translationCtrl) {
        translationError->SetLabel("Max 20 symbols");
        translationError->SetForegroundColour(*wxRED);
    }

    messageTimer->Start(3000, wxTIMER_ONE_SHOT);
    event.Skip();
}

void AddWordsWindow::OnTimer(wxTimerEvent& event) {
    if (event.GetId() == timerId) {
        unknownError->SetLabel("");
        translationError->SetLabel("");
    }
}