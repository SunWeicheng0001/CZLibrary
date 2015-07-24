#ifndef CZ_STRING
#define CZ_STRING
#include "Basics.h"
#include <string>
#include <vector>
namespace cz{
	class CZString : public Object{
	private:
		std::string *data;
		int length;
	public:
		CZString(){
			data = new std::string();
			length = 0;
		}
		CZString(char x){
			data = new std::string();
			data->push_back(x);
			length = 1;
		}

		CZString(const char* src){
			data = new std::string(src);
			length = data->length();
		}

		CZString(char x, int count){
			data = new std::string(count, x);
			length = count;
		}
		CZString(std::string& str){
			data = new std::string(str);
			length = data->length();
		}
		CZString(std::string& str, int start, int length){
			if (start > str.length() || start + length > str.length()){
				data = new std::string();
				length = 0;
			}
			else{
				data = new std::string(str.begin() + start, str.begin() + start + length);
				length = data->length();
			}
		}

		CZString(std::string& str, int count){
			data = new std::string(str);
			while (--count){
				data->append(str);
			}
		}
		template<class InputIt>
		CZString(InputIt first, InputIt last){
			data = new std::string(first, last);
			length = data->length();
		}

		std::vector<CZString> Split(char x);
		void Insert(int index, CZString& src);
		void Insert(int index, std::string& src);
		void Insert(int index, char src);
		CZString& Sub(int start, int end);
		void RemoveBackWhiteSpace();
		void RemoveFrontWhiteSpace();
		void RemoveBackDuplicateChar(char x);
		void RemoveFrontDuplicateChar(char x);

		std::string toString()const {return *data;}
		int Length()const{ return length; }
		char ChatAt(int index){ return (*data)[index]; }
		static bool IsSpace(char x){ return x == ' ' || x == '\n' || x == '\r' || x == '\t'; }
		static int Stoi(const CZString& _Str){ return std::stoi(_Str.toString()); }
		static long Stol(const CZString& _Str){ return std::stol(_Str.toString()); }
		static long long Stoll(const CZString* _Str){ return std::stoll(_Str->toString()); }
		static float Stof(const CZString& _Str){ return std::stof(_Str.toString()); }
		static double Stod(const CZString& _Str){ return std::stod(_Str.toString()); }
		static double Stold(const CZString& _Str){ return std::stold(_Str.toString()); }
		template <typename T>
		static CZString NumToString(T value){ std::string temp = std::to_string(value); return CZString(temp);}
	};
}
#endif