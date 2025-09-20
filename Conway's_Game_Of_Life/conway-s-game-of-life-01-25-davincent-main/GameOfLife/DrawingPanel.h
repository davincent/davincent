#pragma once
#include "wx/wx.h"
#include "Settings.h"
//#include "MainWindow.h"
#include "App.h"



class MainWindow;

class DrawingPanel :
    public wxPanel
{
private:
    //int mPanelGridSize = 15;
    std::vector<std::vector<bool>>& newBoard;
    std::vector<std::vector<int>>* pNeighbors;
    bool& _isNeighborCount;
    bool& _isShowGrid;
    bool& _is10x10;


    Settings* dpSettings = nullptr;

    int* pGenerations = nullptr;
    int* pLivingCells = nullptr;

    

public:
    
    

    DrawingPanel(wxFrame* parent, wxSize size, std::vector<std::vector<bool>>& gameBoard, std::vector<std::vector<int>>* neightbors, bool& isNeighborCount, bool& isShowGrid, bool& is10x10);
    ~DrawingPanel();

    void OnPaint(wxPaintEvent& paintEvent);
    void OnSize(wxSize& _size);
    void SetGridSize(int _gridsize);
    void OnMouseUp(wxMouseEvent& event);
    void SetSettings(Settings* settings);
    int NeighborCount(int x, int y);
    void SetNeighbors(std::vector<std::vector<int>>* neighbors);

    void GetCurrentNeighbors();

    void SetGeneration(int* generations);
    void SetLivingCells(int* livingCells);

    wxDECLARE_EVENT_TABLE();

};

