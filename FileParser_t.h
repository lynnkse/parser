#ifndef __FILEPARSER_T_H__
#define __FILEPARSER_T_H__

#include <string>

using namespace std;

class Tokenizer_t;
class Analyzer_t;
class Parser_t;

class FileParser_t
{
	public:
		FileParser_t();
		~FileParser_t();
		void RunParser(const string& _file) const;
	private:
		void operator=(const FileParser_t& _par);
		FileParser_t(const FileParser_t& _par);
		Parser_t* m_parser;
		Tokenizer_t* m_tokenizer;
		Analyzer_t* m_analyzer;
};

#endif
