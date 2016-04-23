// mswinpe.cpp
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This project is licensed under the terms of the MIT license.
//
// This file contains structures used in the Windows Portable Executable (PE)
// file format. Those structures are defined in the header files available on
// Windows platform, however due to portability reasons we are forced to keep
// a copy of them here.

#ifndef WINPEH_H
#define WINPEH_H

#ifdef WIN32

#include <windows.h>

#else  // !WIN32

#include <stdint.h>

// definitions of data types supported by Windows
typedef uint8_t UCHAR;
typedef uint16_t WORD;
typedef int32_t LONG;
typedef uint32_t ULONG;

#define IMAGE_DOS_SIGNATURE    0x5A4D      // MZ
#define IMAGE_NT_SIGNATURE     0x00004550  // PE00

typedef struct _IMAGE_DOS_HEADER {
	WORD e_magic;     // Magic number
	WORD e_cblp;      // Bytes on last page of file
	WORD e_cp;        // Pages in file
	WORD e_crlc;      // Relocations
	WORD e_cparhdr;   // Size of header in paragraphs
	WORD e_minalloc;  // Minimum extra paragraphs needed
	WORD e_maxalloc;  // Maximum extra paragraphs needed
	WORD e_ss;        // Initial (relative) SS value
	WORD e_sp;        // Initial SP value
	WORD e_csum;      // Checksum
	WORD e_ip;        // Initial IP value
	WORD e_cs;        // Initial (relative) CS value
	WORD e_lfarlc;    // File address of relocation table
	WORD e_ovno;      // Overlay number
	WORD e_res[4];    // Reserved words
	WORD e_oemid;     // OEM identifier (for e_oeminfo)
	WORD e_oeminfo;   // OEM information; e_oemid specific
	WORD e_res2[10];  // Reserved words
	LONG e_lfanew;    // File address of new exe header
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
	ULONG VirtualAddress;
	ULONG Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_FILE_HEADER {
	WORD Machine;
	WORD NumberOfSections;
	ULONG TimeDateStamp;
	ULONG PointerToSymbolTable;
	ULONG NumberOfSymbols;
	WORD SizeOfOptionalHeader;
	WORD Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

typedef struct _IMAGE_OPTIONAL_HEADER {
	WORD Magic;
	UCHAR MajorLinkerVersion;
	UCHAR MinorLinkerVersion;
	ULONG SizeOfCode;
	ULONG SizeOfInitializedData;
	ULONG SizeOfUninitializedData;
	ULONG AddressOfEntryPoint;
	ULONG BaseOfCode;
	ULONG BaseOfData;
	ULONG ImageBase;
	ULONG SectionAlignment;
	ULONG FileAlignment;
	WORD MajorOperatingSystemVersion;
	WORD MinorOperatingSystemVersion;
	WORD MajorImageVersion;
	WORD MinorImageVersion;
	WORD MajorSubsystemVersion;
	WORD MinorSubsystemVersion;
	ULONG Win32VersionValue;
	ULONG SizeOfImage;
	ULONG SizeOfHeaders;
	ULONG CheckSum;
	WORD Subsystem;
	WORD DllCharacteristics;
	ULONG SizeOfStackReserve;
	ULONG SizeOfStackCommit;
	ULONG SizeOfHeapReserve;
	ULONG SizeOfHeapCommit;
	ULONG LoaderFlags;
	ULONG NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[16];
} IMAGE_OPTIONAL_HEADER, *PIMAGE_OPTIONAL_HEADER;

typedef struct _IMAGE_NT_HEADERS {
	ULONG Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER OptionalHeader;
} IMAGE_NT_HEADERS, *PIMAGE_NT_HEADERS;

#endif  // !WIN32

#endif  // WINPEH_H
