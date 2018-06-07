#pragma once
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class TestCase {

	string checkname;
	ostream &os;
	int passed;
	int failed;
	void write2stream(string msg);

public:
	TestCase();
	TestCase(string name, ostream &ost) :
			checkname(name), os(ost), passed(0), failed(0) {
	}
	;
	template<typename T>
	TestCase& check_equal(T a, T b);
	template<typename T>
	TestCase& check_different(T a, T b);
	template<typename T>
	TestCase& check_output(T a, string b);
	template<typename T, typename Function, typename ArgType>
	TestCase& check_function(Function f, ArgType arg, T expected);
	void print();
};

template<typename T>
TestCase& TestCase::check_equal(T a, T b) {
	if (a == b) {
		passed++;
	} else {
		failed++;
		ostringstream save1, save2;
		save1 << a;
		save2 << b;
		string msg = save1.str() + " should equal " + save2.str() + "!";
		write2stream(msg);
		//cout <<checkname<< " : Failure in test #"<<failed+passed<< ":"<<" numbers are not equal"<< endl;
	}
	return *this;
}

template<typename T>
TestCase& TestCase::check_different(T a, T b) {
	if (a != b) {
		passed++;
	} else {
		failed++;
		ostringstream save1, save2;
		save1 << a;
		save2 << b;
		string msg = save1.str() + " shouldn't equal " + save2.str() + "!";
		write2stream(msg);
	}
	return *this;
}

template<typename T, typename Function, typename ArgType>
TestCase& TestCase::check_function(Function f, ArgType arg, T expected) {
	passed++;
	T result = f(arg);
	if (result != expected) {
		ostringstream out1, out2;
		out1 << expected;
		out2 << result;
		string msg = "Function should return " + out1.str() + " but returned "
				+ out2.str() + "!";
		write2stream(msg);
		failed++;
		passed--;
	}
	return *this;
}

/*template<typename T, typename R>
 TestCase& TestCase::check_function(R (*fun)(T), T b, R c) {
 if ((*fun)(b) == c)
 passed++;
 else {
 failed++;

 ostringstream save1, save2;
 save1 << b;
 save2 << c;
 string msg = "Function should return " + save1.str() + " but returned "
 + save2.str() + "!";
 write2stream(msg);
 }
 return *this;
 }*/

/*cout << checkname << " : Failure in test #" << failed + passed << ":"
 << " Function should return " << c << " but returned "
 << (*fun)(b) << "!" << endl;*/

template<typename T>
TestCase& TestCase::check_output(T a, string b) {
	passed++;
	ostringstream save;
	save << a;
	if (save.str() != b) {
		string msg = "string value should be " + b + " but is " + save.str();
		write2stream(msg);
		failed++;
		passed--;
	}
	return (*this);
}
