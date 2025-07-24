#include "MainWindow.h"
#include "AddWordsWindow.h"
#include "EditWordsWindow.h"
#include "TrainingWindow.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Flashcard App", wxDefaultPosition, wxSize(800, 600), 
wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX) {
    SetMinSize(wxSize(800, 600));
    SetMaxSize(wxSize(800, 600));
    Centre();
    dictionary.load();

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(28, 37, 38));
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxButton* addButton = new wxButton(panel, wxID_ANY, "Add Words");
    wxButton* editButton = new wxButton(panel, wxID_ANY, "Edit Words");
    wxButton* trainButton = new wxButton(panel, wxID_ANY, "Training");
    wxButton* exitButton = new wxButton(panel, wxID_ANY, "Exit");

    addButton->SetBackgroundColour(wxColour(60, 60, 60));
    addButton->SetForegroundColour(wxColour(255, 255, 255));
    editButton->SetBackgroundColour(wxColour(60, 60, 60));
    editButton->SetForegroundColour(wxColour(255, 255, 255));
    trainButton->SetBackgroundColour(wxColour(60, 60, 60));
    trainButton->SetForegroundColour(wxColour(255, 255, 255));
    exitButton->SetBackgroundColour(wxColour(60, 60, 60));
    exitButton->SetForegroundColour(wxColour(255, 255, 255));

    sizer->AddStretchSpacer();
    sizer->Add(addButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(editButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(trainButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    sizer->Add(exitButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
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
    TrainingWindow* window = new TrainingWindow(this, &dictionary);
    window->Show(true);
}

void MainWindow::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainWindow::OnButtonEnter(wxMouseEvent& event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button) {
        button->SetBackgroundColour(wxColour(40, 40, 40));
        button->Refresh();
    }
    event.Skip();
}

void MainWindow::OnButtonLeave(wxMouseEvent& event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button) {
        button->SetBackgroundColour(wxColour(60, 60, 60));
        button->Refresh();
    }
    event.Skip();
}