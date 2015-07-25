#ifndef CZ_BASIC_H
#define CZ_BASIC_H
#include <windows.h>
#include <string>
namespace cz{
	/************************************************************************
	NonCopyable                                                           
	************************************************************************/
		class NonCopyable{
		private:
			NonCopyable(const NonCopyable&);
			NonCopyable& operator=(const NonCopyable&);
		public:
			NonCopyable();
		};
	
		//error
		class Error
		{
		private:
			std::string			description;
		public:
			Error(std::string _description);
			std::string			Description()const;
		};
	#ifndef _DEBUG
		#define CHECK_ERROR(CONDITION, DESCRIPTION) do {if(!(CONDITION)throw Error(DESCRIPTION);} while (0);
	#endif
	#ifndef NDEBUG
		#define CHECK_ERROR(CONDITION, DESCRIPTION)
	#endif
	#define CHECK_FAIL(DESCRIPTION) do {throw Error(DESCRIPTION);} while (0);
	
		class Object{
		public:
			virtual ~Object();
		};

	template<typename T>
	class ObjectBox : public Object{
	private:
		T		object;
	public:
		ObjectBox(const T& _object){ this->object = _object; }
		const T& Unbox(){ return this->object; }
	};

	template<typename T, size_t minSize>
	union BinaryRetriver{
		T t;
		char binary[sizeof(T) > minSize ? sizeof(T) : minSize];
	};
	/************************************************************************/
	/*Time                                                                     */
	/************************************************************************/
	struct DateTime{
		int year;
		int month;
		int dayOfweek;
		int day;
		int hour;
		int minute;
		int second;
		int milliseconds;

		long long totalMilliseconds;
		long long filetime;
		static DateTime LocalTime();
		static DateTime UtcTime();

		DateTime	ToLocalTime();
		DateTime	ToUtcTime();
	};

	/************************************************************************
	Interface                                                               
	************************************************************************/
	class Interface :private NonCopyable{
	public:
		virtual ~Interface();
	};

	typedef signed __int64	pos_t;
	typedef signed __int64	cint;
}
#endif