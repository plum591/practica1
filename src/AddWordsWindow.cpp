#include "AddWordsWindow.h"

AddWordsWindow::AddWordsWindow(wxWindow* parent, Dictionary* dict)
    : wxDialog(parent, wxID_ANY, "Add words", wxDefaultPosition, wxSize(300, 200)), dictionary(dict) {
    Centre();
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    unknownCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    translationCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

    wxButton* confirmButton = new wxButton(panel, wxID_ANY, "Confirm");
    wxButton* doneButton = new wxButton(panel, wxID_ANY, "Done");

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Unknown word:"));
    sizer->Add(unknownCtrl, 0, wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Translation:"));
    sizer->Add(translationCtrl, 0, wxALL, 5);
    sizer->Add(confirmButton, 0, wxALL, 5);
    sizer->Add(doneButton, 0, wxALL, 5);

    panel->SetSizer(sizer);

    confirmButton->Bind(wxEVT_BUTTON, &AddWordsWindow::OnConfirm, this);
    doneButton->Bind(wxEVT_BUTTON, &AddWordsWindow::OnDone, this);
}

void AddWordsWindow::OnConfirm(wxCommandEvent& event) {
    wxString unknown = unknownCtrl->GetValue();
    wxString translation = translationCtrl->GetValue();
    if (!unknown.IsEmpty() && !translation.IsEmpty()) {
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