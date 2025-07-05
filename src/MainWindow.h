#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include "Dictionary.h"

class MainWindow : public wxFrame {
public:
    MainWindow();
private:
    Dictionary dictionary;
    wxColour buttonNormal;
    wxColour buttonHover;
    void OnAddWords(wxCommandEvent& event);
    void OnEditWords(wxCommandEvent& event);
    void OnTraining(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnButtonEnter(wxMouseEvent& event);
    void OnButtonLeave(wxMouseEvent& event);
};

#endif