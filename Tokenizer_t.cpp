#include "Tokenizer_t.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

void Tokenizer_t::SkipLeading()
{
    while(m_currPos != m_buffer.end() && IsDelimiter(*m_currPos))
	{
        ++m_currPos;
	}
}

bool Tokenizer_t::IsDelimiter(char _c)
{
	return (m_delimiters.find(_c) != string::npos);
}

bool Tokenizer_t::IsToken(char _c)
{
	return (m_tokensDel.find(_c) != string::npos);
}

string Tokenizer_t::NextToken()
{
	if(!m_buffer.size())
	{
		return "";
	}	

	string token;
	SkipLeading();
	
	if(IsToken(*m_currPos))
	{
		token += *m_currPos;
		++m_currPos;
		return token;		
	}

	while(m_currPos!=m_buffer.end() && !IsDelimiter(*m_currPos) && !IsToken(*m_currPos))
	{
		token += *m_currPos;
		++m_currPos;
	}

	return token;
}

vector<string> Tokenizer_t::GetStringTokens(const string& _str)
{
	string token;
	m_buffer = _str;
	m_currPos = m_buffer.begin();	
	while((token = NextToken()) != "")
	{
		m_tokens.push_back(token);
	}
	
	return m_tokens;
}

struct Printv
{
	void operator()(const string& s)
	{
		cout << s << endl;
	};
};

int main()
{
	string s("int a = ()a+b)");
	Tokenizer_t t;
	
	vector<string> v = t.GetStringTokens(s);

	for_each(v.begin(), v.end(), Printv());
	
	return 0;
}


























































