#include "EditFlashcardDialog.h"

EditFlashcardDialog::EditFlashcardDialog(wxWindow* parent, Flashcard* card)
    : wxDialog(parent, wxID_ANY, "Edit Card", wxDefaultPosition, wxDefaultSize, 
    wxDEFAULT_DIALOG_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX),
    flashcard(card)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* content = new wxBoxSizer(wxVERTICAL);

    content->Add(new wxStaticText(panel, wxID_ANY, "Unknown Word:"), 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    unknownCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->unknown, wxDefaultPosition, wxSize(200, -1));
    unknownCtrl->SetMaxLength(20);
    content->Add(unknownCtrl, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    unknownError = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    content->Add(unknownError, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    content->Add(new wxStaticText(panel, wxID_ANY, "Translation:"), 0, wxTOP|wxALIGN_CENTER_HORIZONTAL, 2);
    translationCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->translation, wxDefaultPosition, wxSize(200, -1));
    translationCtrl->SetMaxLength(20);
    content->Add(translationCtrl, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL, 2);
    translationError = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    content->Add(translationError, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    panel->SetSizer(content);
    mainSizer->Add(panel, 1, wxEXPAND|wxALL, 10);
    mainSizer->Add(CreateButtonSizer(wxOK|wxCANCEL), 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 10);

    SetSizer(mainSizer);
    Layout();

    const wxSize fixedSize(300, 250);
    SetSize(fixedSize);
    SetMinSize(fixedSize);
    SetMaxSize(fixedSize);
    CentreOnScreen();

    timerId = wxID_HIGHEST + 1;
    messageTimer = new wxTimer(this, timerId);
    Bind(wxEVT_TIMER, &EditFlashcardDialog::OnTimer, this, timerId);

    unknownCtrl->Bind(wxEVT_TEXT_MAXLEN, &EditFlashcardDialog::OnMaxLen, this);
    translationCtrl->Bind(wxEVT_TEXT_MAXLEN, &EditFlashcardDialog::OnMaxLen, this);
}

EditFlashcardDialog::~EditFlashcardDialog()
{
    if (messageTimer->IsRunning())
        messageTimer->Stop();
    delete messageTimer;
}

wxString EditFlashcardDialog::GetUnknown() const {
    return unknownCtrl->GetValue();
}

wxString EditFlashcardDialog::GetTranslation() const {
    return translationCtrl->GetValue();
}

void EditFlashcardDialog::OnMaxLen(wxCommandEvent& event) {
    wxTextCtrl* ctrl = static_cast<wxTextCtrl*>(event.GetEventObject());
    if (ctrl == unknownCtrl) {
        unknownError->SetLabel("Max 20 symbols");
        unknownError->SetForegroundColour(*wxRED);
    } else {
        translationError->SetLabel("Max 20 symbols");
        translationError->SetForegroundColour(*wxRED);
    }
    messageTimer->Start(3000, wxTIMER_ONE_SHOT);
    event.Skip();
}

void EditFlashcardDialog::OnTimer(wxTimerEvent& event) {
    if (event.GetId() == timerId) {
        unknownError->SetLabel("");
        translationError->SetLabel("");
    }
}
