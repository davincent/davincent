#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)

	EVT_PAINT(DrawingPanel::OnPaint)
	EVT_LEFT_UP(DrawingPanel::OnMouseUp)

wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent, wxSize size, std::vector<std::vector<bool>>& gameBoard, std::vector<std::vector<int>>* neighbors, bool& isNeighborCount, bool& isShowGrid, bool& is10x10) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), size), newBoard(gameBoard), pNeighbors(neighbors), _isNeighborCount(isNeighborCount), _isShowGrid(isShowGrid), _is10x10(is10x10)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	//this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	//this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
}

DrawingPanel::~DrawingPanel()
{
}

void DrawingPanel::OnPaint(wxPaintEvent& paintEvent)
{

	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);

	if (!context) { return; }

	if (_isShowGrid) {
		context->SetPen(*wxBLACK);
	}
	else {
		context->SetPen(wxTransparentColor);
	}
	
	context->SetBrush(*wxWHITE);

	wxSize size = GetSize();

	float cellWidth = size.GetWidth() / (float)dpSettings->gridSize;
	float cellHeight = size.GetHeight() / (float)dpSettings->gridSize;

	context->SetFont(wxFontInfo(16), *wxRED);

	for (int i = 0; i < newBoard.size(); i++) {
		for (int j = 0; j < newBoard.size(); j++) {
			if (newBoard[i][j]) {
				context->SetBrush(dpSettings->GetLivingColor());
			}
			else {
				context->SetBrush(dpSettings->GetDeadColor());
			}
			context->DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
			// ++ Neighbor Count Display ++

			wxString cellText = std::to_string((*pNeighbors)[i][j]);
			double textWidth, textHeight;

			if (_isNeighborCount && (*pNeighbors)[i][j] != 0) {
				context->GetTextExtent(cellText, &textWidth, &textHeight);
				context->DrawText(cellText, (i * cellWidth) + cellWidth / 2 - (textWidth / 2), (j * cellHeight) + cellHeight / 2 - (textHeight / 2));
			}

			
		}
	}


	if (_is10x10){
		int numOfLines = dpSettings->gridSize / 10;

		wxPen* pen = new wxPen(*wxBLACK, 2); // ++ I opted for a size od 2 on this one ++
		dc.SetPen(*pen);
		for (int i = 0; i < numOfLines; i++) {

			wxPoint vStart(cellWidth * (i * 10), 0);

			wxPoint vEnd(cellWidth * (i * 10), this->GetSize().y);

			dc.DrawLine(vStart, vEnd);

		}

		for (int i = 0; i < numOfLines; i++) {

			wxPoint vStart(0, cellHeight * (i * 10));

			wxPoint vEnd(this->GetSize().x, cellHeight * (i * 10));

			dc.DrawLine(vStart, vEnd);

		}
		delete pen;
	}

	

	// ++ HUD Logic ++


	if (dpSettings->isHUD) {
		double xText, yText;
		wxString line1 = "Number of Generations: " + std::to_string(*pGenerations);
		context->SetFont(wxFontInfo(16), *wxRED);
		context->GetTextExtent(line1, &xText, &yText);
		context->DrawText(line1, 5, GetSize().y - (yText * 4));

		wxString line2 = "Number of Living Cells: " + std::to_string(*pLivingCells);
		context->SetFont(wxFontInfo(16), *wxRED);
		context->GetTextExtent(line2, &xText, &yText);
		context->DrawText(line2, 5, GetSize().y - (yText * 3));


		wxString type;
		if (dpSettings->isFinite) {
			type = "Finite";
		}
		else {
			type = "Torodial";
		}

		wxString line3 = "Boundary Type: " + type;
		context->SetFont(wxFontInfo(16), *wxRED);
		context->GetTextExtent(line3, &xText, &yText);
		context->DrawText(line3, 5, GetSize().y - (yText * 2));



		wxString line4 = "Universe Size: " + std::to_string(dpSettings->gridSize);
		context->SetFont(wxFontInfo(16), *wxRED);
		context->GetTextExtent(line4, &xText, &yText);
		context->DrawText(line4, 5, GetSize().y - (yText * 1));
	}
	




	// ++ Not sure if this is the correct place for this but it cleans up the leaks ++
	delete context;
	
	
}

void DrawingPanel::OnSize(wxSize& _size)
{
	this->SetSize(_size);
	this->Refresh();
}

void DrawingPanel::SetGridSize(int _gridsize)
{
	dpSettings->gridSize = _gridsize;
	this->Refresh(); // redraw the panel with the new grid size
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
	int _x = event.GetX();
	int _y = event.GetY();

	wxSize size = GetSize();

	float cellWidth = size.GetWidth() / (float)dpSettings->gridSize;
	float cellHeight = size.GetHeight() / (float)dpSettings->gridSize;

	int row = _x / cellWidth;
	int column = _y / cellHeight;

	newBoard[row][column] = !newBoard[row][column];


	// ++ Little repative but this is for testing ++


	this->Refresh();
}

void DrawingPanel::SetSettings(Settings* settings)
{
	this->dpSettings = settings;
}

int DrawingPanel::NeighborCount(int x, int y)
{
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;

			int _x = x + i;
			int _y = y + j;

			if (dpSettings->isFinite == false) {
				// ++ Calculate with torodial universe ++
				if (_x < 0) _x = dpSettings->gridSize - 1;
				if (_x >= dpSettings->gridSize) _x = 0;
				if (_y < 0) _y = dpSettings->gridSize - 1;
				if (_y >= dpSettings->gridSize) _y = 0;
			}
			else {
				// ++ Calculate with finite universe ++
				if ((_x < 0 || _x >= dpSettings->gridSize) || (_y < 0 || _y >= dpSettings->gridSize)) continue; // ++ Combined some logic here from previous versions ++
			}

			if (newBoard[_x][_y]) {
				count += 1;
			}
		}
	}

	return count;
}

void DrawingPanel::SetNeighbors(std::vector<std::vector<int>>* neighbors)
{
	pNeighbors = neighbors;
}

void DrawingPanel::SetGeneration(int* generations)
{
	pGenerations = generations;
}

void DrawingPanel::SetLivingCells(int* livingCells)
{
	pLivingCells = livingCells;
}
