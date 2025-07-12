#include "EditFlashcardDialog.h"

EditFlashcardDialog::EditFlashcardDialog(wxWindow* parent, Flashcard* card)
    : wxDialog(parent, wxID_ANY, "Edit flashcard", wxDefaultPosition, wxSize(300, 200)), flashcard(card) {
    Centre();
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    unknownCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->unknown);
    translationCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->translation);

    wxButton* confirmButton = new wxButton(panel, wxID_OK, "Done");
    wxButton* cancelButton = new wxButton(panel, wxID_CANCEL, "Cancel");

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Unknown word:"));
    sizer->Add(unknownCtrl, 0, wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Translate:"));
    sizer->Add(translationCtrl, 0, wxALL, 5);
    sizer->Add(confirmButton, 0, wxALL, 5);
    sizer->Add(cancelButton, 0, wxALL, 5);

    panel->SetSizer(sizer);
}

wxString EditFlashcardDialog::GetUnknown() const {
    return unknownCtrl->GetValue();
}

wxString EditFlashcardDialog::GetTranslation() const {
    return translationCtrl->GetValue();
}