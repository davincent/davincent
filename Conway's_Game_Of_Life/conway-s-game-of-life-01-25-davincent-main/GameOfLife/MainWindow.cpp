#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "wx/filedlg.h"
#include "Settings.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)

	EVT_SIZE(MainWindow::OnSizeChanged)
	EVT_MENU(10001, MainWindow::PlayButtonClick)
	EVT_MENU(10002, MainWindow::PauseButtonClick)
	EVT_MENU(10003, MainWindow::NextButtonClick)
	EVT_MENU(10004, MainWindow::TrashButtonClick)
	EVT_TIMER(10005, MainWindow::Timer)
	EVT_MENU(10008, MainWindow::OptionsMenuClick)
	EVT_MENU(10009, MainWindow::CheckOption1Click)
	EVT_MENU(wxID_NEW, MainWindow::OnNewClick)
	EVT_MENU(wxID_OPEN, MainWindow::OnOpenClick)
	EVT_MENU(wxID_SAVE, MainWindow::OnSaveClick)
	EVT_MENU(wxID_SAVEAS, MainWindow::OnSaveAsClick)
	EVT_MENU(10010, MainWindow::RandomizeClick)
	EVT_MENU(10011, MainWindow::RandomizeWithSeedClick)
	EVT_MENU(wxID_EXIT, MainWindow::OnExitClick)
	EVT_MENU(10012, MainWindow::OnFiniteClick)
	EVT_MENU(10013, MainWindow::OnToroidalClick)
	EVT_MENU(10014, MainWindow::OnResetSettings)
	EVT_MENU(10015, MainWindow::OnImportClick)
	EVT_MENU(10016, MainWindow::OnShowGridClick)
	EVT_MENU(10017, MainWindow::On10x10Click)
	EVT_MENU(10018, MainWindow::OnHUDClick)

wxEND_EVENT_TABLE()

class DrawingPanel;

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 800))
{
	pStatusBar = CreateStatusBar();

	pToolBar = CreateToolBar();
	wxBitmap playIcon(play_xpm);
	pToolBar->AddTool(10001, "Play", playIcon);
	

	wxBitmap pauseIcon(pause_xpm);
	pToolBar->AddTool(10002, "Pause", pauseIcon);
	

	wxBitmap nextIcon(next_xpm);
	pToolBar->AddTool(10003, "Next", nextIcon);
	

	wxBitmap trashIcon(trash_xpm);
	pToolBar->AddTool(10004, "Trash", trashIcon);
	
	pToolBar->Realize();
	
	pPanel = new DrawingPanel(this, wxSize(100, 100), gameBoard, &_neighbors, settings.isNeighborCount, settings.isShowGrid, settings.is10x10);
	//this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChanged, this);
	settings.LoadSettings();
	pPanel->SetSettings(&settings);

	InitializeGrid();

	UpdateStatusBar();

	this->Layout();

	pTimer = new wxTimer(this, 10005);

	wxMenuBar* menu = new wxMenuBar();
	SetMenuBar(menu);

	// ++ File Menu button ++
	wxMenu* settingsMenu = new wxMenu();
	settingsMenu->Append(wxID_NEW, "New");
	settingsMenu->Append(wxID_OPEN, "Open");
	settingsMenu->Append(wxID_SAVE, "Save");
	settingsMenu->Append(wxID_SAVEAS, "Save As...");
	settingsMenu->Append(10008, "Settings");
	settingsMenu->Append(10014, "Reset Settings");
	settingsMenu->Append(10010, "Randomize");
	settingsMenu->Append(10011, "Randomize with Seed");
	settingsMenu->Append(10015, "Import Game Board");
	settingsMenu->Append(wxID_EXIT, "Exit");
	menu->Append(settingsMenu, "File");



	// ++ View Menu button ++
	wxMenu* viewMenu = new wxMenu();
	checkedOption1 = new wxMenuItem(viewMenu, 10009, "Show Neighbor Count", "", wxITEM_CHECK);
	checkedOption1->SetCheckable(true);
	viewMenu->Append(checkedOption1);
	checkedOption1->Check(settings.isNeighborCount);

	_showGrid = new wxMenuItem(viewMenu, 10016, "Show Grid Lines", "", wxITEM_CHECK);
	_showGrid->SetCheckable(true);
	viewMenu->Append(_showGrid);
	_showGrid->Check(settings.isShowGrid);

	_is10x10 = new wxMenuItem(viewMenu, 10017, "Show 10x10 Grid", "", wxITEM_CHECK);
	_is10x10->SetCheckable(true);
	viewMenu->Append(_is10x10);
	_is10x10->Check(settings.is10x10);

	_isHUD = new wxMenuItem(viewMenu, 10018, "Show HUD", "", wxITEM_CHECK);
	_isHUD->SetCheckable(true);
	viewMenu->Append(_isHUD);
	_isHUD->Check(settings.isHUD);

	_finite = new wxMenuItem(viewMenu, 10012, "Finite", "", wxITEM_CHECK);
	_finite->SetCheckable(true);
	viewMenu->Append(_finite);


	_toroidal = new wxMenuItem(viewMenu, 10013, "Toroidal", "", wxITEM_CHECK);
	_toroidal->SetCheckable(true);
	viewMenu->Append(_toroidal);

	_finite->Check(settings.isFinite);


	menu->Append(viewMenu, "View");

	matrix.resize(settings.gridSize);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].resize(settings.gridSize);
	}


	pPanel->SetNeighbors(&_neighbors);
	//pPanel->SetNeighbors(&_neighbors);
	pPanel->SetGeneration(&mGeneration);
	pPanel->SetLivingCells(&mLivingCells);

	PopulateMatrix();
	RefreshViewMenu();

}

