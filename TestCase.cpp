#include "TestCase.hpp"

void TestCase::write2stream(string msg){
	string result= checkname+": Failure in test #" +std::to_string(passed+failed)+": "+msg;
	os<<result<<endl;
}

void TestCase::print(){

	os << checkname << ": "<< std::to_string(failed) << " failed, ";
	os << to_string(passed) << " passed, ";
	os << to_string(passed+failed) << " total."<<endl;
}
