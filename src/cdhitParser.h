#ifndef __CDHITPARSER_H__
#define __CDHITPARSER_H__

#include "Parser.h"
#include <map>
#include <vector>

class cdhitParser : public Parser {
public :
	//constructors && distructors
	cdhitParser();
	cdhitParser(const char* file_name);
	cdhitParser(const std::string& file_name);
	~cdhitParser();

	//getters
	std::map<unsigned int, std::vector<std::string> > getWholeClusters() const;
	std::map<unsigned int, std::string> getWholeReps() const;
	std::vector<std::string> getCluster(const unsigned int num) const;
	std::string getRep(const unsigned int num) const;

	//actions
	bool parse();
private :
	std::map<unsigned int, std::vector<std::string> > clusters;
	std::map<unsigned, std::string> representatives;
};

#endif // ! __CDHITPARSER_H__