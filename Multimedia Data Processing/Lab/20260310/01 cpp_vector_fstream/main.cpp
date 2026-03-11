#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cassert>
#include <fstream>
#include <ostream>
#include <utility>

namespace mdp {

template <typename T>
class vector {
	T* data_;
	size_t n_;
	size_t cap_;

  public:
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
		n_ = other.n_;
		cap_ = other.cap_;
		data_ = new T[n_];
		std::copy_n(other.data_, n_, data_);
	}
	// Move constructor
	vector(vector&& other) noexcept {  // r-value reference to vector
		n_ = other.n_;
		cap_ = other.cap_;
		data_ = other.data_;
		other.data_ = nullptr;
	}
	// Assignment operator (Copy and Swap Idiom)
	vector& operator=(vector rhs) {
		using std::swap;  // Enables ADL
		swap(*this, rhs);
		return *this;
	}
	~vector() { delete[] data_; }

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

	// Option 1: declaration + definition
	// friend void swap(vector<T>& left, vector<T>& right);

	// Option 2: definition inside
	friend void swap(vector<T>& left, vector<T>& right) {
		std::swap(left.n_, right.n_);
		std::swap(left.cap_, right.cap_);
		std::swap(left.data_, right.data_);
	}
};

}  // namespace mdp

mdp::vector<int> read_from_file(const char* filename) {
	// RAII: Resource Allocation Is Initialization
	std::ifstream is(filename /*, std::ios::binary*/);
	mdp::vector<int> v;

	if (!is) return v;

	int d;
	while (is >> d) v.push_back(d);

	return v;
}

bool write_to_file(const char* filename, const mdp::vector<int>& arr) {
	std::ofstream os(filename /*, std::ios::binary*/);

	if (!os) return false;

	for (size_t i = 0; i < arr.size(); i++) {
		// os << arr[i] << '\n';
		std::println(os, "{}\n", arr[i]);
	}

	return true;
}

struct person {
	char name[20], surname[20];
	int age;
};

int main(int argc, char** argv) {
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