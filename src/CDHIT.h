#ifndef __CDHIT_H__
#define __CDHIT_H__

#include "Program.h"
#include <vector>

enum cdhitMode {cd_hit, cd_hit_est, cd_hit_454, none};

class CDHIT : public Program {
public :
	//constructors
	CDHIT();
	CDHIT(cdhitMode mode);

	//setters
	void setMode(cdhitMode mode);

	//actions
	std::pair<std::string, int> run();

private :
	void setRequired();
	bool checkValid() const;

	cdhitMode mode;
	std::vector<std::string> required;
};

#endif // !__CDHIT_H__
