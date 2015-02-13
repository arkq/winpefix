// PELinkFix.h
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#ifndef PELINKFIX_H
#define PELINKFIX_H

#include <fstream>
#include <string>

using std::fstream;
using std::string;


class PELinkFix {
public:

	enum ErrorCode {
		NoErrorCode = 0,
		FileOpenError,
		CreateBackupError,
		InvalidPEFormat,
	};

	PELinkFix(string filename);
	~PELinkFix();

	bool process();

	ErrorCode getErrorCode() const { return m_error; };
	string getErrorString();

	const string &getFileName() const { return m_filename; }
	string getBackupFileName() const;

protected:
	bool checkFileFormat();
	bool updateSystemVersion();
	bool createBackupFile();

private:
	string m_filename;
	fstream m_file;
	ErrorCode m_error;

};

#endif  // PELINKFIX_H
