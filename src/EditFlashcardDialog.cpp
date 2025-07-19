#include "EditFlashcardDialog.h"

EditFlashcardDialog::EditFlashcardDialog(wxWindow* parent, Flashcard* card)
    : wxDialog(parent, wxID_ANY, "Edit Card", wxDefaultPosition, wxSize(300, 200), wxDEFAULT_DIALOG_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX), flashcard(card) {
    SetMinSize(wxSize(300, 200));
    SetMaxSize(wxSize(300, 200));
    Centre();
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    unknownCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->unknown, wxDefaultPosition, wxSize(200, -1));
    translationCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->translation, wxDefaultPosition, wxSize(200, -1));
    unknownCtrl->SetMaxLength(20);
    translationCtrl->SetMaxLength(20);

    wxButton* confirmButton = new wxButton(panel, wxID_OK, "Confirm");
    wxButton* cancelButton = new wxButton(panel, wxID_CANCEL, "Cancel");

    sizer->AddStretchSpacer();
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Unknown Word:"), 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(unknownCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Translation:"), 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(translationCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(confirmButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(cancelButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);
}

wxString EditFlashcardDialog::GetUnknown() const {
    return unknownCtrl->GetValue();
}

wxString EditFlashcardDialog::GetTranslation() const {
    return translationCtrl->GetValue();
}