#ifndef __PARSER_T_H__
#define __PARSER_T_H__

#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class Parser_t
{
	public:
		Parser_t(const string& _fileName);
		~Parser_t();
		string GetNextLine();
		inline int GetLineNum() const;
		inline bool HasLines() const;
	private:
		void operator=(const Parser_t& _pars);
		Parser_t(const Parser_t& _pars);

		FILE* m_fp;
		int m_currLineNum;
		ifstream* m_fs;
};

inline int Parser_t::GetLineNum() const
{
	return m_currLineNum;
}

inline bool Parser_t::HasLines() const
{
	return !m_fs->eof();
}

#endif


