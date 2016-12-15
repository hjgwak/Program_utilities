#include "CDHIT.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	int ret = 0;
	CDHIT cdhit(cdhitMode::cd_hit);
	
	cdhit.setMode(cdhitMode::cd_hit_est);
	cdhit.setName("cd-hit-est");
	cdhit.setPath("/home/hjgwak/program/cdhit-master/");

	if (cdhit.getName() != "cd-hit-est") {
		cerr << "[ERROR] Program.getName()" << endl;
		ret -= 1;
	}

	if (cdhit.getPath() != "/home/hjgwak/program/cdhit-master/") {
		cerr << "[ERROR] Program.getPath()" << endl;
		ret -= 1;
	}

	map<string, string> options;
	options["-i"] = "../test_data/test.fasta";
	options["-o"] = "../test_output/test_CDHIT.cdhit";
	options["-c"] = "0.94";
	options["-M"] = "0";
	options["-n"] = "8";
	options["-d"] = "100";

	map<string, string>::iterator m_it = options.begin();
	for (; m_it != options.end(); ++m_it) {
		cdhit.addOption(m_it->first, m_it->second);
	}
	
	vector<string> keys = cdhit.getOptionKeys();
	vector<string> answer_keys = { "-i", "-o", "-c", "-M", "-n", "-d" };
	if (keys.size() != answer_keys.size()) {
		cerr << "[ERROR] Program.getOptionKeys()" << endl;
		ret -= 1;
	}
	else {
		vector<string>::iterator v_it = answer_keys.begin();
		for (; v_it != keys.end(); ++v_it) {
			vector<string>::iterator has = find(keys.begin(), keys.end(), *v_it);
			if (has == keys.end()) {
				cerr << "[ERROR] Program.getOptionKeys()" << endl;
				ret -= 1;
				break;
			}
		}
	}

	m_it = options.begin();
	for (; m_it != options.end(); ++m_it) {
		string val = cdhit.getOption(m_it->first);
		if (val != m_it->second) {
			cerr << "[ERROR] Program.getOption()" << endl;
			ret -= 1;
			break;
		}
	}

	pair<string, int> res = cdhit.run();

	ifstream result, answer;
	result.open("../test_output/test_CDHIT.cdhit.clstr");
	answer.open("../test_output/answer_CDHIT.cdhit.clstr");

	string result_line, answer_line;
	while (getline(result, result_line) && getline(answer, answer_line)) {
		if (result_line != answer_line) {
			cerr << "[ERROR] CDHIT.run()" << endl;
			ret -= 1;
			break;
		}
	}

	return ret;
}