MainWindow::~MainWindow()
{
	delete pPanel;
	delete pTimer;
}

int MainWindow::GetGenerations()
{
	return mGeneration;
}

int MainWindow::GetLivingCells()
{
	return mLivingCells;
}





void MainWindow::OnSizeChanged(wxSizeEvent& event)
{

	wxSize size = this->GetSize();
	this->Refresh();

	event.Skip();
}

void MainWindow::InitializeGrid()
{
	gameBoard.resize(settings.gridSize);
	_neighbors.resize(settings.gridSize);
	for (int i = 0; i < settings.gridSize; i++)
	{
		gameBoard[i].resize(settings.gridSize, false);
		_neighbors[i].resize(settings.gridSize);
	}
	pPanel->SetGridSize(settings.gridSize);
}

void MainWindow::PlayButtonClick(wxCommandEvent& event)
{
	pTimer->Start(50);
}

void MainWindow::PauseButtonClick(wxCommandEvent& event)
{
	pTimer->Stop();
}

void MainWindow::NextButtonClick(wxCommandEvent& event)
{
	NextGeneration();
}

void MainWindow::TrashButtonClick(wxCommandEvent& event)
{
	pTimer->Stop();
	for (int i = 0; i < settings.gridSize; i++) {
		for (int j = 0; j < settings.gridSize; j++) {
			gameBoard[i][j] = false;

		}
	}
	mGeneration = 0;
	mLivingCells = 0;

	UpdateStatusBar();
	this->Refresh();
}

int MainWindow::NeighborCount(int x, int y)
{
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;

			int _x = x + i;
			int _y = y + j;

			if (settings.isFinite == false) {
				// ++ Calculate with torodial universe ++
				if (_x < 0) _x = settings.gridSize - 1;
				if (_x >= settings.gridSize) _x = 0;
				if (_y < 0) _y = settings.gridSize - 1;
				if (_y >= settings.gridSize) _y = 0;
			}
			else {
				// ++ Calculate with finite universe ++
				if ((_x < 0 || _x >= settings.gridSize) || (_y < 0 || _y >= settings.gridSize)) continue; // ++ Combined some logic here from previous versions ++
			}

			if (gameBoard[_x][_y]) {
				count += 1;
			}
		}
	}
	
	return count;
}

void MainWindow::GetCurrentNeighborCount()
{
	for (int i = 0; i < settings.gridSize; i++) {
		for (int j = 0; j < settings.gridSize; j++) {
			_neighbors[i][j] = NeighborCount(i, j);
		}
	}
}

void MainWindow::UpdateStatusBar()
{
	wxString statusText = wxString::Format("Generation: %d, Living Cells: %d", mGeneration, mLivingCells);
	pStatusBar->SetStatusText(statusText);
}

