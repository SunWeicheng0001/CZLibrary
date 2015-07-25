#ifndef CZFILE_H
#define CZFILE_H
#include "Basics.h"
#include "String.h"
#include "Interface.h"
#include <cstdio>
namespace cz{
	namespace stream{
		class CZFileStream :public Object, public virtual IStream{
		public:
			enum AccessRight{
				ReadOnly,
				WriteOnly,
				ReadWrite
			};
		protected:
			AccessRight		mAccessRight;
			FILE*			mFile;
		public:
			CZFileStream(const CZString& fileName, AccessRight _accessRight);
			~CZFileStream();

			bool					CanRead()const;
			bool					CanWrite()const;
			bool					CanSeek()const;
			bool					CanPeek()const;
			bool					IsLimited()const;
			bool					IsAvailable()const;
			void					Close();
			pos_t					Position()const;
			pos_t					Size()const;
			void					Seek(pos_t _size);
			void					SeekFromBegin(pos_t _size);
			void					SeekFromEnd(pos_t _size);
			cint					Read(void* _buffer, cint _size);
			cint					Write(void* _buffer, cint _size);
			cint					Peek(void* _buffer, cint _size);
		};
	}
}
#endif