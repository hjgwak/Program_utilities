#ifndef __CDHIT_H__
#define __CDHIT_H__

#include "Program.h"
#include <vector>

enum class cdhitMode {cd_hit, cd_hit_est, cd_hit_454, none};

class CDHIT : public Program {
public :
	//constructors
	CDHIT();
	CDHIT(const std::string name, const std::string path, const cdhitMode mode);
	CDHIT(const cdhitMode mode);

	//setters
	void setMode(const cdhitMode mode);

	//actions
	std::pair<std::string, int> run();

private :
	void setRequired();
	bool checkValid() const;

	cdhitMode mode;
	std::vector<std::string> required;
};

#endif // !__CDHIT_H__
