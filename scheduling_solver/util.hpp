#pragma once

//generates a range of integers between int_begin and int_end
template <int int_begin, int int_end>
class Range
{
public:
	class Iterator
	{
	private:
		int i;
	public:
		Iterator(int start) : i(start) { }
		
		//operator overloading
		Iterator operator ++() { ++i; return *this; }
		int operator *() { return i; }
		
		bool operator ==(const Iterator & other) const { return i == other.i; }
		bool operator !=(const Iterator & other) const { return i != other.i; }
	};
	
	Iterator begin() const { return Iterator(int_begin); }
	Iterator end() const { return Iterator(int_end); }
	
};
