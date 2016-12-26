#include "CDHIT.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

string makeDirForm(string path) {
	return (path[path.length() - 1] != '/') ? path + "/" : path;
}

int main(int argc, char* argv[]) {
	int ret = 0;

	if (argc != 3) {
		return -1;
	}
	string path = makeDirForm(argv[1]);
	string cdhit_path = makeDirForm(argv[2]);

	CDHIT cdhit(cdhitMode::cd_hit);
	
	cdhit.setMode(cdhitMode::cd_hit_est);
	cdhit.setName("cd-hit-est");
	cdhit.setPath(cdhit_path);

	if (cdhit.getName() != "cd-hit-est") {
		cerr << "[ERROR] Program.getName()" << endl;
		ret -= 1;
	}

	if (cdhit.getPath() != cdhit_path) {
		cerr << "[ERROR] Program.getPath()" << endl;
		ret -= 1;
	}

	map<string, string> options;
	options["-i"] = path + "test_data/test.fasta";
	options["-o"] = path + "test_output/test_CDHIT.cdhit";
	options["-c"] = "0.94";
	options["-M"] = "0";

	map<string, string>::iterator m_it = options.begin();
	for (; m_it != options.end(); ++m_it) {
		cdhit.addOption(m_it->first, m_it->second);
	}

	options["-n"] = "8";
	options["-d"] = "100";

	cdhit.addOption("-n", "8").addOption("-d", "100");
	
	vector<string> keys = cdhit.getOptionKeys();
	vector<string> answer_keys = { "-i", "-o", "-c", "-M", "-n", "-d" };
	if (keys.size() != answer_keys.size()) {
		cerr << "[ERROR] Program.getOptionKeys()" << endl;
		ret -= 1;
	}
	else {
		vector<string>::iterator v_it = answer_keys.begin();
		for (; v_it != answer_keys.end(); ++v_it) {
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
	if (res.second != 0) {
		cerr << "[ERROR] cd-hit did not execute collectly" << endl;
		ret -= 1;
	}

	ifstream result, answer;
	result.open(path + "test_output/test_CDHIT.cdhit.clstr");
	answer.open(path + "test_answer/answer_CDHIT.cdhit.clstr");

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