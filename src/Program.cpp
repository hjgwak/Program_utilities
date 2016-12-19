#include "Program.h"

using namespace std;

//constructors
Program::Program() {
	this->path = "";
	this->name = "";
	this->options.clear();
}

Program::Program(const string& name, const string& path) {
	this->name = name;
	this->path = path;
	this->options.clear();
}

//setters
Program& Program::addOption(const string& key, const string& value) {
	this->options[key] = value;

	return *this;
}

Program& Program::setName(const string name) {
	this->name = name;

	return *this;
}

Program& Program::setPath(const string path) {
	this->path = path;
	if (this->path[this->path.size() - 1] != '/') {
		this->path += "/";
	}

	return *this;
}

//getters
string Program::getPath() const {
	return this->path;
}

string Program::getName() const {
	return this->name;
}

string Program::getOption(const string& key) const {
	map<string, string>::const_iterator m_it = this->options.find(key);
	if (m_it != this->options.end()) {
		return m_it->second;
	}
	return "";
}

vector<string> Program::getOptionKeys() const {
	vector<string> keys;
	map<string, string>::const_iterator m_it = this->options.begin();

	for (; m_it != this->options.end(); ++m_it) {
		keys.push_back(m_it->first);
	}

	return keys;
}