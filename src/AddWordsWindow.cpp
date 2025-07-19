#include "AddWordsWindow.h"

AddWordsWindow::AddWordsWindow(wxWindow* parent, Dictionary* dict)
    : wxDialog(parent, wxID_ANY, "Add Words", wxDefaultPosition, wxSize(400, 300), wxDEFAULT_DIALOG_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX), dictionary(dict) {
    SetMinSize(wxSize(400, 300));
    SetMaxSize(wxSize(400, 300));
    Centre();
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    unknownCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    translationCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    unknownCtrl->SetMaxLength(20);
    translationCtrl->SetMaxLength(20);

    wxButton* confirmButton = new wxButton(panel, wxID_ANY, "Confirm");
    wxButton* doneButton = new wxButton(panel, wxID_ANY, "Done");

    sizer->AddStretchSpacer();
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Unknown Word:"), 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(unknownCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Translation:"), 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(translationCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(confirmButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(doneButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);

    confirmButton->Bind(wxEVT_BUTTON, &AddWordsWindow::OnConfirm, this);
    doneButton->Bind(wxEVT_BUTTON, &AddWordsWindow::OnDone, this);
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