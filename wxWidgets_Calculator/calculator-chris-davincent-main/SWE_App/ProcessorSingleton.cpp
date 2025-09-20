#include "ProcessorSingleton.h"


ProcessorSingleton* ProcessorSingleton::instance = nullptr;

ProcessorSingleton* ProcessorSingleton::GetInstance() {
    if (!instance) {
        instance = new ProcessorSingleton();
    }
    return instance;
}


int ProcessorSingleton::GetPrecedence(const wxString& token) const
{
    if (token == '+' || token == '-') {
        return 1;
    }
    else if (token == '*' || token == '/' || token == '%') {
        return 2;
    }
    return 0;
}

bool ProcessorSingleton::IsOperator(const wxString& token) const
{
    return (token == wxT("+") || token == wxT("-") || token == wxT("*") || token == wxT("/") || token == wxT("%"));
}

bool ProcessorSingleton::IsFunction(const wxString& token) const
{
    return (token == wxT("sin") || token == wxT("cos") || token == wxT("tan"));
}

bool ProcessorSingleton::IsNumber(const wxString& token) const
{
    double num;
    return token.ToDouble(&num);
}

double ProcessorSingleton::ApplyOperator(double operand2, double operand1, const wxString& op) const
{
    if (op == wxT("+"))
        return operand1 + operand2;
    if (op == wxT("-"))
        return operand1 - operand2;
    if (op == wxT("*"))
        return operand1 * operand2;
    if (op == wxT("/"))
    {
        if (operand2 == 0)
            throw std::runtime_error("Division by zero!");
        return operand1 / operand2;
    }
    if (op == wxT("%"))
    {
        if (static_cast<int>(operand2) == 0)
            throw std::runtime_error("Modulo by zero!");
        return std::fmod(operand1, operand2);
    }
    return 0.0;
}

double ProcessorSingleton::ApplyFunction(double operand, const wxString& func) const
{
    if (func == wxT("sin"))
        return std::sin(operand);
    if (func == wxT("cos"))
        return std::cos(operand);
    if (func == wxT("tan"))
        return std::tan(operand);
    return 0.0;
}

wxString ProcessorSingleton::ProcessExpression(const wxString expression)
{
    wxStringTokenizer tokenizer(expression, "+-*/% ");
    std::queue<wxString> outputQueue;
    std::stack<wxString> operatorStack;
    wxString token;
    wxString op;

    while (tokenizer.HasMoreTokens()) {
        token = tokenizer.GetNextToken();
        if (IsNumber(token)) {
            outputQueue.push(token);
            op = tokenizer.GetLastDelimiter();
        }
        else if (IsFunction(token)) {
            operatorStack.push(token);
        }
        else {
            return "ERROR";
        }
        
        
        while (!operatorStack.empty() && (IsOperator(operatorStack.top()) || IsFunction(operatorStack.top())) && GetPrecedence(operatorStack.top()) >= GetPrecedence(op)) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        }

        if (op != "") {
            operatorStack.push(op); // ++ I have no idea why iut keeps adding "" to the stack even though I am explicitly talling it not to.
        }
        

    }

    std::stack<double> evaluationStack;
    while (!outputQueue.empty()) {
        token = outputQueue.front();
        outputQueue.pop();

        if (IsNumber(token)) {
                double num;
            if (!token.ToDouble(&num)) {
                return "ERROR";
            }
            evaluationStack.push(num);
        }
        else if (IsOperator(token)) {
            if (evaluationStack.size() < 2) {
                return "ERROR";
            }
            double operand2 = evaluationStack.top();
            evaluationStack.pop();
            double operand1 = evaluationStack.top();
            evaluationStack.pop();
            try {
                evaluationStack.push(ApplyOperator(operand2, operand1, token));
            }
            catch (const std::exception& exception) {
                return "ERROR";
            }
            
        }
        else if (IsFunction(token)) {
            if (evaluationStack.empty()) {
                return "ERROR";
            }
            double operand = evaluationStack.top();
            evaluationStack.pop();
            evaluationStack.push(ApplyFunction(operand, token));
        }
    }

        if (evaluationStack.size() != 1) {
            return "ERROR";
        }

        return std::to_string(evaluationStack.top());
        
    }
