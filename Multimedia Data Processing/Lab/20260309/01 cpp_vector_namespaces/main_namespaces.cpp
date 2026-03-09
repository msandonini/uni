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
struct vector {
	T* data_;
	size_t n_;
	size_t cap_;

	// Default constructor
	vector() {
		data_ = nullptr;
		n_ = 0;
		cap_ = 0;
	}
	// Constructor with starting size
	vector(size_t n) {
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
};

// -- 3: Better swap inside our namespace --

template <typename T>
void swap(vector<T>& left, vector<T>& right) {
	std::swap(left.n_, right.n_);
	std::swap(left.cap_, right.cap_);
	std::swap(left.data_, right.data_);
}

// -- 3 --

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
	// -- 5: using keyword --

	// If we use the `using` keyword to define which swap() function we are
	// using, the compiler will automatically use this if no swap() function is
	// defined in a more specialized namespace, without the need to specify
	// which one to use everytime
	using std::swap;

	/*
	// We can also use the following:
	using namespace std;
	// This specifies that we always use the std namespace, but it's a bit of a
	// malpractice to use it and it should be used only if really needed (like
	// in some functions)
	*/

	/*
	// Instead of using `using namespace <name>` in order to avoid using long
	// namespace names, we can instead alias the names using the following:
	namespace n = std;
	*/

	// -- 5 --

	// -- 1: Use something from standard library (std namespace) --
	// This function can swap anything thanks to templates

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

	// std::swap(c, d);

	// -- 1 --

	// -- 2: std::move() --

	/*
	mdp::vector<int> tmp =
	c;  // This way of swapping is inefficient, since it copies the objects
		// for each initialization and assignment
	c = d;
	d = tmp;
	*/

	/*
	// In order to swap in a better way we can use std::move, so that instead of
	// the copy constructor and assignment it uses the move ones. The curly
	// brackets are used to define a scope, so that after the operation the tmp
	// variable is automatically destroyed
	{
		mdp::vector<int> tmp = std::move(c);
		c = std::move(d);
		d = std::move(tmp);
	}
	*/
	/*
	// Using the std::move is exactly like doing the following:
	{
		mdp::vector<int> tmp;
		tmp.n_ = c.n_;
		tmp.cap_ = c.cap_;
		tmp.data_ = c.data_;
		c.data_ = nullptr;  // Useless
		c.n_ = d.n_;
		c.cap_ = d.cap_;
		c.data_ = d.data_;
		delete[] c.data_;  // Useless
		c.data_ = d.data_;
		delete[] d.data_;   // Useless
		d.data_ = nullptr;  // Useless
		d.n_ = tmp.n_;
		d.cap_ = tmp.cap_;
		d.data_ = tmp.data_;
		delete[] tmp.data_;   // Useless
		tmp.data_ = nullptr;  // Useless
	}
	*/
	/*
	// By doing this, while it's better, it's still quite useless since it makes
	// a lot of useless calls. The even better way is the following:
	{
		std::swap(c.n_, d.n_);
		std::swap(c.cap_, d.cap_);
		std::swap(c.data_, d.data_);
	}
	// At this point we can just go inside our mdp namespace and implement a
	// swap function that works like this (point 3)
	*/

	// -- 2 --

	// -- 4: Use our new swap function --

	/*
	mdp::swap(c, d);
	// The namespace doesn't need to be specified since the compiler
	// automatically looks for the closest namespace (here, it selects mdp::swap
	// since it's defined in the same namespace of our vector)
	// If we had not defined mdp::swap this would get us an error, as there
	// would be no swap() function both in the same namespace of mdp::vector nor
	// in its parent namespaces.
	*/
	swap(c, d);	 // Argument-dependent lookup (ADL)
	// There is also a way to make it work even without the mdp::swap()
	// function definition (point 5)

	// -- 4 --

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