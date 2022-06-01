#pragma once

#include <iterator>
#include <memory>
#include <initializer_list>

namespace Iterator {
	
	template<typename T>
	class Allocator
	{
	public:
		
		T* allocate(size_t count);
		
		void deallocate(T*ptr, size_t count);
	};
	
	
	template<typename T>
	class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
	public:
		
		Iterator();
		
		Iterator(T*rhs);
		
		Iterator(const Iterator<T> & rhs);
		
		Iterator<T> & operator=(T*rhs);
		
		Iterator<T> & operator=(const Iterator<T> & rhs);
		
		Iterator<T> & operator+=(difference_type rhs);
		
		Iterator<T> & operator-=(difference_type rhs);
		
		T& operator*() const;
		
		T*operator->() const;
		
		T& operator[](difference_type rhs) const;
		
		Iterator<T> & operator++();
		
		Iterator<T> & operator--();
		
		Iterator<T> operator++(int) const;
		
		Iterator<T> operator--(int) const;
		
		Iterator<T> operator+(const Iterator<T> & rhs);
		
		difference_type operator-(const Iterator<T> & rhs) const;
		
		Iterator<T> operator+(difference_type rhs) const;
		
		Iterator<T> operator-(difference_type rhs) const;
		
		template<typename Type>
		friend Iterator<Type> operator+(difference_type lhs, const Iterator<Type> & rhs);
		
		template<typename Type>
		friend Iterator<Type> operator-(difference_type lhs, const Iterator<Type> & rhs);
		
		bool operator==(const Iterator<T> & rhs) const;
		
		bool operator!=(const Iterator<T> & rhs) const;
		
		bool operator>(const Iterator<T> & rhs) const;
		
		bool operator<(const Iterator<T> & rhs) const;
		
		bool operator>=(const Iterator<T> & rhs) const;
		
		bool operator<=(const Iterator<T> & rhs) const;
	
	private:
		T*_ptr;
	};
}

namespace customVector
{
	template<typename T>
	class Vector {
	public:
		
		Vector();
		
		explicit Vector(size_t size);
		
		Vector(size_t size, const T& defaultValue);
		
		Vector(std::initializer_list <T> init);
		
		Vector(const Vector<T> & other);
		
		Vector<T> & operator=(const Vector<T> & other);
		
		T& operator[](size_t ind);
		
		void push_back(T&& elem);
		
		void pop_back();
		
		template<typename ... Args>
		void emplace_back(Args && ... args);
		
		bool empty() const;
		
		size_t size() const;
		
		void clear();
		
		Iterator::Iterator<T> begin();
		
		Iterator::Iterator<T> rbegin();
		
		Iterator::Iterator<T> end();
		
		Iterator::Iterator<T> rend();
		
		void resize(size_t count);
		
		void reserve(size_t size);
		
		size_t capacity() const;
		
		~Vector();
	
	private:
		T*data_;
		size_t size_;
		size_t capacity_;
		Iterator::Allocator<T> allocator_;
	};
}
#include "Vector.tpp"