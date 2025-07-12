#include "MainWindow.h"
#include "AddWordsWindow.h"
#include "EditWordsWindow.h"
#include "TrainingWindow.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Flashcard App", wxDefaultPosition, wxSize(800, 600)),
    buttonNormal(60, 60, 60), buttonHover(40, 40, 40) {
    Centre();
    dictionary.load();

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(28, 37, 38));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddStretchSpacer();

    wxButton* addButton = new wxButton(panel, wxID_ANY, "Add words");
    wxButton* editButton = new wxButton(panel, wxID_ANY, "Edit words");
    wxButton* trainButton = new wxButton(panel, wxID_ANY, "Train");
    wxButton* exitButton = new wxButton(panel, wxID_ANY, "Exit");

    addButton->SetBackgroundColour(buttonNormal);
    addButton->SetForegroundColour(wxColour(255, 255, 255));
    editButton->SetBackgroundColour(buttonNormal);
    editButton->SetForegroundColour(wxColour(255, 255, 255));
    trainButton->SetBackgroundColour(buttonNormal);
    trainButton->SetForegroundColour(wxColour(255, 255, 255));
    exitButton->SetBackgroundColour(buttonNormal);
    exitButton->SetForegroundColour(wxColour(255, 255, 255));

    sizer->Add(addButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    sizer->Add(editButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    sizer->Add(trainButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    sizer->Add(exitButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);

    addButton->Bind(wxEVT_BUTTON, &MainWindow::OnAddWords, this);
    editButton->Bind(wxEVT_BUTTON, &MainWindow::OnEditWords, this);
    trainButton->Bind(wxEVT_BUTTON, &MainWindow::OnTraining, this);
    exitButton->Bind(wxEVT_BUTTON, &MainWindow::OnExit, this);

    addButton->Bind(wxEVT_ENTER_WINDOW, &MainWindow::OnButtonEnter, this);
    addButton->Bind(wxEVT_LEAVE_WINDOW, &MainWindow::OnButtonLeave, this);
    editButton->Bind(wxEVT_ENTER_WINDOW, &MainWindow::OnButtonEnter, this);
    editButton->Bind(wxEVT_LEAVE_WINDOW, &MainWindow::OnButtonLeave, this);
    trainButton->Bind(wxEVT_ENTER_WINDOW, &MainWindow::OnButtonEnter, this);
    trainButton->Bind(wxEVT_LEAVE_WINDOW, &MainWindow::OnButtonLeave, this);
    exitButton->Bind(wxEVT_ENTER_WINDOW, &MainWindow::OnButtonEnter, this);
    exitButton->Bind(wxEVT_LEAVE_WINDOW, &MainWindow::OnButtonLeave, this);
}

void MainWindow::OnAddWords(wxCommandEvent& event) {
    AddWordsWindow dialog(this, &dictionary);
    dialog.ShowModal();
}

void MainWindow::OnEditWords(wxCommandEvent& event) {
    EditWordsWindow dialog(this, &dictionary);
    dialog.ShowModal();
}

void MainWindow::OnTraining(wxCommandEvent& event) {
    TrainingWindow* window = new TrainingWindow(nullptr, &dictionary);
    window->Show(true);
}

void MainWindow::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainWindow::OnButtonEnter(wxMouseEvent& event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button) {
        button->SetBackgroundColour(buttonHover);
        button->Refresh();
    }
    event.Skip();
}

void MainWindow::OnButtonLeave(wxMouseEvent& event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button) {
        button->SetBackgroundColour(buttonNormal);
        button->Refresh();
    }
    event.Skip();
}