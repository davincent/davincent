#include "ButtonFactory.h"

wxButton* ButtonFactory::CreateButton(MainWindow* parent, int x, int y, wxString character)
{
	wxButton* button = new wxButton(parent, wxID_ANY, character, wxPoint(x, y), wxSize(50, 50));
	button->Bind(wxEVT_BUTTON, &MainWindow::OnButtonClick, parent);
	return button;
}
