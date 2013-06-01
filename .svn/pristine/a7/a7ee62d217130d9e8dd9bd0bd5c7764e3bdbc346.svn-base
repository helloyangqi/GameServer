/*
 * ByteBuffer.h
 *
 *  Created on: 2013-5-31
 *      Author: YangQi
 */

#ifndef BYTEBUFFER_H_
#define BYTEBUFFER_H_

#include "Common.h"

class ByteBufferException
{
public:
	ByteBufferException(bool add,size_t pos, size_t esize, size_t size)
	:m_add(add), m_pos(pos) , m_esize(esize), m_size(size)
	{
		PrintPosError();
	}

	void PrintPosError() const;
private:
	bool m_add;
	size_t m_pos;
	size_t m_esize;
	size_t m_size;
};


template<class T>
struct Unused
{
	Unused(){}
};

class ByteBuffer
{
public:
	const static size_t sDefaultSize = 0x1000;


	ByteBuffer():m_rpos(0), m_wpos(0)
	{
		m_storage.reserve(sDefaultSize);
	}

	ByteBuffer(size_t size):m_rpos(0), m_wpos(0)
	{
		m_storage.reserve(size);
	}


	ByteBuffer(const ByteBuffer& buf): m_rpos(buf.m_rpos), m_wpos(buf.m_wpos), m_storage(buf.m_storage)
	{

	}

	void clear()
	{
		m_storage.clear();
		m_rpos = 0;
		m_wpos = 0;
	}

	template <typename T>
	void put(size_t pos, T value)
	{
		//EndianConvert(value);
		put(pos, (char*)&value, sizeof(value));
	}

	/*
	 * unsigned
	 */
	ByteBuffer& operator<<(uint8 value)
	{
		append<uint8>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint16 value)
	{
		append<uint16>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint32 value)
	{
		append<uint32>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint64 value)
	{
		append<uint64>(value);
		return *this;
	}

	/*
	 * signed
	 */
	ByteBuffer& operator<<(int8 value)
	{
		append<int8>(value);
		return *this;
	}

	ByteBuffer& operator<<(int16 value)
	{
		append<int16>(value);
		return *this;
	}

	ByteBuffer& operator<<(int32 value)
	{
		append<int32>(value);
		return *this;
	}

	ByteBuffer& operator<<(int64 value)
	{
		append<int64>(value);
		return *this;
	}

	ByteBuffer& operator<<(float value)
	{
		append<float>(value);
		return *this;
	}

	ByteBuffer& operator<<(double value)
	{
		append<double>(value);
		return *this;
	}

	ByteBuffer& operator<<(const string& value)
	{
		append((uint8 const*)value.c_str(), value.length());
		append((uint8)0);
		return *this;
	}

	ByteBuffer& operator<<(const char *str)
	{
		append((uint8 const*)value, strlen(str));
		append((uint8)0);
		return *this;
	}

	template<typename T>
	ByteBuffer& operator<<(ByteBuffer& b, vector<T> const& v)
	{
		b<<(uint32)v.size();
		for(typename vector<T>::iterator i = v.begin(); i != v.end(); ++i)
		{
			b<<*i;
		}
		return b;
	}

	template<typename T>
	ByteBuffer& operator<<(ByteBuffer& b, list<T> const& v)
	{
		b<<(uint32)v.size();
		for(typename list<T>::iterator i = v.begin(); i != v.end(); ++i)
		{
			b<<*i;
		}
		return b;
	}

	template<typename K,typename V>
	ByteBuffer& operator<<(ByteBuffer& b, map<K,V>& m)
	{
		b<<(uint32)m.size();
		for(typename map<K,V>::itorator i = m.begin(); i != m.end(); ++i)
		{
			b<<i->first<<i->second;
		}
		return b;
	}




	ByteBuffer& operator>>(bool& value)
	{
		value = read<char>() > 0 ? true : false;
		return *this;
	}

	ByteBuffer& operator>>(uint8& value)
	{
		value = read<uint8>();
		return *this;
	}

	ByteBuffer& operator>>(uint16& value)
	{
		value = read<uint16>();
		return *this;
	}

	ByteBuffer& operator>>(uint32& value)
	{
		value = read<uint32>();
		return *this;
	}

	ByteBuffer& operator>>(uint64& value)
	{
		value = read<uint64>();
		return *this;
	}

	ByteBuffer& operator>>(int8& value)
	{
		value = read<int8>();
		return *this;
	}

	ByteBuffer& operator>>(int16& value)
	{
		value = read<int16>();
		return *this;
	}

	ByteBuffer& operator>>(int32& value)
	{
		value = read<int32>();
		return *this;
	}

