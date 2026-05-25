#include <cstdint>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <print>
#include <string>
#include <variant>
#include <vector>

namespace bencode {

struct elem {
	using ptr_t = std::unique_ptr<elem>;

	virtual ~elem() = default;
	virtual std::istream& read(std::istream& is) = 0;
	virtual void print(std::ostream& os, int tab = 0) const = 0;

	static ptr_t factory(std::istream& is, const std::string& name = "");

	static std::string get_string(std::istream& is) {
		size_t len;
		is >> len;
		if (is.get() != ':') {
			throw std::runtime_error("Missing : after the string length");
		}
		std::string s(len, 0);
		is.read(s.data(), len);
		if (!is || is.gcount() != len) {
			throw std::runtime_error("Failed to read the string");
		}
		return s;
	}
};

struct integer : public elem {
	int64_t i_;

	std::istream& read(std::istream& is) override {
		if (is.get() != 'i') {
			throw std::runtime_error("Expecting an i");
		}
		is >> i_;
		if (is.get() != 'e') {
			throw std::runtime_error("Missing e after an integer");
		}
		return is;
	}

	void print(std::ostream& os, int tab) const override { std::print("{}", i_); }
};

struct string : public elem {
	std::string s_;

	std::istream& read(std::istream& is) override {
		s_ = get_string(is);
		return is;
	}

	void print(std::ostream& os, int tab) const override {
		for (const auto& c : s_) {
			std::print("{}", 32 <= c && c <= 126 ? c : '.');
		}
	}
};

struct list : public elem {
	std::vector<ptr_t> l_;

	std::istream& read(std::istream& is) override {
		if (is.get() != 'l') {
			throw std::runtime_error("Expecting an l");
		}
		while (is.peek() != 'e') {
			l_.emplace_back(factory(is));
		}
		if (is.get() != 'e') {
			throw std::runtime_error("Missing e after a list");
		}
		return is;
	}

	void print(std::ostream& os, int tab) const override {
		std::string indent(tab, '\t');
		std::println(os, "[");
		for (const auto& e : l_) {
			std::print(os, "{}\t", indent);
			e->print(os, tab + 1);
			std::println(os);
		}
		std::print(os, "{}]", indent);
	}
};

struct dict : public elem {
	std::map<std::string, ptr_t> d_;

	std::istream& read(std::istream& is) override {
		if (is.get() != 'd') {
			throw std::runtime_error("Expecting an d");
		}
		while (is.peek() != 'e') {
			auto key = get_string(is);
			d_[key] = factory(is, key);
		}
		if (is.get() != 'e') {
			throw std::runtime_error("Missing e after a dictionary");
		}
		return is;
	}

	void print(std::ostream& os, int tab) const override {
		std::string indent(tab, '\t');
		std::println(os, "{{");
		for (const auto& [k, v] : d_) {
			std::print(os, "{}\t{} => ", indent, k);
			v->print(os, tab + 1);
			std::println(os);
		}
		std::print(os, "{}}}", indent);
	}
};

typedef elem::ptr_t (*create_fn)();
// std::map<std::string, create_fn> factory_map; // Doesn't accept lambdas
std::map<std::string, std::function<elem::ptr_t()>> factory_map;

elem::ptr_t elem::factory(std::istream& is, const std::string& name) {
	ptr_t e;

	auto it = factory_map.find(name);
	if (it != end(factory_map)) {
		e = it->second();
	} else {
		char next = is.peek();
		switch (next) {
			break;
			case 'd':
				e = std::make_unique<dict>();
				break;
			case 'l':
				e = std::make_unique<list>();
				break;
			case 'i':
				e = std::make_unique<integer>();
				break;
			default:
				e = std::make_unique<string>();
		}
	}
	e->read(is);
	return e;
}

}  // namespace bencode

struct pieces : public bencode::string {
	void print(std::ostream& os, int tab) const override {
		std::string indent(tab, '\t');
		for (size_t i = 0; i < s_.size(); i += 20) {
			std::print(os, "\n{}\t", indent);
			for (size_t j = 0; j < 20; ++j) {
				std::print(os, "{:02x}", s_[i + j]);
			}
		}
	}
};
bencode::elem::ptr_t create_pieces() {
	return std::make_unique<pieces>();
}

int main(int argc, char* argv[]) {
	bencode::factory_map["pieces"] = []() { return std::make_unique<pieces>(); };
	// https://www.nirfriedman.com/2018/04/29/unforgettable-factory/

	if (argc != 2) {
		return EXIT_FAILURE;
	}

	std::ifstream is(argv[1], std::ios::binary);
	if (!is) {
		return EXIT_FAILURE;
	}
	auto root = bencode::elem::factory(is);
	root->print(std::cout);

	return EXIT_SUCCESS;
}
