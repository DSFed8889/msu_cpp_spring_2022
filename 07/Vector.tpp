#pragma once

#include <iterator>
#include <memory>
#include <initializer_list>

#include "Vector.hpp"


namespace Iterator {
	
	template<typename T>
	T *Allocator<T>::allocate(size_t count) {
		return new T[count];
	}
	
	template<typename T>
	void Allocator<T>::deallocate(T *ptr, size_t) {
		delete[] ptr;
	}
	
	
	template<typename T>
	Iterator<T>::Iterator() : _ptr(nullptr) {}
	
	template<typename T>
	Iterator<T>::Iterator(T *rhs) : _ptr(rhs) {}
	
	template<typename T>
	Iterator<T>::Iterator(const Iterator <T> &rhs) : _ptr(rhs._ptr) {}
	
	template<typename T>
	Iterator <T> &Iterator<T>::operator=(T *rhs) {
		_ptr = rhs;
		return *this;
	}
	
	template<typename T>
	Iterator <T> &Iterator<T>::operator=(const Iterator <T> &rhs) {
		_ptr = rhs._ptr;
		return *this;
	}
	
	template<typename T>
	Iterator <T> &Iterator<T>::operator+=(typename Iterator<T>::difference_type rhs) {
		_ptr += rhs;
		return *this;
	}
	
	template<typename T>
	Iterator <T> &Iterator<T>::operator-=(typename Iterator<T>::difference_type rhs) {
		_ptr -= rhs;
		return *this;
	}
	
	template<typename T>
	T &Iterator<T>::operator*() const {
		return *_ptr;
	}
	
	template<typename T>
	T *Iterator<T>::operator->() const {
		return _ptr;
	}
	
	template<typename T>
	T &Iterator<T>::operator[](typename Iterator<T>::difference_type rhs) const {
		return _ptr[rhs];
	}
	
	template<typename T>
	Iterator <T> &Iterator<T>::operator++() {
		++_ptr;
		return *this;
	}
	
	template<typename T>
	Iterator <T> &Iterator<T>::operator--() {
		--_ptr;
		return *this;
	}
	
	template<typename T>
	Iterator <T> Iterator<T>::operator++(int) const {
		Iterator <T> tmp(*this);
		++_ptr;
		return tmp;
	}
	
	template<typename T>
	Iterator <T> Iterator<T>::operator--(int) const {
		Iterator <T> tmp(*this);
		--_ptr;
		return tmp;
	}
	
	template<typename T>
	Iterator <T> Iterator<T>::operator+(const Iterator <T> &rhs) {
		return Iterator<T>(_ptr + rhs.ptr);
	}
	
	template<typename T>
	typename Iterator<T>::difference_type Iterator<T>::operator-(const Iterator <T> &rhs) const {
		return _ptr - rhs.ptr;
	}
	
	template<typename T>
	Iterator <T> Iterator<T>::operator+(typename Iterator<T>::difference_type rhs) const {
		return Iterator<T>(_ptr + rhs);
	}
	
	template<typename T>
	Iterator <T> Iterator<T>::operator-(typename Iterator<T>::difference_type rhs) const {
		return Iterator<T>(_ptr - rhs);
	}
	
	template<typename T>
	Iterator <T> operator+(typename Iterator<T>::difference_type lhs, const Iterator <T> &rhs) {
		return Iterator<T>(lhs + rhs._ptr);
	}
	
	template<typename T>
	Iterator <T> operator-(typename Iterator<T>::difference_type lhs, const Iterator <T> &rhs) {
		return Iterator<T>(lhs - rhs._ptr);
	}
	
	template<typename T>
	bool Iterator<T>::operator==(const Iterator <T> &rhs) const {
		return _ptr == rhs._ptr;
	}
	
	template<typename T>
	bool Iterator<T>::operator!=(const Iterator <T> &rhs) const {
		return _ptr != rhs._ptr;
	}
	
	template<typename T>
	bool Iterator<T>::operator>(const Iterator <T> &rhs) const {
		return _ptr > rhs._ptr;
	}
	
	template<typename T>
	bool Iterator<T>::operator<(const Iterator <T> &rhs) const {
		return _ptr < rhs._ptr;
	}
	
	template<typename T>
	bool Iterator<T>::operator>=(const Iterator <T> &rhs) const {
		return _ptr >= rhs._ptr;
	}
	
	template<typename T>
	bool Iterator<T>::operator<=(const Iterator <T> &rhs) const {
		return _ptr <= rhs._ptr;
	}
}

namespace customVector {
	
