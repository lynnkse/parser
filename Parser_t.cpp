#include "Parser_t.h"
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

Parser_t::Parser_t(const string& _fileName): m_currLineNum(0)
{
	m_fp = fopen(_fileName.c_str(), "r");
	if(!m_fp)
	{
		throw("couldn't open file");
	}
	m_fs = new ifstream(_fileName.c_str());
}

Parser_t::~Parser_t()
{
	if(m_fp) 
	{
		fclose(m_fp);
		delete m_fs;
	}	
}

string Parser_t::GetNextLine() 
{
	if(!m_fs->eof() && !m_fs->fail() && !m_fs->bad())
	{	
		string line;
		getline(*m_fs, line);	
		return line;
	}
	throw("cannot read from file");
}

/*int main()
{
	Parser_t p("file.txt");
	
	while(p.HasLines())
	{
		cout << p.GetNextLine() << endl;
	}

	return 0;
}*/







































