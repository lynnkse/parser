#ifndef __FILEPARSER_T_H__
#define __FILEPARSER_T_H__

class FileParser_t
{
	public:
		FileParser_t(const string& _file);
		~FileParser_t();
		void RunParser();
	private:
		void operator=(const FileParser_t& _par);
		FileParser_t(const FileParser_t& _par);
		Parser_t m_parser;
		Tokenizer_t m_tokenizer;
		Analyzer_t_m analyzer;
};

#endif
