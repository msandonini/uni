#include <fstream>
#include <string>

class bitreader {
	std::istream& is_;
	std::string buffer_();

  public:
	bitreader(std::istream& is) : is_(is) {}
};

int main(int argc, char const* argv[]) {
	/* code */
	return 0;
}
