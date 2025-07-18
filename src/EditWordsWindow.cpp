#include "EditWordsWindow.h"
#include "EditFlashcardDialog.h"

EditWordsWindow::EditWordsWindow(wxWindow* parent, Dictionary* dict)
    : wxDialog(parent, wxID_ANY, "Edit Words", wxDefaultPosition, wxSize(400, 300), wxDEFAULT_DIALOG_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX), dictionary(dict) {
    SetMinSize(wxSize(400, 300));
    SetMaxSize(wxSize(400, 300));
    Centre();
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    listCtrl = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 200), wxLC_REPORT);
    listCtrl->InsertColumn(0, "Unknown Word", wxLIST_FORMAT_LEFT, 200);
    listCtrl->InsertColumn(1, "Translation", wxLIST_FORMAT_LEFT, 200);

    for (size_t i = 0; i < dictionary->size(); ++i) {
        const Flashcard& card = dictionary->get(i);
        long index = listCtrl->InsertItem(i, card.unknown);
        listCtrl->SetItem(index, 1, card.translation);
    }

    wxButton* editButton = new wxButton(panel, wxID_ANY, "Edit");
    wxButton* deleteButton = new wxButton(panel, wxID_ANY, "Delete");
    wxButton* doneButton = new wxButton(panel, wxID_ANY, "Done");

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(editButton, 0, wxALL, 5);
    buttonSizer->Add(deleteButton, 0, wxALL, 5);
    buttonSizer->Add(doneButton, 0, wxALL, 5);

    sizer->AddStretchSpacer();
    sizer->Add(listCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);

    editButton->Bind(wxEVT_BUTTON, &EditWordsWindow::OnEdit, this);
    deleteButton->Bind(wxEVT_BUTTON, &EditWordsWindow::OnDelete, this);
    doneButton->Bind(wxEVT_BUTTON, &EditWordsWindow::OnDone, this);
}

void EditWordsWindow::OnEdit(wxCommandEvent& event) {
    long item = listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (item != -1) {
        Flashcard& card = dictionary->get(item);
        EditFlashcardDialog dialog(this, &card);
        if (dialog.ShowModal() == wxID_OK) {
            card.unknown = dialog.GetUnknown();
            card.translation = dialog.GetTranslation();
            if (card.unknown.Length() > 20 || card.translation.Length() > 20) {
                wxMessageBox("Words must not exceed 20 characters.", "Error", wxOK | wxICON_ERROR);
                return;
            }
            dictionary->save();
            listCtrl->SetItem(item, 0, card.unknown);
            listCtrl->SetItem(item, 1, card.translation);
        }
    }
}

void EditWordsWindow::OnDelete(wxCommandEvent& event) {
    long item = listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (item != -1) {
        dictionary->remove(item);
        dictionary->save();
        listCtrl->DeleteItem(item);
        for (long i = 0; i < listCtrl->GetItemCount(); ++i) {
            listCtrl->SetItemData(i, i);
        }
    }
}

void EditWordsWindow::OnDone(wxCommandEvent& event) {
    EndModal(wxID_OK);
}