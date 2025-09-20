#pragma once
#include "wx/wx.h"
#include <vector>
#include "Settings.h"
#include "SettingsDialog.h"
#include <fstream>
#include "wx/numdlg.h"
#include "wx/filedlg.h"



class DrawingPanel;

class MainWindow :
    public wxFrame
{

private:
	DrawingPanel* pPanel = nullptr;

	std::vector<std::vector<bool>> gameBoard;

	//int gridSize = 15;

	int mGeneration;

	int mLivingCells;

	wxStatusBar* pStatusBar = nullptr;
	
	void UpdateStatusBar();

	wxToolBar* pToolBar = nullptr;

	wxTimer* pTimer = nullptr;

	int mTime = 10;

	Settings settings;

	SettingsDialog* settingsDialog = nullptr;

	wxMenuItem* checkedOption1 = nullptr;
	

	std::vector<std::vector<int>> _neighbors;

	std::vector<std::vector<bool>> matrix;

	wxString m_filename;

	wxMenuItem* _finite = nullptr;
	wxMenuItem* _toroidal = nullptr;
	wxMenuItem* _showGrid = nullptr;
	wxMenuItem* _is10x10 = nullptr;
	wxMenuItem* _isHUD = nullptr;


public:
	MainWindow();
	~MainWindow();

	int GetGenerations();

	int GetLivingCells();

	void OnSizeChanged(wxSizeEvent& event);

	void InitializeGrid();

	void PlayButtonClick(wxCommandEvent& event);
	void PauseButtonClick(wxCommandEvent& event);
	void NextButtonClick(wxCommandEvent& event);
	void TrashButtonClick(wxCommandEvent& event);

	int NeighborCount(int x, int y);
	void GetCurrentNeighborCount();

	void NextGeneration();

	void Timer(wxTimerEvent& event);

	void OptionsMenuClick(wxCommandEvent& event);

	void ClearMatrix();

	void CheckOption1Click(wxCommandEvent& event);
	void OnFiniteClick(wxCommandEvent& event);
	void OnToroidalClick(wxCommandEvent& event);



	void PopulateMatrix();
	void PopulateMatrixWithSeed(int seed);

	void OnNewClick(wxCommandEvent& event);
	void OnOpenClick(wxCommandEvent& event);
	void OnSaveClick(wxCommandEvent& event);
	void OnSaveAsClick(wxCommandEvent& event);
	void RandomizeClick(wxCommandEvent& event);
	void RandomizeWithSeedClick(wxCommandEvent& event);
	void OnExitClick(wxCommandEvent& event);

	// ++ I opted to pull the Save logic outside of the event handlers ++
	void SaveGame(const wxString& filename);


	void RefreshViewMenu();

	bool GetIsNeighbor();
	bool GetIsFinite();

	void OnResetSettings(wxCommandEvent& event);
	void OnImportClick(wxCommandEvent& event);

	void OnShowGridClick(wxCommandEvent& event);
	void On10x10Click(wxCommandEvent& event);
	void OnHUDClick(wxCommandEvent& event);
	

	wxDECLARE_EVENT_TABLE();

};

