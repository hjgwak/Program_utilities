#ifndef __PARSER_H__
#define __PARSER_H__

#include <fstream>
#include <string>

class Parser {
public :
	//constructors && distructors
	Parser();
	Parser(const char* file_name);
	Parser(const std::string& file_name);
	~Parser();

	//setters
	void open(const char* file_name);
	void open(const std::string& file_name);
	void close();

	//getters
	bool is_open() const;

	//actions
	virtual bool parse() = 0;

protected :
	std::ifstream file;
};

#endif // !__PARSER_H__
