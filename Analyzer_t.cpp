#include "Analyzer_t.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Analyzer_t::Analyzer_t(): m_prevToken(""), m_befLastToken(""), m_otherTokens(";<>&"), m_parenesisCount(0), m_bracketsCount(0), m_curlyBrace(0), m_errOpeningPar(0), m_errOpeningBrack(0), m_errOpeningCurl(0) 
{
	EnterPredefinedTypes();
	EnterOperators();
	EnterKeywords();
}

Analyzer_t::~Analyzer_t(){}

void Analyzer_t::EnterPredefinedTypes()
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

bool Analyzer_t::BracesCheck(vector<string>::const_iterator& it, int _lineNum)
{
	if((*it).compare("(") == 0) m_parenesisCount = (m_parenesisCount >= 0 ? ++m_parenesisCount : 1);
	else if((*it).compare(")") == 0) {--m_parenesisCount; if(m_parenesisCount < 0) m_errOpeningPar = 1;}
	else if((*it).compare("[") == 0) m_bracketsCount = (m_bracketsCount >= 0 ? ++m_bracketsCount : 1);
	else if((*it).compare("]") == 0) {--m_bracketsCount; if(m_bracketsCount < 0) m_errOpeningBrack = 1;}
	else if((*it).compare("{") == 0) m_curlyBrace = (m_curlyBrace >= 0 ? ++m_curlyBrace : 1);
	else if((*it).compare("}") == 0) {--m_curlyBrace; if(m_curlyBrace < 0) m_errOpeningCurl = 1;}
	else return false;

	return true;
}

bool Analyzer_t::IfElseCheck(vector<string>::const_iterator& it, int _lineNum)
{
	if((*it).compare("if") == 0) m_if = 1;
	else if((*it).compare("else") == 0 && !m_if) PrintError("else without prior if", _lineNum);
	else if((*it).compare("else") == 0) m_if = 0;
	else return false;
	
	return true;
}

bool Analyzer_t::IlligalOpCheck(vector<string>::const_iterator& it, int _lineNum) const
{
	if(!(*it).compare("+") && !(m_prevToken).compare("+") && !(m_befLastToken).compare("+")) PrintError("illigal operator +++", _lineNum);
	else if(!(*it).compare("-") && !(m_prevToken).compare("-") && !(m_befLastToken).compare("-")) PrintError("illigal operator ---", _lineNum);
	else return false;

	return true;
}

bool Analyzer_t::TypeCheck(vector<string>::const_iterator& it, int _lineNum) const
{
	if(m_types.find(*it) != m_types.end() && m_types.find(m_prevToken) != m_types.end()) PrintError("multiple predefined typed", _lineNum);
	else return false;

	return true;
}

bool Analyzer_t::UserDeclaredCheck(vector<string>::const_iterator& it, int _lineNum) const
{
	if(m_userDeclared.find(*it) != m_userDeclared.end()) cout << "Error on line " << _lineNum << ": " << *it << " is already declared" << endl;
	else return false;

	return true;
}

bool Analyzer_t::KeywordsCheck(vector<string>::const_iterator& it, int _lineNum)
{
	if(m_types.find(m_prevToken) != m_types.end() && m_keywords.find(*it) == m_keywords.end() && m_operators.find(*it) == m_operators.end() && m_otherTokens.find(*it) == string::npos) m_userDeclared.insert(*it);
	else if(m_keywords.find(*it) != m_keywords.end() && m_types.find(m_prevToken) != m_types.end()) PrintError("illigal declaration", _lineNum);
	else return false;
	
	return true;
}

bool Analyzer_t::UndeclaredCheck(vector<string>::const_iterator& it, int _lineNum) const
{
	if(m_keywords.find(*it)     == m_keywords.end()     && 
	   m_types.find(*it)        == m_types.end()        && 
       m_operators.find(*it)    == m_operators.end()    && 
	   m_userDeclared.find(*it) == m_userDeclared.end() && 
       !IsNumber(*it)                                   &&
	   m_otherTokens.find(*it)  == string::npos) 
	   cout << "Error on line "  << _lineNum << ": "<< *it << " not declared" << endl;
	else return false;
	
	return true;
}

void Analyzer_t::Analyze(const vector<string>& _words, int _lineNum)
{
	static int isFirst = 1;	

	if(_words.empty()) return;

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
		   if (BracesCheck(it, _lineNum));
		   else if(IfElseCheck(it, _lineNum));
		   else if(IlligalOpCheck(it, _lineNum));
		   else if(TypeCheck(it, _lineNum));
		   else if(UserDeclaredCheck(it, _lineNum));
		   else if(KeywordsCheck(it, _lineNum));
		   else if(UndeclaredCheck(it, _lineNum));

		m_befLastToken = m_prevToken;
		m_prevToken = *it;
	}
}

void Analyzer_t::PrintError(const string& _msg, int _lineNum) const
{
	cout << "Error on line " << _lineNum << ": " << _msg << endl;
}

bool Analyzer_t::IsNumber(const string& _s) const
{
    string::const_iterator it = _s.begin();
    while (it != _s.end() && std::isdigit(*it)) 
	{
		++it;
	}
    return !_s.empty() && it == _s.end();
}

void Analyzer_t::ZeroAll()
{
	m_parenesisCount = 0;
	m_bracketsCount = 0;
	m_curlyBrace = 0;	
	m_userDeclared.clear();	
}

void Analyzer_t::AnalyzeFinal()
{
	if(m_bracketsCount > 0) cout << "Error: "<< m_bracketsCount <<" unclosed brackets" << endl;
	if(m_errOpeningBrack) cout << "Error: closing brackets without openning one" << endl;
	if(m_curlyBrace > 0) cout << "Error: "<< m_curlyBrace <<" unclosed curlybrace" << endl;
	if(m_errOpeningCurl) cout << "Error: closing curlybrace without openning one" << endl;
	if(m_parenesisCount > 0) cout << "Error: " << m_parenesisCount <<" unclosed parentesis" << endl;
	if(m_errOpeningPar) cout << "Error: closing parentesis without openning one" << endl;
	
	ZeroAll();
}























