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
		//enum TokenType {TYPE, KEYWORD, OPERATOR, USER_DECLARED};
		
		Analyzer_t();
		~Analyzer_t();
		int Analyze(vector<string> _words, int _lineNum);	

	private:
		void operator=(const Analyzer_t& _anz);
		Analyzer_t(const Analyzer_t& _anz);
		void EnterPredefinedTyped();
		void EnterOperators();
		void EnterKeywords();
		void PrintError(const string& _msg, int _lineNum) const;
		void ParenesisCountUp();
		void ParenesisCountDown();
		void BracketsCountUp();
		void BracketsCountDown();
		void CurlybraceCountUp();
		void CurlybraceCountDown();

		set<string> m_types;
		set<string> m_operators;
		set<string> m_tokens;
		set<string> m_userDeclared;
		set<string> m_keywords;
		int m_if;
		string m_prevToken;
		TokenType m_lastToken;
};

#endif
