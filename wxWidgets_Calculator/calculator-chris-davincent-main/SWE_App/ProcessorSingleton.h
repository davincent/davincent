#pragma once
#include "MainWindow.h"
#include <string>
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <sstream>
#include <iomanip>


class ProcessorSingleton
{
private:
	static ProcessorSingleton* instance;

	ProcessorSingleton() {}

	int GetPrecedence(const wxString& token) const;
	bool IsOperator(const wxString& token) const;
	bool IsFunction(const wxString& token) const;
	bool IsNumber(const wxString& token) const;
	
	double ApplyOperator(double operand2, double operand1, const wxString& op) const;

	double ApplyFunction(double operand, const wxString& func) const;

public:
	static ProcessorSingleton* GetInstance();

	wxString ProcessExpression(const wxString expression);



};

