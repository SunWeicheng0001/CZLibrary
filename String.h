#ifndef CZ_STRING
#define CZ_STRING
#include "Basics.h"
#include <vector>
#include <iostream>
#include <sstream>
namespace cz{
	class CZString : public Object{
	private:
		std::string *data;
		int length;
	public:
		~CZString(){ delete data; }
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
			if (start > (int)str.length() || start + length > (int)str.length()){
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

		void			Assign(const std::string& str){ data = new std::string(str); length = data->length(); }
		void			Assign(const CZString& str){ data = new std::string(str.ToString()); length = data->length(); }
		void			Assign(const char* str){ data = new std::string(str); length = data->length(); }
		void			Assign(const char x){data = new std::string();data->push_back(x);length = 1;}
		std::vector<CZString> Split(char x);
		void			Insert(int index, CZString& src);
		void			Insert(int index, std::string& src);
		void			Insert(int index, char src);
		CZString&		Sub(int start, int end);
		void			RemoveBackWhiteSpace();
		void			RemoveFrontWhiteSpace();
		void			RemoveBackDuplicateChar(char x);
		void			RemoveFrontDuplicateChar(char x);
		std::wstring	ToWString() const;
		std::string		ToString()const {return *data;}
		bool			IsEmpty()const { return length == 0; }
		int				Length()const{ return length; }
		char			ChatAt(int index){ 
			CHECK_ERROR(index >= 0 && index < length, L"CZString::CharAtÖÐindexÔ½½ç");
			return (*data)[index]; 
		}
		static bool		IsSpace(char x){ return x == ' ' || x == '\n' || x == '\r' || x == '\t'; }
		static int		Stoi(const CZString& _Str){ return std::stoi(_Str.ToString()); }
		static long		Stol(const CZString& _Str){ return std::stol(_Str.ToString()); }
		static long long Stoll(const CZString* _Str){ return std::stoll(_Str->ToString()); }
		static float	Stof(const CZString& _Str){ return std::stof(_Str.ToString()); }
		static double	Stod(const CZString& _Str){ return std::stod(_Str.ToString()); }
		static double	Stold(const CZString& _Str){ return std::stold(_Str.ToString()); }
		template <typename T>
		static CZString NumToString(T value){ std::string temp = std::to_string(value); return CZString(temp);}
		CZString operator+(const CZString& str){ data->append(str.ToString()); length = data->length(); return *this; }
		CZString operator+(const char* str){ data->append(str); length = data->length(); return *this; }
		CZString operator+(const std::string& str){ data->append(str); length = data->length(); return *this; }
		CZString operator+(const char x){ data->append(&x); length = data->length(); return *this; }
		template <typename T>
		CZString operator+(T x){
			std::stringstream ss;ss << x;
			data->append(ss.str());
			length = data->length();
			return *this;
		}
		CZString& operator+=(const CZString& str){ data->append(str.ToString()); length = data->length(); return *this; }
		CZString& operator+=(const char* str){ data->append(str); length = data->length(); return *this; }
		CZString& operator+=(const std::string& str){ data->append(str); length = data->length(); return *this; }
		CZString& operator+=(const char x){ data->append(&x); length = data->length(); return *this; }
		bool operator==(const CZString& str){ return this->ToString() == str.ToString(); }
		bool operator==(const std::string& str){ return this->ToString() == str; }
		bool operator==(const char x){ return this->Length() == 1 && this->ChatAt(0) == x; }
		bool operator==(const char* str){ return this->ToString() == std::string(str); }
		char	operator[](int x){ return this->ChatAt(x); }
		template <typename T>
		CZString& operator+=(T x){
			std::stringstream ss; ss << x;
			data->append(ss.str());
			length = data->length();
			return *this;
		}
		friend std::ostream& operator<<(std::ostream & output, const CZString & str){
			output << str.ToString();
			return output;
		}
		friend std::istream& operator>>(std::istream& input, CZString & str){
			std::string temp;
			input >> temp;
			str.Assign(temp);
			return input;
		}
	};
	
}
#endif