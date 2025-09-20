#pragma once

#include "wx/wx.h"

class MainWindow;

class App : public wxApp
{
	MainWindow* window = nullptr;

public:
	App();
	~App();
	virtual bool OnInit();

};