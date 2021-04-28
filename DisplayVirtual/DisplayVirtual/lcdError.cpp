#include "lcdError.h"

using namespace std;
string lcdError :: getErrorName() {
	return this->name;
}

string lcdError::getErrorDescription() {
	return this->description;
}

unsigned long lcdError::getErrorCode() {
	return this->errorCode;
}

bool lcdError::setError(const char* name_, const char* description_, unsigned long int code_) {
	int success = false;
	if (name_ != NULL){
		(this->name).clear();
		(this->name).append(name_);
		success = true;
	}
	
	if (description_ != NULL) {
		(this->description).clear();
		(this->description).append(description_);
		success = true;
	}

	if (code_ != 0) {
		this->errorCode = code_;
		success = true;
	}
	
	return success;
}