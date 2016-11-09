#ifndef __ANALYZER_T_H__
#define __ANALYZER_T_H__

#include <cstring>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Analyzer_t
{
	public:		
		Analyzer_t();
		virtual ~Analyzer_t();
		void Analyze(const vector<string>& _words, int _lineNum);
		void AnalyzeFinal();	

	private:
		void operator=(const Analyzer_t& _anz);
		Analyzer_t(const Analyzer_t& _anz);
		void EnterPredefinedTyped();
		void EnterOperators();
		void EnterKeywords();
		void PrintError(const string& _msg, int _lineNum) const;
		bool IsNumber(const string& _s);
		void ZeroAll();

		set<string> m_types;
		set<string> m_operators;
		set<string> m_userDeclared;
		set<string> m_keywords;
		const string m_otherTokens; 
		int m_if;
		string m_prevToken;
		string m_lastToken;
		string m_befLastToken;
		int m_parenesisCount;
		int m_bracketsCount;
		int m_curlyBrace;
		int m_errOpeningPar;
		int m_errOpeningBrack;
		int m_errOpeningCurl;
};

#endif
