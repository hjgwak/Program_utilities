#include "Muscle.h"

using namespace std;

// constructors
Muscle::Muscle() : Program("Muscle", "") {
	this->required.clear();
	this->setRequired();
}

Muscle::Muscle(const string name, const string path)
: Program(name, path) {
	this->required.clear();
	this->setRequired();
}

// actions
pair<string, int> Muscle::run() {
	if (!this->checkValid()) {
		return make_pair("error", -1);
	}

	string cmd = this->getPath() + "muscle";

	map<string, string>::iterator m_it = this->options.begin();
	for (; m_it != this->options.end(); ++m_it) {
		cmd += " " + m_it->first + " " + m_it->second;
	}

	int ret = system(cmd.c_str());

	return make_pair(cmd, ret);
}

// privates
void Muscle::setRequired() {
	this->required.push_back("-in");
	this->required.push_back("-out");
}

bool Muscle::checkValid() const {
	if (this->getPath() == "") {
		return false;
	}

	vector<string>::const_iterator v_it = this->required.begin();

	for (; v_it != this->required.end(); ++v_it) {
		if (this->getOption(*v_it) == "") {
			return false;
		}
	}

	return true;
}