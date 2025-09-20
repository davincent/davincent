#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include <wx/tokenzr.h>
#include <vector>
#include <cmath>
#include "ProcessorSingleton.h"

class MainWindow : public wxFrame
{
private:
    double result = 0.0;
    wxStatusBar* pStatusBar = nullptr;
    wxToolBar* pToolBar = nullptr;
    wxTextCtrl* textBox = nullptr;

    std::vector<wxString> buttons = { "(", ")", "%", "Clr", "<-", "7", "8", "9", "+", "sin ", "4", "5", "6", "-", "cos ", "1", "2", "3", "*", "tan ", "-", "0", ".", "/", "=" };

public:
    MainWindow();
    ~MainWindow();

    // ++ Button Events ++
    void OnButtonClick(wxCommandEvent& event);
};

#endif // MAINWINDOW_H