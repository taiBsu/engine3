#include "../lang/Character.h"

#include "PrintStream.h"

PrintStream::PrintStream() {
	streamFlags = SF_none;
}

void PrintStream::print(char ch) {
	printf("%c", ch);
}

void PrintStream::print(int val) {
	if (doHex())
		printf("%ih", val);
	else
		printf("%i", val);
}

void PrintStream::print(uint32 val) {
	if (doHex())
		printf("%uh", val);
	else
		printf("%u", val);
}

void PrintStream::print(long val) {
	if (doHex())
		printf("%ldh", val);
	else
		printf("%ld", val);
}

void PrintStream::print(int64 val) {
	if (doHex())
		printf("%ldh", (long) val);
	else
		printf("%ld", (long) val);
}

void PrintStream::print(uint64 val) {
	if (doHex())
		printf("%luh", (unsigned long) val);
	else
		printf("%lu", (unsigned long) val);
}

void PrintStream::print(float val) {
	printf("%f", val);
}

void PrintStream::print(const char* str) {
	printf("%s", str);
}

void PrintStream::print(const String& str) {
	printf("%s", str.toCharArray());
}

void PrintStream::println(char ch) {
	printf("%c\n", ch);
}

void PrintStream::println(int val) {
	if (doHex())
		printf("%ih", val);
	else
		printf("%i", val);
}

void PrintStream::println(uint32 val) {
	if (doHex())
		printf("%uh\n", val);
	else
		printf("%u\n", val);
}

void PrintStream::println(long val) {
	if (doHex())
		printf("%ldh\n", val);
	else
		printf("%ld\n", val);
}

void PrintStream::println(int64 val) {
	if (doHex())
		printf("%ldh", (long) val);
	else
		printf("%ld", (long) val);
}

void PrintStream::println(uint64 val) {
	if (doHex())
		printf("%luh\n", (unsigned long) val);
	else
		printf("%lu\n", (unsigned long) val);
}

void PrintStream::println(float val) {
	printf("%f\n", val);
}

void PrintStream::println(const char* str) {
	printf("%s\n", str);
}

void PrintStream::println(const String& str) {
	printf("%s\n", str.toCharArray());
}

PrintStream& PrintStream::operator<<(char ch) {
	print(ch);

	return *this;
}

PrintStream& PrintStream::operator<<(int val) {
	print(val);

	return *this;
}

PrintStream& PrintStream::operator<<(uint32 val) {
	print(val);

	return *this;
}

PrintStream& PrintStream::operator<<(long val) {
	print(val);

	return *this;
}

PrintStream& PrintStream::operator<<(int64 val) {
	print(val);

	return *this;
}

PrintStream& PrintStream::operator<<(uint64 val) {
	print(val);

	return *this;
}

PrintStream& PrintStream::operator<<(float val) {
	print(val);

	return *this;
}

PrintStream& PrintStream::operator<<(const char* str) {
	print(str);

	return *this;
}

PrintStream& PrintStream::operator<<(const String& str) {
	print(str);

	return *this;
}

PrintStream& PrintStream::operator<< (const StreamFlags flags) {
	streamFlags = (StreamFlags) ((uint32) streamFlags | (uint32) flags);

	return *this;
}