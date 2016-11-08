#include "Analyzer_t.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Analyzer_t::Analyzer_t(): m_prevToken("")
{
	EnterPredefinedTyped();
	EnterOperators();
	EnterKeywords();
}

void Analyzer_t::EnterPredefinedTyped()
{
	string ch("char");	
	string sh("short");
	string in("int");
	string lg("long");	
	string fl("float");
	string db("double");
	string vd("void");
	m_types.insert(ch);
	m_types.insert(sh);
	m_types.insert(in);
	m_types.insert(lg);
	m_types.insert(fl);
	m_types.insert(db);
	m_types.insert(vd);
}

void Analyzer_t::EnterOperators()
{
	string op1("++");
	string op2("--");
	string op3("==");
	string op4("->");
	string op5("=");
	string op6("+");
	string op7("-");
	string op8("*");
	string op9("&");
	string op10("<<");
	string op11(">>");
	m_operators.insert(op1);
	m_operators.insert(op2);
	m_operators.insert(op3);
	m_operators.insert(op4);
	m_operators.insert(op5);
	m_operators.insert(op6);
	m_operators.insert(op7);
	m_operators.insert(op8);
	m_operators.insert(op9);
	m_operators.insert(op10);
	m_operators.insert(op11);	
}

void Analyzer_t::EnterKeywords()
{
	string op1("class");
	string op2("private");
	string op3("public");
	string op4("protected");
	string op5("main");
	string op6("const");
	string op7("virtual");
	string op8("if");
	string op9("else");
	string op10("for");
	string op11("while");
	m_keywords.insert(op1);
	m_keywords.insert(op2);
	m_keywords.insert(op3);
	m_keywords.insert(op4);
	m_keywords.insert(op5);
	m_keywords.insert(op6);
	m_keywords.insert(op7);
	m_keywords.insert(op8);
	m_keywords.insert(op9);
	m_keywords.insert(op10);
	m_keywords.insert(op11);
}

int Analyzer_t::Analyze(vector<string> _words, int _lineNum)
{
	static int isFirst = 1;	
	int m_parenesisCount;
	int m_bracketsCount;
	int m_curlyBrace;	
	int errCount = 0;
	vector<string>::const_iterator it = _words.begin();

	if(isFirst)
	{
		isFirst = 0;
		if((*it).compare("main") != 0)	
		{	
			PrintError("Program should start with main()", _lineNum);
		}
	}

	for(; it != _words.end(); ++it)
	{
				if((*it).compare("(") == 0) ++m_parenesisCount;
				else if((*it).compare(")") == 0) m_parenesisCount = (m_parenesisCount >= 0 ? ++m_parenesisCount : 1);
				else if((*it).compare("[") == 0) ++m_bracketsCount;
				else if((*it).compare("]") == 0) m_bracketsCount = (m_bracketsCount >= 0 ? ++m_bracketsCount : 1);
				else if((*it).compare("{") == 0) ++m_curlyBrace;
				else if((*it).compare("}") == 0) m_curlyBrace = (m_curlyBrace >= 0 ? ++m_curlyBrace : 1);
				else if((*it).compare("if") == 0) m_if = 1;
				else if((*it).compare("else") == 0 && !m_if) PrintError("else without prior if", _lineNum);
				// TODO else if   ILLIGAL OPERATORS
				
				if(m_types.find(m_prevToken) != set::end && m_types.find(*it) != set::end) PrintError("multiple predefined typed", _lineNum);
				else if(m_userDeclared.find(*it) != set::end) cout << "Error on line " << _lineNum << ": " << *it << " is already declared" << endl;
				else if(m_types.find(m_prevToken) != set::end && m_keywords.find(*it) == set::end) m_userDeclared.insert(*it);
			
				m_prevToken = *it;
				
	}
}

void Analyzer_t::PrintError(const string& _msg, int _lineNum) const
{
	cout << "Error on line " << _lineNum << ": " << _msg << endl;
}


//----------------------------------------//
int main() { return 0; }
























