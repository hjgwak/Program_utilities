#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <string>
#include <map>
#include <utility>
#include <vector>

class Program {
public :
	//constructors
	Program();
	Program(const std::string& name, const std::string& path);

	//setters
	void addOption(const std::string& key, const std::string& value);

	//getters
	std::string getPath() const;
	std::string getName() const;
	std::string getOption(const std::string& key) const;
	std::vector<std::string> getOptionKeys() const;

	//actions
	virtual std::pair<std::string, int> run() = 0;

protected :
	std::map<std::string, std::string> options;

private :
	std::string path;
	std::string name;
};

#endif // !__PROGRAM_H__
