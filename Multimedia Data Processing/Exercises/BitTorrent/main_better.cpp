#include <cinttypes>
#include <fstream>
#include <map>
#include <string>
#include <vector>

struct elem {
	char type_;

	void read(std::ifstream& is);
};

struct elem_str : elem {
	std::string s_;

	void read(std::ifstream& is) {}
};

struct elem_int : elem {
	int64_t i_;
};

struct elem_list : elem {
	std::vector<elem> l_;
};

struct elem_dict : elem {
	std::map<std::string, elem> d_;
};

int main(int argc, char const* argv[]) {
	/* code */
	return 0;
}