	ByteBuffer& operator>>(int64& value)
	{
		value = read<int64>();
		return *this;
	}

	ByteBuffer& operator>>(float& value)
	{
		value = read<float>();
		return *this;
	}

	ByteBuffer& operator>>(double& value)
	{
		value = read<double>();
		return *this;
	}

	ByteBuffer& operator>>(string& value)
	{
		value.clear();
		while(rpos() < size())
		{
			char c = read<char>();
			if(c == 0)
				break;
			value += c;
		}
		return *this;
	}

	template<class T>
	ByteBuffer& operator>>(Unused<T> const&)
	{
		read_skip<T>();
		return *this;
	}

	template<typename T>
	ByteBuffer& operator>>(ByteBuffer& b, vector<T> &v)
	{
		uint32 vsize;
		b>>vsize;
		v.clear();
		while(vsize--)
		{
			T t;
			b >> t;
			v.push_back(t);
		}
		return b;
	}


	template<typename T>
	ByteBuffer& operator>>(ByteBuffer& b, list<T> &v)
	{
		uint32 vsize;
		b>>vsize;
		v.clear();
		while(vsize--)
		{
			T t;
			b >> t;
			v.push_back(t);
		}
		return b;
	}

	template<typename K,typename V>
	ByteBuffer& operator>>(ByteBuffer& b, map<K,V> &m)
	{
		uint32 msize;
		b>>msize;
		m.clear();
		while(msize--)
		{
			K k;
			V v;
			b >> k >> v;
			m.insert(make_pair(k, v));
		}
		return b;
	}

	void append(const string& str)
	{
		append((uint8 const*)str.c_str(), str.size()+1);
	}

	void append(const char *src, size_t cnt)
	{
		append((uint8 const*)src, cnt);
	}

	template<class T>
	void append(const T *src, size_t cnt)
	{
		append((const uint8*)src, cnt * sizeof(T));
	}

	void append(const uint8* src, size_t cnt)
	{
		if(!cnt)
			return;
		assert(size() < 10000000);
		if(m_storage.size() < m_rpos + cnt)
			m_storage.resize(m_rpos + cnt);
		memcpy((void*)&m_storage[m_wpos], (void*)src, cnt);
		m_wpos += cnt;
	}

	void append(const ByteBuffer& buffer)
	{
		if(buffer.wpos())
			append(buffer.contents(), buffer.wpos());
	}


	template<typename T>
	T read()
	{
		T r = read<T>(m_rpos);
		m_rpos += sizeof(T);
		return r;
	}

	template<typename T>
	T read(size_t pos)
	{
		if(pos + sizeof(T) > size())
			throw ByteBufferException(false, pos, sizeof(T), size());
		T val = *((T const*)&m_storage[pos]);
		//EndianConvert(val);
		return val;
	}

	void read(uint8 *dest, size_t len)
	{
		if(m_rpos + len > size())
			throw ByteBufferException(false, m_rpos, len, size());
		memcpy((void*)dest,(void*)&m_storage[m_rpos],len);
		m_rpos += len;
	}

	uint8 operator[](size_t pos) const
	{
		return read<uint8>(pos);
	}

	size_t rpos() const { return m_rpos; }
	size_t rpos(size_t rpos)
	{
		m_rpos = rpos;
		return m_rpos;
	}

	size_t wpos() const { return m_wpos; }
	size_t wpos(size_t wpos)
	{
		m_wpos = wpos;
		return m_wpos;
	}

	template<typename T>
	void read_skip()
	{
		read_skip(sizeof(T));
	}

	void read_skip(size_t skip)
	{
		if(m_rpos + skip > size())
			throw ByteBufferException(false, m_rpos, skip, size());
		m_rpos += skip;
	}

	const uint8* contents() const
	{
		return &m_storage[0];
	}

	size_t size() const
	{
		return m_storage.size();
	}

	bool empty() const
	{
		return m_storage.empty();
	}

	void resize(size_t newsize)
	{
		m_storage.resize(newsize);
		m_rpos = 0;
		m_wpos = size();
	}

private:
	/*
	 * limited for internal use
	 */
	template<typename T>
	void append(T value)
	{
		//Endianconvert(value);
		append((uint8*)&value, sizeof(value));
	}
protected:
		size_t m_rpos;		//read pos
		size_t m_wpos;		//write pos
		vector<char*> m_storage;
};



template<>
inline void ByteBuffer::read_skip<char*>()
{
	string temp;
	*this >> temp;
}

template<>
inline void ByteBuffer::read_skip<char const*>()
{
	read_skip<char*>();
}

template<>
inline void ByteBuffer::read_skip<string>()
{
	read_skip<char*>();
}




#endif /* BYTEBUFFER_H_ */
