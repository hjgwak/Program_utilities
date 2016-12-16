#include "CDHIT.h"
#include <cstdlib>

using namespace std;

//constructors
CDHIT::CDHIT() {
	this->mode = cdhitMode::none;
	this->required.clear();
}

CDHIT::CDHIT(const string name, const string path, const cdhitMode mode) 
: Program(name, path){
	this->mode = mode;
	this->setRequired();
}

CDHIT::CDHIT(const cdhitMode mode) {
	this->mode = mode;
	this->setRequired();
}

//setters
void CDHIT::setMode(const cdhitMode mode) {
	this->mode = mode;
	this->setRequired();
}

//actions
pair<string, int> CDHIT::run() {
	if (!this->checkValid()) {
		return make_pair("error", -1);
	}

	string cmd = this->getPath() + 
				((this->mode == cdhitMode::cd_hit)     ? "cd-hit" :
				 (this->mode == cdhitMode::cd_hit_454) ? "cd-hit-454" :
				 (this->mode == cdhitMode::cd_hit_est) ? "cd-hit-est" : "error");

	map<string, string>::iterator m_it = this->options.begin();
	for (; m_it != this->options.end(); ++m_it) {
		cmd += " " + m_it->first + " " + m_it->second;
	}

	int ret = system(cmd.c_str());

	return make_pair(cmd, ret);
}

//privates
void CDHIT::setRequired() {
	this->required.clear();
	if (mode == cdhitMode::cd_hit) {

	}
	else if (mode == cdhitMode::cd_hit_454) {

	}
	else if (mode == cdhitMode::cd_hit_est) {
		this->required.push_back("-i");
		this->required.push_back("-o");
	}
}

bool CDHIT::checkValid() const {
	if (this->mode == cdhitMode::none) {
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