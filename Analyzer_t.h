#ifndef __ANALYZER_T_H__
#define __ANALYZER_T_H__

#include <cstring>

class Analyzer_t
{
	public:
		enum TokenType {TYPE, KEYWORD, OPERATOR, USER_DECLARED};
		
		Analyzer_t();
		~Analyzer_t();
		int Analyze(vector<string> _words);	

	private:
		void operator=(const Analyzer_t& _anz);
		Analyzer_t(const Analyzer_t& _anz);
		set<string> m_types;
		set<string> m_operators;
		set<string> m_tokens;
		set<string> m_userDeclared;
		set<string> m_keywords;
		int m_parenesisCount;
		int m_bracketsCount;
		int m_curlyBrace;
		int m_if;
		TokenType m_lastToken;
};

#endif
