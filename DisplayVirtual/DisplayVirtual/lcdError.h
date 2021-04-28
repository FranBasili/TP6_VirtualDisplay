#ifndef lcderror
#define lcderror
#include <string>

enum ERRORS { 
	ALINIT = 1,
	STRING_INIT, 
	DISPLAY,
	BACKGROUND,
	FONT,
	LEFT_BOUNDARY,
	RIGHT_BOUNDARY,
	UP_BOUNDARY,
	DOWN_BOUNDARY,
	WRITING_EXCEEDED, 
	OUT_OF_BOUNDS,
	FAIL_CLEAR
};

class lcdError
{
public:

	lcdError() {
		errorCode = 0;
		name.clear();
		description.clear();
	}

	std::string getErrorName();
	std::string getErrorDescription();
	unsigned long getErrorCode();

	bool setError(const char* name, const char* description, unsigned long int code);

private:
	std::string name;
	std::string description;
	unsigned long errorCode;
};
#endif