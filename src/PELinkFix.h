// PELinkFix.h
// Copyright (c) 2015-2018 Arkadiusz Bokowy
//
// This file is a part of WinPEFix.
//
// This project is licensed under the terms of the MIT license.

#ifndef WINPEFIX_PELINKFIX_H_
#define WINPEFIX_PELINKFIX_H_

#include <fstream>
#include <string>

class PELinkFix {
public:

	enum class ErrorCode {
		NoErrorCode = 0,
		FileOpenError,
		CreateBackupError,
		InvalidPEFormat,
	};

	PELinkFix(std::string filename);
	~PELinkFix();

	bool process();

	ErrorCode getErrorCode() const { return m_error; };
	std::string getErrorString();

	const std::string &getFileName() const { return m_filename; }
	std::string getBackupFileName() const;

protected:
	bool checkFileFormat();
	bool updateSystemVersion();
	bool createBackupFile();

private:
	std::string m_filename;
	std::fstream m_file;
	ErrorCode m_error;

};

#endif
