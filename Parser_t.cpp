#include "Parser_t.h"
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

//Parser_t::Parser_t(const string& _fileName): m_currLineNum(0), m_fs(_fileName.c_str()){}

Parser_t::Parser_t():m_currLineNum(0), m_fs(0){}

Parser_t::~Parser_t()
{
	if(m_fs) delete m_fs; //because last m_fs is not deleted in ProcessFile()
}

string Parser_t::GetNextLine() 
{
	if(!m_fs->eof() && !m_fs->fail() && !m_fs->bad())
	{	
		string line;
		getline(*m_fs, line);
		++m_currLineNum;	
		return line;
	}
	throw("cannot read from file");
}

void Parser_t::ProcessFile(const string& _fileName)
{
	if(m_fs) delete m_fs;
	
	m_fs = new ifstream(_fileName.c_str());
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







































