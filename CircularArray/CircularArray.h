/*
MIT License

Copyright (c) 2022 Mohammad Ishrak Abedin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

namespace ish
{
	template<typename _Ty, size_t _Capacity>
	class CircularArray
	{
	private:
		_Ty m_Data[_Capacity] = {0};
		size_t m_Start = 0;
		size_t m_Next = 0;
		size_t m_Count = 0;
	public:
		CircularArray() {}

		CircularArray(const CircularArray& other)
		{
			for (size_t i = 0; i < _Capacity; i++)
			{
				m_Data[i] = other[i];
				m_Start = other.m_Start;
				m_Next = other.m_Next;
				m_Count = other.m_Count;
			}
		}

		CircularArray& operator=(const CircularArray& other)
		{
			for (size_t i = 0; i < _Capacity; i++)
			{
				m_Data[i] = other[i];
				m_Start = other.m_Start;
				m_Next = other.m_Next;
				m_Count = other.m_Count;
			}
			return *this;
		}

		CircularArray(CircularArray&& other)
		{
			for (size_t i = 0; i < _Capacity; i++)
			{
				m_Data[i] = std::move(other[i]);
				m_Start = other.m_Start;
				m_Next = other.m_Next;
				m_Count = other.m_Count;
			}
		}

		CircularArray& operator=(CircularArray&& other)
		{
			for (size_t i = 0; i < _Capacity; i++)
			{
				m_Data[i] = std::move(other[i]);
				m_Start = other.m_Start;
				m_Next = other.m_Next;
				m_Count = other.m_Count;
			}
			return *this;
		}
		
		~CircularArray() {}
		
		constexpr size_t Capacity() const { return _Capacity; }

		inline size_t Count() const { return m_Count; }

		inline size_t Start() const { return m_Start; }

		inline size_t Next() const { return m_Next; }

		_Ty* Data() { return m_Data; }

		const _Ty& operator[](size_t index) const
		{
			return m_Data[(m_Start + index) % _Capacity];
		}

		_Ty& operator[](size_t index)
		{
			return m_Data[(m_Start + index) % _Capacity];
		}

		void Add(const _Ty& item)
		{
			m_Data[m_Next] = item;
			m_Next = (m_Next + 1) % _Capacity;
			if (m_Count == _Capacity)
			{
				m_Start = (m_Start + 1) % _Capacity;
			}
			else m_Count++;
		}

		void Add(_Ty&& item)
		{
			m_Data[m_Next] = std::move(item);
			m_Next = (m_Next + 1) % _Capacity;
			if (m_Count == _Capacity)
			{
				m_Start = (m_Start + 1) % _Capacity;
			}
			else m_Count++;
		}

		template<typename... Args>
		_Ty& EmplaceBack(Args&&... args)
		{
			new(&m_Data[m_Next]) _Ty(std::forward<Args>(args)...);
			_Ty& rtrnRef = m_Data[m_Next];
			m_Next = (m_Next + 1) % _Capacity;
			if (m_Count == _Capacity)
			{
				m_Start = (m_Start + 1) % _Capacity;
			}
			else m_Count++;
			return rtrnRef;
		}

		void RemoveLastItem()
		{
			if (m_Count != 0)
			{
				m_Count--;
				m_Next = m_Next == 0 ? _Capacity - 1 : m_Next - 1;
			}
		}
	};
}