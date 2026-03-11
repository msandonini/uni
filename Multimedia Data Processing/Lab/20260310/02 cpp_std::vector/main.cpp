#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <fstream>
#include <numeric>
#include <ostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

std::vector<int> read_from_file(const std::string filename) {
	// RAII: Resource Allocation Is Initialization
	std::ifstream is(filename /*, std::ios::binary*/);
	std::vector<int> v;

	if (!is) return v;

	int d;
	while (is >> d) v.push_back(d);

	return v;
}

bool write_to_file(const std::string filename, const std::vector<int>& arr) {
	std::ofstream os(filename /*, std::ios::binary*/);

	if (!os) return false;

	for (const auto& x : arr) {
		// os << x << '\n';
		std::println(os, "{}\n", x);
	}

	return true;
}

struct person {
	std::string name, surname;
	int age;
};

template <typename T>
bool put_before(const T& a, const T& b) {
	return a < b;
}

/*
// Function object / Functor
template <typename T>
struct dist_avg {
	T avg;

	bool operator()(T& a, T& b) const {
		auto da = abs(a - avg);
		auto db = abs(b - avg);
		return da < db;
	}
};
*/

int main(int argc, char** argv) {
	if (argc != 3) {
		return 1;
	}

	std::vector<int> arr = read_from_file(argv[1]);

	// dist_avg<int> cmp = {80};
	// dist_avg<int> cmp = {.avg = 80};
	// dist_avg<int> cmp(80);
	// std::sort(arr.begin(), arr.end(), cmp);
	// std::sort(arr.begin(), arr.end(), dist_avg<double>(80));

	/*
	struct dist_avg {
		double avg;

		auto operator()(const int& a, const int& b) const {
			auto da = abs(a - avg);
			auto db = abs(b - avg);
			return da < db;
		}
	};
	std::sort(arr.begin(), arr.end(), dist_avg(80));
	*/

	/*
	auto avg = std::accumulate(arr.begin(), arr.end(), 0.0) / arr.size();
	// Any external object passed to the lambda is called closure
	// [=] Takes a copy of everything (and it's constant)
	// [&] Takes a reference to anything
	std::sort(arr.begin(), arr.end(), [&](int a, int b) {
		auto da = abs(a - avg);
		auto db = abs(b - avg);
		return da < db;
	});
	*/

	namespace rg = std::ranges;
	rg::sort(arr);

	/*
	struct person {
		std::std::string name, surname;
		int age;
	};
	std::vector<person> pvec = {{"Marco", "Rossi", 17},
								{"Luca", "Azzini", 32},
								{"Francesco", "Lucchini", 42}};
	// Using a projection makes it possible to sort directly based on a
	// specific attribute of an object
	rg::sort(pvec, {}, &person::age);
	*/

	for (const auto& x : arr) std::println("{}\n", x);

	write_to_file(argv[2], arr);

	return 0;
}
