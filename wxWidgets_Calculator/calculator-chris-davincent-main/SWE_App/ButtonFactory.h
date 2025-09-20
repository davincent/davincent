#pragma once
#include "wx/wx.h"
#include "MainWindow.h"

class ButtonFactory
{public:
	static wxButton* CreateButton(MainWindow* parent, int x, int y, wxString character);
};

