#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)

	EVT_BUTTON(wxID_OK, SettingsDialog::OnOK)
	EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)

wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, Settings* settings) : wxDialog(parent, wxID_ANY, "Settings"), mSettings(settings)
{
	pMainSizer = new wxBoxSizer(wxVERTICAL);

	// ++ Setting 1: SpinCtrl GridSize
	spinCtrlSizer1 = new wxBoxSizer(wxHORIZONTAL);
	spinCtrlSizer1->Add(new wxStaticText(this, wxID_ANY, "Grid Size"));
	pSpinCtrl = new wxSpinCtrl(this, 10006);
	spinCtrlSizer1->Add(pSpinCtrl);
	pMainSizer->Add(spinCtrlSizer1);

	// ++ Time Interval ++
	timeIntervalSizer = new wxBoxSizer(wxHORIZONTAL);
	timeIntervalSizer->Add(new wxStaticText(this, wxID_ANY, "Time Interval"));
	timeIntervalCtrl = new wxSpinCtrl(this, 10020);
	timeIntervalSizer->Add(timeIntervalCtrl);
	pMainSizer->Add(timeIntervalSizer);



	// ++ Setting 2: ColorPickerCtrl I want to see how these pointers that are declared here in the .cpp file behave upon going out of scope ++
	wxBoxSizer* colourPickerSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* colourPickerLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color");
	pColourPicker = new wxColourPickerCtrl(this, 10007);
	colourPickerSizer->Add(colourPickerLabel, 0, wxALIGN_CENTER);
	colourPickerSizer->Add(pColourPicker, 0, wxALIGN_CENTER);
	pMainSizer->Add(colourPickerSizer, 0, wxALL, 5);


	wxBoxSizer* colourPickerSizer2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* colourPickerLabel2 = new wxStaticText(this, wxID_ANY, "Dead Cell Color");
	pColourPicker2 = new wxColourPickerCtrl(this, 10021);
	colourPickerSizer->Add(colourPickerLabel2, 0, wxALIGN_CENTER);
	colourPickerSizer->Add(pColourPicker2, 0, wxALIGN_CENTER);
	pMainSizer->Add(colourPickerSizer2, 0, wxALL, 5);



	wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	pMainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

	SetSizer(pMainSizer);

	pSpinCtrl->SetValue(settings->GetGridSize());
	timeIntervalCtrl->SetValue(settings->GetTime());
	pColourPicker->SetColour(settings->GetLivingColor());
	pColourPicker2->SetColour(settings->GetDeadColor());




}


SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::OnOK(wxCommandEvent& event)
{
	if (mSettings) {
		mSettings->SetGridSize(pSpinCtrl->GetValue());
		mSettings->SetLivingColor(pColourPicker->GetColour()); // ++ Had to change the Set color methods to take in a const instead ++
		mSettings->SetTime(timeIntervalCtrl->GetValue());
		mSettings->SetDeadColor(pColourPicker2->GetColour());
	}
	EndModal(wxID_OK);
	mSettings->SaveSettings();
}

void SettingsDialog::OnCancel(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
}
