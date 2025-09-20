#pragma once
#include "wx/wx.h"
#include "Settings.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"

class SettingsDialog :
    public wxDialog
{
public:
    SettingsDialog(wxWindow* parent, Settings* settings);

    ~SettingsDialog();

private:
    Settings* mSettings = nullptr;

    wxBoxSizer* pMainSizer = nullptr;

    wxSpinCtrl* pSpinCtrl = nullptr;
    wxSpinCtrl* timeIntervalCtrl = nullptr;
    wxColourPickerCtrl* pColourPicker = nullptr;
    wxColourPickerCtrl* pColourPicker2 = nullptr;

    wxBoxSizer* spinCtrlSizer1 = nullptr;
    wxBoxSizer* timeIntervalSizer = nullptr;

    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
