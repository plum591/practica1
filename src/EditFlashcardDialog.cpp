#include "EditFlashcardDialog.h"

EditFlashcardDialog::EditFlashcardDialog(wxWindow* parent, Flashcard* card)
    : wxDialog(parent, wxID_ANY, "Edit flashcard", wxDefaultPosition, wxSize(300, 200)), flashcard(card) {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    unknownCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->unknown);
    translationCtrl = new wxTextCtrl(panel, wxID_ANY, flashcard->translation);

    wxButton* confirmButton = new wxButton(panel, wxID_OK, "Apply");
    wxButton* cancelButton = new wxButton(panel, wxID_CANCEL, "Cancel");

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Unknown Word:"));
    sizer->Add(unknownCtrl, 0, wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Translation:"));
    sizer->Add(translationCtrl, 0, wxALL, 5);
    sizer->Add(confirmButton, 0, wxALL, 5);
    sizer->Add(cancelButton, 0, wxALL, 5);

    panel->SetSizer(sizer);
}

std::string EditFlashcardDialog::GetUnknown() const {
    return unknownCtrl->GetValue().ToStdString();
}

std::string EditFlashcardDialog::GetTranslation() const {
    return translationCtrl->GetValue().ToStdString();
}