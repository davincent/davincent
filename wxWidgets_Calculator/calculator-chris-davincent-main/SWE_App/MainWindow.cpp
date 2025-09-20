#include "MainWindow.h"
#include "ButtonFactory.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "SWE - Calculator", wxPoint(200, 200), wxSize(800, 800))
{
    textBox = new wxTextCtrl(this, 20000, "", wxPoint(0, 0), wxSize(250, 50));
    int offset = 50;
    int button_size = 50;
    int cols = 5;
    int row = 0;
    int col = 0;

    for (const wxString& buttonChar : buttons) {
        int x = col * button_size;
        int y = offset + row * button_size;
        ButtonFactory::CreateButton(this, x, y, buttonChar);

        col++;
        if (col >= cols) {
            col = 0;
            row++;
        }
    }
}

MainWindow::~MainWindow()
{
    delete textBox;
}

void MainWindow::OnButtonClick(wxCommandEvent& event)
{
    wxButton* clickedButton = static_cast<wxButton*>(event.GetEventObject());
    if (clickedButton) {
        wxString buttonLabel = clickedButton->GetLabel();

        if (buttonLabel == "Clr") {
            textBox->Clear();
            result = 0;
        }
        else if (buttonLabel == "<-") {
            wxString text = textBox->GetValue();
            if (!text.IsEmpty()) {
                text.RemoveLast();
                textBox->SetValue(text);
            }
        }
        else if (buttonLabel == "=") {
            wxString text = textBox->GetValue();
            wxString result = ProcessorSingleton::GetInstance()->ProcessExpression(text);
            textBox->SetValue(result);
        }
        else {
            textBox->AppendText(buttonLabel);
        }
    }
}

