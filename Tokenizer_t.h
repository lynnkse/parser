#ifndef __TOKENIZER_T_H__
#define __TOKENIZER_T_H__

#include <vector>
#include <iterator>

using namespace std;

class Tokenizer_t
{
	public:
		Tokenizer_t(): m_delimiters(" 	"), m_tokensDel("()[]{};<>=+-*&"){};
		~Tokenizer_t(){};
		vector<string> GetStringTokens(const string& _str);	//should I return ref to local variable here??

	private:
		void operator=(const Tokenizer_t& _tok);
		Tokenizer_t(const Tokenizer_t& _toks);	
		void SkipLeading();
		bool IsDelimiter(char c) const;
		bool IsToken(char c) const;   
		string NextToken();                        
    	string m_buffer; 
		vector<string> m_tokens;                                                                 
		string m_delimiters;    
		string m_tokensDel;                          
		string::const_iterator m_currPos; 
};

#endif


