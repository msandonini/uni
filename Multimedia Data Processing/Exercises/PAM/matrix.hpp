#pragma once

#include <cstdint>
#include <vector>

template <typename T>
class matrix {
  protected:
	size_t rows_, cols_;
	std::vector<T> data_;

  public:
	// -- CONSTRUCTORS & DESTRUCTORS --
	matrix() {};
	matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {}

	~matrix() {}

	// -- GETTERS --

	auto rows() const { return rows_; }
	auto cols() const { return cols_; }
	auto data() const { return data_; }
	auto size() const { return rows_ * cols_; }

	const char* rawdata() const {
		return reinterpret_cast<const char*>(data_.data());
	}
	char* rawdata() { return reinterpret_cast<char*>(data_.data()); }
	size_t rawsize() { return size(); }

	// -- METHODS --

	auto empty() const { return data_.empty(); }

	const T& at(size_t r, size_t c) const { return data_[r * cols_ + c]; }

	T& at(size_t r, size_t c) {
		return const_cast<T&>(static_cast<const matrix*>(this)->at(r, c));
	}

	// -- OVERLOADING --

	const T& operator()(size_t r, size_t c) const { return at(r, c); }
	T& operator()(size_t r, size_t c) { return at(r, c); }

	// -- ABSTRACT --

	virtual void loadPAM(const std::string& filename);
	virtual void savePAM(const std::string& filename);

	virtual void flip();
	virtual void mirror();
};