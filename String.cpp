#include "String.h"
namespace cz{
	std::vector<CZString> CZString::Split(char x){
		RemoveFrontWhiteSpace();
		RemoveBackWhiteSpace();
		RemoveFrontDuplicateChar(x);
		RemoveBackDuplicateChar(x);
		int cur = 0, last = 0;
		std::vector<CZString> res;
		res.reserve(10);
		while (cur < Length()){
			if (ChatAt(cur) == x){
				CZString temp(data->begin() + last, data->begin() + cur);
				res.push_back(temp);
				while (ChatAt(cur) == x){
					cur++;
					continue;
				}
				last = cur;
			}
			cur++;
		}
		if (last != Length()){
			CZString temp(data->begin() + last, data->begin() + cur);
			res.push_back(temp);
		}
		return res;
	}
	void CZString::RemoveBackWhiteSpace(){
		int last = Length() - 1;
		while (last >= 0 && IsSpace(ChatAt(last))){
			last--;
		}
		if (last >= 0)
			data = new std::string(data->begin(), data->begin() + last + 1);
		else
			data = new std::string(data->begin(), data->begin());
		length = data->length();
	}

	void CZString::RemoveFrontWhiteSpace(){
		int cur = 0;
		while (cur < Length() && IsSpace(ChatAt(cur))){
			cur++;
		}
		data = new std::string(data->begin() + cur, data->end());
		length = data->length();
	}

	void CZString::RemoveBackDuplicateChar(char x){
		int last = Length() - 1;
		while (last >= 0 && ChatAt(last) == x){
			last--;
		}
		if (last >= 0)
			data = new std::string(data->begin(), data->begin() + last + 1);
		else
			data = new std::string(data->begin(), data->begin());
		length = data->length();
	}
	void CZString::RemoveFrontDuplicateChar(char x){
		int cur = 0;
		while (cur < Length() && ChatAt(cur) == x){
			cur++;
		}
		data = new std::string(data->begin() + cur, data->end());
		length = data->length();
	}

	void CZString::Insert(int index, CZString& src){
		CHECK_ERROR(index >= 0 && index <= length, "CZString::Insert(int,CZString)#参数count越界。");
		data->insert(index, src.toString());
		length = data->length();
	}
	void CZString::Insert(int index, std::string& src){
		CHECK_ERROR(index >= 0 && index <= length, "CZString::Insert(int,string)#参数count越界。");
		data->insert(index, src);
		length = data->length();
	}
	void CZString::Insert(int index, char src){
		CHECK_ERROR(index >= 0 && index <= length, "CZString::Insert(int,char)#参数index越界。");
		std::string temp(1, src);
		data->insert(index, temp);
		length = data->length();
	}

	CZString& CZString::Sub(int start, int count){
		CHECK_ERROR(start >= 0 && count + start <= length, "CZString::Sub(int,int)#参数越界。");
		data = new std::string (data->begin() + start, data->begin() + start + count);
		length = data->length();
		return *this;
	}
}