void MainWindow::NextGeneration()
{
	std::vector<std::vector<bool>> sandbox;
	mLivingCells = 0;

	sandbox.resize(settings.gridSize);
	for (int i = 0; i < settings.gridSize; i++)
	{
		sandbox[i].resize(settings.gridSize);
	}

	for (int i = 0; i < settings.gridSize; i++) {
		for (int j = 0; j < settings.gridSize; j++) {
			if (gameBoard[i][j]) {
				if (NeighborCount(i, j) == 2 || NeighborCount(i, j) == 3) {
					sandbox[i][j] = true;
					mLivingCells += 1;
				}
				else {
					sandbox[i][j] = false;
				}
			}

			if (!gameBoard[i][j] && NeighborCount(i, j) == 3) {
				sandbox[i][j] = true;
				mLivingCells += 1;
			}
		}
	}


	
	GetCurrentNeighborCount();

	gameBoard.swap(sandbox);

	mGeneration += 1;
	UpdateStatusBar();
	this->Refresh();
}

void MainWindow::Timer(wxTimerEvent& event)
{
	NextGeneration();
}

void MainWindow::OptionsMenuClick(wxCommandEvent& event)
{
	settingsDialog = new SettingsDialog(this, &settings);
	if (settingsDialog->ShowModal() == wxID_OK) {
		InitializeGrid();
		pPanel->Refresh();
	}
}

void MainWindow::ClearMatrix()
{
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].clear();
	}
	matrix.resize(0);

	matrix.clear();
	matrix.resize(0);

}

void MainWindow::CheckOption1Click(wxCommandEvent& event)
{
	settings.isNeighborCount = !settings.isNeighborCount;
	settings.SaveSettings();
	this->Refresh();
}

void MainWindow::OnFiniteClick(wxCommandEvent& event)
{
	settings.isFinite = true;
	settings.SaveSettings();
	this->Refresh();
	RefreshViewMenu();
	event.Skip();
}

void MainWindow::OnToroidalClick(wxCommandEvent& event)
{
	settings.isFinite = false;
	settings.SaveSettings();
	this->Refresh();
	RefreshViewMenu();
	event.Skip();
}

void MainWindow::PopulateMatrix()
{

	matrix.resize(settings.gridSize);
	srand(time(NULL));

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			int num = rand();
			if (num % 3 == 0) {
				matrix[i][j] = true;
			}
			else {
				matrix[i][j] = false;
			}
		}
	}

}

void MainWindow::PopulateMatrixWithSeed(int seed)
{
	srand(seed);

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			int num = rand();
			if (num % 3 == 0) {
				matrix[i][j] = true;
			}
			else {
				matrix[i][j] = false;
			}
		}
	}
}

void MainWindow::OnNewClick(wxCommandEvent& event)
{

	TrashButtonClick(event);
	ClearMatrix();
	m_filename = "";
	this->Refresh();
}

