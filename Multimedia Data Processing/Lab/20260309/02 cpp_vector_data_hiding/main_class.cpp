#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <utility>

// static int cmp_int32(const void *a, const void *b) {
//     int32_t ia = *(const int32_t *)a;
//     int32_t ib = *(const int32_t *)b;
//     return (ia > ib) - (ia < ib);
// }

namespace mdp {

template <typename T>
class vector {
	// -- 2: class --
	// We changed the `struct` keyword to `class`
	// A class is basically a struct but where all code inside is private by
	// default
	// -- 2 --

	// -- 1: data hiding --
	// In order to make it possible to hide or show specific data outside of our
	// struct we can use the `private` and `public keywords`.
	// Usually structs have public parts in the start and private part at the
	// bottom, while for classes it's the other way
	// -- 2 --

  private:
	T* data_;
	size_t n_;
	size_t cap_;

  public:
	// Default constructor
	vector() {
		printf("vector()\n");
		data_ = nullptr;
		n_ = 0;
		cap_ = 0;
	}
	// Constructor with starting size
	vector(size_t n) {
		printf("vector(size_t n)\n");
		n_ = n;
		cap_ = n;
		data_ = new T[n];
	}
	// Copy constructor
	vector(const vector& other) {  // const reference to vector
		printf("vector(const vector& other)\n");
		n_ = other.n_;
		cap_ = other.cap_;
		data_ = new T[n_];
		for (size_t i = 0; i < n_; ++i) {
			data_[i] = other.data_[i];
		}
	}
	// Move constructor
	vector(vector&& other) {  // r-value reference to vector
		printf("vector(vector &&other)\n");
		n_ = other.n_;
		cap_ = other.cap_;
		data_ = other.data_;
		other.data_ = nullptr;
	}

	// -- 5: Better assignment --

	/*
	// Assignment operator
	vector& operator=(const vector& rhs) {
		printf("vector& operator=(const vector &rhs)\n");
		if (this == &rhs) {
			return *this;
		}
		n_ = rhs.n_;
		cap_ = rhs.cap_;
		delete[] data_;
		data_ = new T[n_];
		for (size_t i = 0; i < n_; ++i) {
			data_[i] = rhs.data_[i];
		}
		return *this;
	}
	*/
	// The = copy operator as we wrote it before was good, but it's quite long,
	// so let's shorten it by using every new thing:
	vector operator=(const vector rhs) {
		using std::swap;  // Enables SDL
		swap(*this, rhs);
		return *this;
	}
	// This is called Assignment operator with Copy and Move Idiom, as with this
	// new syntax it makes the move assignment operator redundant
	/*
	// Move assignment operator
	vector& operator=(vector&& rhs) {
		printf("vector &operator=(vector &&rhs)\n");
		n_ = rhs.n_;
		cap_ = rhs.cap_;
		delete[] data_;
		data_ = rhs.data_;
		rhs.data_ = nullptr;
		return *this;
	}
	*/
	// -- 5 --

	~vector() {
		printf("~vector()\n");
		delete[] data_;
	}

	void push_back(const T& val) {
		if (n_ == cap_) {
			size_t new_cap = (cap_ == 0) ? 4 : cap_ * 2;
			T* tmp = new T[new_cap];
			for (size_t i = 0; i < n_; ++i) {
				tmp[i] = data_[i];
			}
			delete[] data_;
			data_ = tmp;
			cap_ = new_cap;
		}
		data_[n_] = val;
		n_++;
	}
	// void sort() {
	//     qsort(data_, n_, sizeof(int32_t), cmp_int32);
	// }
	size_t size() const { return n_; }
	const T& at(size_t pos) const {
		assert(pos < n_);
		return data_[pos];
	}
	const T& operator[](size_t pos) const { return data_[pos]; }
	T& operator[](size_t pos) { return data_[pos]; }

	// -- 3: static --
	/*
	// Now that we re-defined our object as a class, the swap function doesn't
	// work anymore since it cannot access private members.
	// To make it work again we can move it inside the class we can move it
	// inside and use the `static` keyword to define the fact that it is used
	// on objects different than `this` (so that we can call it as
	// `swap(v1, v2)` instead of v1.swap(v2))
	static void swap(vector<T>& left, vector<T>& right) {
		std::swap(left.n_, right.n_);
		std::swap(left.cap_, right.cap_);
		std::swap(left.data_, right.data_);
	}

	// In our case we don't want a static function, since it must be called as
	// `mdp::vector<int>::swap()`, which totally defies our objective of using
	// ADL in order to just write `swap()` without specifying namespaces
	*/
	// -- 3 --

	// -- 4: MA CI SONO GLI AMICIIIIII --
	// To solve the problem at point 3, we can use the `friend` keyword:
	friend void swap(vector<T>& left, vector<T>& right);

	/*
	// To use the `friend` keyword we also have the shorter option of defining
	// the function directly inside the class:

	friend void swap(vector<T>& left, vector<T>& right) {
		std::swap(left.n_, right.n_);
		std::swap(left.cap_, right.cap_);
		std::swap(left.data_, right.data_);
	}
	*/
	// -- 4 --
};

template <typename T>
void swap(vector<T>& left, vector<T>& right) {
	std::swap(left.n_, right.n_);
	std::swap(left.cap_, right.cap_);
	std::swap(left.data_, right.data_);
}

}  // namespace mdp

mdp::vector<int> read_from_file(const char* filename) {
	FILE* fin = fopen(filename, "r");
	if (!fin) {
		return mdp::vector<int>();
	}

	mdp::vector<int> v;

	char token[128];
	while (fscanf(fin, "%127s", token) == 1) {
		errno = 0;
		char* endp = NULL;
		long val = strtol(token, &endp, 10);
		if (*endp != '\0') {
			break;
		}
		if (errno == ERANGE || val < INT32_MIN || val > INT32_MAX) {
			break;
		}
		v.push_back(val);
	}
	fclose(fin);
	return v;
}

bool write_to_file(const char* filename, const mdp::vector<int>& arr) {
	FILE* fout = fopen(filename, "w");
	if (!fout) {
		return false;
	}
	for (size_t i = 0; i < arr.size(); i++) {
		fprintf(fout, "%d\n", arr[i]);
	}
	fclose(fout);
	return true;
}

struct person {
	char name[20], surname[20];
	int age;
};

int main(int argc, char** argv) {
	using std::swap;

	int x = 5, y = 4;
	std::swap(x, y);

	double z = 3, t = 42;
	std::swap(z, t);

	person a = {"Enzo", "Catania", 32};
	person b = {"Mario", "Rossi", 42};
	std::swap(a, b);

	mdp::vector<int> c;
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);

	mdp::vector<int> d;
	d.push_back(4);
	d.push_back(5);
	d.push_back(6);

	swap(c, d);

	if (argc != 3) {
		return 1;
	}

	const char* in_name = argv[1];
	const char* out_name = argv[2];

	mdp::vector<int> arr;
	arr = read_from_file(in_name);

	mdp::vector<double> darr;
	darr.push_back(3.5);

	mdp::vector<person> parr;
	parr.push_back({"Mario", "Rossi", 41});

	//    arr.sort();

	write_to_file(out_name, arr);

	return 0;
}