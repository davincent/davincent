#pragma once
#include "wx/wx.h"

class MainWindow;

class DrawingPanel :
    public wxPanel
{
public:
    DrawingPanel(wxFrame* parent, wxSize size);
    ~DrawingPanel();
};