void MainWindow::OnOpenClick(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Open Game of Life File", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);
	if (fileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	m_filename = fileDialog.GetPath();

	ClearMatrix();

	std::string buffer;
	std::ifstream fileStream;

	int index = 0;
	fileStream.open((std::string)fileDialog.GetPath());

	if (fileStream.is_open()) {
		while (!fileStream.eof()) {
			std::getline(fileStream, buffer);
			if (buffer.size() == 0) { break; }
			settings.SetGridSize(buffer.size());
			if (matrix.size() == 0) {
				matrix.resize(buffer.size());
				_neighbors.resize(buffer.size());
			}

			matrix[index].resize(buffer.size());
			_neighbors[index].resize(buffer.size());
			for (int i = 0; i < buffer.size(); i++) {
				if (buffer[i] == '*') {
					matrix[index][i] = true;
				}
				else {
					matrix[index][i] = false;
				}
			}
			index++;
		}
		fileStream.close();
		gameBoard.swap(matrix);
		this->Refresh();
	}
	event.Skip();

}

void MainWindow::OnSaveClick(wxCommandEvent& event)
{
	if (m_filename.empty()) {
		OnSaveAsClick(event);
	}
	else {
		SaveGame(m_filename);
	}

	event.Skip();
}

void MainWindow::OnSaveAsClick(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Save Game of Life File", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (fileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	wxString m_filename = fileDialog.GetPath();
	SaveGame(m_filename);

	event.Skip();
}

void MainWindow::RandomizeClick(wxCommandEvent& event)
{
	PopulateMatrix();
	gameBoard.swap(matrix);
	this->Refresh();
}

void MainWindow::RandomizeWithSeedClick(wxCommandEvent& event)
{
	long seed = wxGetNumberFromUser(
		"Enter a seed for randomization:",
		"Seed:",
		"Randomize with Seed",
		0, // Default value
		0, // Minimum value
		LONG_MAX, // Maximum value (adjust as needed)
		this
	);
	if (seed != -1) { // -1 indicates the user canceled
		PopulateMatrixWithSeed(seed);
	}
	gameBoard.swap(matrix);
	this->Refresh();
}

void MainWindow::OnExitClick(wxCommandEvent& event)
{
	Close();
}

void MainWindow::SaveGame(const wxString& filename)
{

	std::ofstream fileStream(filename.mb_str());

	if (fileStream.is_open()) {
		for (int i = 0; i < gameBoard.size(); i++) {
			for (int j = 0; j < gameBoard[i].size(); j++) {
				if (gameBoard[i][j]) {
					fileStream << '*';
				}
				else {
					fileStream << '.';
				}
			}
			fileStream << '\n';
		}
		fileStream.close();
	}

}

void MainWindow::RefreshViewMenu()
{
	_finite->Check(settings.isFinite);
	_toroidal->Check(!settings.isFinite);
}

bool MainWindow::GetIsNeighbor()
{
	return settings.isNeighborCount;
}

bool MainWindow::GetIsFinite()
{
	return settings.isFinite;
}

void MainWindow::OnResetSettings(wxCommandEvent& event)
{
	settings.ResetSettings();
	this->Refresh();
}

void MainWindow::OnImportClick(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Import Game of Life File", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);
	if (fileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	m_filename = fileDialog.GetPath();

	ClearMatrix();

	std::string buffer;
	std::ifstream fileStream;

	int index = 0;
	fileStream.open((std::string)fileDialog.GetPath());

	if (fileStream.is_open()) {
		while (!fileStream.eof()) {
			std::getline(fileStream, buffer);

			if (buffer.size() == 0) { break; }
			if (index == settings.GetGridSize()) { break; }
			
			if (buffer.size() > settings.GetGridSize()){
				if (matrix.size() == 0) {
					matrix.resize(settings.GetGridSize());
					_neighbors.resize(settings.GetGridSize());
				}

				matrix[index].resize(settings.GetGridSize());
				_neighbors[index].resize(settings.GetGridSize());


				for (int i = 0; i < settings.GetGridSize(); i++) {
					if (buffer[i] == '*') {
						matrix[index][i] = true;
					}
					else {
						matrix[index][i] = false;
					}
				}
			}
			else {
				if (matrix.size() == 0) {
					matrix.resize(settings.GetGridSize());
					_neighbors.resize(settings.GetGridSize());
				}

				matrix[index].resize(settings.GetGridSize());
				_neighbors[index].resize(settings.GetGridSize());


				for (int i = 0; i < buffer.size(); i++) {
					if (buffer[i] == '*') {
						matrix[index][i] = true;
					}
					else {
						matrix[index][i] = false;
					}
				}
			}
			index++;
		}
		fileStream.close();
		gameBoard.swap(matrix);
		// ++ fill in the dead space ++
		for (int i = 0; i < gameBoard[0].size(); i++) {
			if (gameBoard[i].size() != gameBoard[0].size()) {
				gameBoard[i].resize(gameBoard[0].size());
			}
		}




		this->Refresh();
	}
	event.Skip();
}

void MainWindow::OnShowGridClick(wxCommandEvent& event)
{
	settings.isShowGrid = !settings.isShowGrid;
	settings.SaveSettings();
	event.Skip();
	this->Refresh();
}

void MainWindow::On10x10Click(wxCommandEvent& event)
{
	settings.is10x10 = !settings.is10x10;
	settings.SaveSettings();
	event.Skip();
	this->Refresh();
}

void MainWindow::OnHUDClick(wxCommandEvent& event)
{
	settings.isHUD = !settings.isHUD;
	settings.SaveSettings();
	event.Skip();
	this->Refresh();
}

