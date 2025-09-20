#pragma once
#include "wx/wx.h"
#include <fstream>

struct Settings {
	
	
	int gridSize = 15;

	// Interval
	int interval = 50;

	// Living cell color
	unsigned int livingCell_r = 128;
	unsigned int livingCell_g = 128;
	unsigned int livingCell_b = 128;
	unsigned int livingCell_a = 255;

	// Dead cell color
	unsigned int deadCell_r = 255;
	unsigned int deadCell_g = 255;
	unsigned int deadCell_b = 255;
	unsigned int deadCell_a = 255;

	void SetLivingColor(const wxColor& color) {
		livingCell_r = color.GetRed();
		livingCell_g = color.GetGreen();
		livingCell_b = color.GetBlue();
		livingCell_a = color.GetAlpha();
	}

	wxColor GetLivingColor() {
		wxColor color(livingCell_r, livingCell_g, livingCell_b, livingCell_a);
		return color;
	}

	void SetDeadColor(const wxColor& color) {
		deadCell_r = color.GetRed();
		deadCell_g = color.GetGreen();
		deadCell_b = color.GetBlue();
		deadCell_a = color.GetAlpha();
	}

	wxColor GetDeadColor() {
		wxColor color(deadCell_r, deadCell_g, deadCell_b, deadCell_a);
		return color;
	}

	int GetGridSize() {
		return gridSize;
	}

	void SetGridSize(int size) {
		gridSize = size;
	}

	int GetTime() {
		return interval;
	}

	void SetTime(int ms) {
		interval = ms;
	}



	//Load Data
	void LoadSettings() {
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read((char*)this, sizeof(Settings));
		file.close();
	}


	//Save Data

	void SaveSettings() {
		std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
		file.write((char*)this, sizeof(Settings));
		file.close();
	}

	bool isNeighborCount = true;
	bool isFinite = true;

	void ResetSettings() {
		gridSize = 15;

		// Interval
		interval = 50;

		// Living cell color
		livingCell_r = 128;
		livingCell_g = 128;
		livingCell_b = 128;
		livingCell_a = 255;

		// Dead cell color
		deadCell_r = 255;
		deadCell_g = 255;
		deadCell_b = 255;
		deadCell_a = 255;

		SaveSettings();
	}

	bool isShowGrid = true;
	bool is10x10 = true;
	bool isHUD = true;

	

};