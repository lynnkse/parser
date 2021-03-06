#include "Analyzer_t.h"
#include "Parser_t.h"
#include "Tokenizer_t.h"
#include "FileParser_t.h"
#include <cstring>
#include <vector>

FileParser_t::FileParser_t()
{
	m_analyzer = new Analyzer_t();
	m_parser = new Parser_t();
	m_tokenizer = new Tokenizer_t();
}

FileParser_t::~FileParser_t()
{
	delete m_analyzer;
	delete m_parser;
	delete m_tokenizer;
}

void FileParser_t::RunParser(const string& _file) const
{
		
	m_parser->ProcessFile(_file);
	string fileName;
	
	while(m_parser->HasLines())
	{
		string s = m_parser->GetNextLine();
		fileName = m_parser->GetFileName();
		vector<string> tokens = m_tokenizer->GetStringTokens(s);
		m_analyzer->Analyze(tokens, m_parser->GetLineNum(), fileName);
	}
	m_analyzer->AnalyzeFinal();
}
