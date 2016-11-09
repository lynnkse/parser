#ifndef __PARSER_T_H__
#define __PARSER_T_H__

#include <cstring>
#include <fstream>

using namespace std;

class Parser_t
{
	public:
		Parser_t();
		~Parser_t();
		void ProcessFile(const string& _fileName);
		string GetNextLine();
		inline int GetLineNum() const;
		inline bool HasLines() const;
	private:
		void operator=(const Parser_t& _pars);
		Parser_t(const Parser_t& _pars);
		int m_currLineNum;
		ifstream* m_fs;
};

inline int Parser_t::GetLineNum() const
{
	return m_currLineNum;
}

inline bool Parser_t::HasLines() const
{
	return m_fs ? !m_fs->eof() : false;
}

#endif


