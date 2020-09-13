#include "utils.h"

bool compare(const string& x, const string& y) {
	return _stricmp(x.c_str(), y.c_str()) == 0;
}