	template<typename T>
	Vector<T>::Vector() {
		size_ = 0;
		capacity_ = 4;
		data_ = allocator_.allocate(capacity_);
	}
	
	template<typename T>
	Vector<T>::Vector(size_t size) {
		if (size < 4) {
			size_ = 0;
			capacity_ = 4;
		} else {
			size_ = 0;
			capacity_ = 1;
			while (size > 0) {
				size >>= 1;
				capacity_ <<= 1;
			}
		}
		data_ = allocator_.allocate(capacity_);
	}
	
	template<typename T>
	Vector<T>::Vector(size_t size, const T &defaultValue) {
		if (size < 4) {
			size_ = 0;
			capacity_ = 4;
		} else {
			size_ = size;
			capacity_ = 1;
			while (size > 0) {
				size >>= 1;
				capacity_ <<= 1;
			}
		}
		data_ = allocator_.allocate(capacity_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] = defaultValue;
	}
	
	template<typename T>
	Vector<T>::Vector(std::initializer_list<T> init) {
		if (init.size() < 4) {
			size_ = init.size();
			capacity_ = 4;
		} else {
			size_ = init.size();
			capacity_ = 1;
			while (size_ > 0) {
				size_ >>= 1;
				capacity_ <<= 1;
			}
			size_ = init.size();
		}
		data_ = allocator_.allocate(capacity_);
		auto current = init.begin();
		const auto end = init.end();
		for (size_t i = 0; current != end; ++i)
			data_[i] = *current++;
	}
	
	template<typename T>
	Vector<T>::Vector(const Vector <T> &other) {
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = allocator_.allocate(capacity_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
	}
	
	template<typename T>
	Vector<T>::~Vector() {
		clear();
	}
	
	template<typename T>
	Vector <T> &Vector<T>::operator=(const Vector <T> &other) {
		if (&other == this)
			return *this;
		
		clear();
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = allocator_.allocate(capacity_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
		
		return *this;
	}
	
	template<typename T>
	T &Vector<T>::operator[](size_t ind) {
		return data_[ind];
	}
	
	template<typename T>
	void Vector<T>::push_back(T &&elem) {
		if (data_) {
			if (size_ == capacity_)
				resize(capacity_ + 1);
			data_[size_++] = elem;
		} else {
			size_ = 0;
			capacity_ = 4;
			data_ = allocator_.allocate(capacity_);
			data_[size_++] = elem;
		}
	}
	
	template<typename T>
	void Vector<T>::pop_back() {
		--size_;
		if (capacity_ >= 8 && size_ <= capacity_ / 4)
			resize(capacity_ / 2 - 1);
	}
	
	template<typename T>
	template<typename ... Args>
	void Vector<T>::emplace_back(Args &&... args) {
		if (data_) {
			if (size_ == capacity_)
				resize(capacity_ + 1);
			data_[size_++] = T(args...);
		} else {
			size_ = 0;
			capacity_ = 4;
			data_ = allocator_.allocate(capacity_);
			data_[size_++] = T(args...);
		}
	}
	
	template<typename T>
	bool Vector<T>::empty() const {
		return size_ == 0;
	}
	
	template<typename T>
	size_t Vector<T>::size() const {
		return size_;
	}
	
	template<typename T>
	void Vector<T>::clear() {
		if (data_)
			allocator_.deallocate(data_, capacity_);
		size_ = 0;
		capacity_ = 0;
		data_ = nullptr;
	}
	
	template<typename T>
	Iterator::Iterator <T> Vector<T>::begin() {
		return Iterator::Iterator<T>(data_);
	}
	
	template<typename T>
	Iterator::Iterator <T> Vector<T>::rbegin() {
		return Iterator::Iterator<T>(data_ + size_ - 1);
	}
	
	template<typename T>
	Iterator::Iterator <T> Vector<T>::end() {
		return Iterator::Iterator<T>(data_ + size_);
	}
	
	template<typename T>
	Iterator::Iterator <T> Vector<T>::rend() {
		return Iterator::Iterator<T>(data_ - 1);
	}
	
	template<typename T>
	void Vector<T>::resize(size_t count) {
		Vector <T> tmp = *this;
		clear();
		if (count < tmp.size_)
			size_ = count;
		else
			size_ = tmp.size_;
		capacity_ = 1;
		while (count > 0) {
			count >>= 1;
			capacity_ <<= 1;
		}
		data_ = allocator_.allocate(capacity_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] = tmp[i];
	}
	
	template<typename T>
	void Vector<T>::reserve(size_t size) {
		resize(capacity_ + size);
	}
	
	template<typename T>
	size_t Vector<T>::capacity() const {
		return capacity_;
	}
}
