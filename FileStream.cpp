#include "FileStream.h"
namespace cz{
	namespace stream{
		CZFileStream::CZFileStream(const CZString& filename, AccessRight _accessRight)
			:mAccessRight(_accessRight){
			const wchar_t* mode = L"rb";
			switch (_accessRight){
			case ReadOnly:
				mode = L"rb";
				break;
			case WriteOnly:
				mode = L"wb";
				break;
			case ReadWrite:
				mode = L"w+b";
				break;
			}
			if (_wfopen_s(&mFile, (filename.ToWString()).c_str(), mode) != 0)
				mFile = 0;
		}

		CZFileStream::~CZFileStream(){
			Close();
		}

		bool CZFileStream::CanRead() const{
			return mFile != 0 && (mAccessRight == ReadOnly || mAccessRight == ReadWrite);
		}

		bool CZFileStream::CanWrite() const{
			return mFile != 0 && (mAccessRight == WriteOnly || mAccessRight == ReadWrite);
		}

		bool CZFileStream::CanSeek() const{
			return mFile != 0;
		}

		bool CZFileStream::CanPeek() const{
			return mFile != 0 && (mAccessRight == ReadOnly || mAccessRight == ReadWrite);
		}

		bool CZFileStream::IsLimited() const{
			return mFile != 0 && mAccessRight == ReadOnly;
		}

		bool CZFileStream::IsAvailable() const{
			return mFile != 0;
		}

		void CZFileStream::Close(){
			if (mFile != 0){
				fclose(mFile);
				mFile = 0;
			}
		}

		pos_t CZFileStream::Position() const{
			if (mFile != 0){
				fpos_t position = 0;
				if (fgetpos(mFile, &position) == 0)
					return position;
			}
			return -1;
		}

		pos_t CZFileStream::Size() const{
			if (mFile != 0){
				fpos_t position = 0;
				if (fgetpos(mFile, &position) == 0){
					if (fseek(mFile, 0, SEEK_END) == 0){
						pos_t size = Position();
						if (fsetpos(mFile, &position) == 0)
							return size;
					}
				}
			}
			return -1;
		}

		void CZFileStream::Seek(pos_t _size){
			if (Position() + _size > Size())
			{
				_fseeki64(mFile, 0, SEEK_END);
			}
			else if (Position() + _size < 0)
			{
				_fseeki64(mFile, 0, SEEK_SET);
			}
			else
			{
				_fseeki64(mFile, _size, SEEK_CUR);
			}
		}

		void CZFileStream::SeekFromBegin(pos_t _size){
			if (_size > Size())
			{
				_fseeki64(mFile, 0, SEEK_END);
			}
			else if (_size < 0)
			{
				_fseeki64(mFile, 0, SEEK_SET);
			}
			else
			{
				_fseeki64(mFile, _size, SEEK_CUR);
			}
		}

		void CZFileStream::SeekFromEnd(pos_t _size){
			if (_size<0)
			{
				_fseeki64(mFile, 0, SEEK_END);
			}
			else if (_size>Size())
			{
				_fseeki64(mFile, 0, SEEK_SET);
			}
			else
			{
				_fseeki64(mFile, -_size, SEEK_END);
			}
		}

		cint CZFileStream::Read(void* _buffer, cint _size){
			CHECK_ERROR(file != 0, "CZFileStream::Read(pos_t)#流处于关闭状态，不可执行此操作。");
			CHECK_ERROR(_size >= 0, "CZFileStream::Read(void*, vint)#参数size不可为负。");
			int res =  fread(_buffer, 1, _size, mFile);
			((char*)_buffer)[res] = '\0';
			return res;
		}

		cint CZFileStream::Write(void* _buffer, cint _size){
			CHECK_ERROR(file != 0, "CZFileStream::Write(pos_t)#流处于关闭状态，不可执行此操作。");
			CHECK_ERROR(_size >= 0, "CZFileStream::Write(void*, vint)#参数size不可为负。");
			return fwrite(_buffer, 1, _size, mFile);
		}

		cint CZFileStream::Peek(void* _buffer, cint _size)
		{
			CHECK_ERROR(file != 0, "CZFileStream::Peek(pos_t)#流处于关闭状态，不可执行此操作。");
			CHECK_ERROR(_size >= 0, "CZFileStream::Peek(void*, vint)#参数size不可为负。");
			fpos_t position = 0;
			if (fgetpos(mFile, &position) == 0)
			{
				size_t count = fread(_buffer, 1, _size, mFile);
				if (fsetpos(mFile, &position) == 0)
				{
					return count;
				}
			}
			return -1;
		}
	}
}