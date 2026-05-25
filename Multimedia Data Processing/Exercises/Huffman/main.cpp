#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

template <typename T>
std::ostream& raw_write(std::ostream& os, const T& x, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char*>(&x), size);
}

template <typename T>
std::istream& raw_read(std::istream& is, T& x, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char*>(&x), size);
}

class bitwriter {
	uint8_t buffer_;
	size_t n_;
	std::ostream& os_;

	void writebit(uint8_t curbit) {
		buffer_ = (buffer_ << 1) | curbit;
		++n_;
		if (n_ == 8) {
			os_.put(buffer_);
			n_ = 0;
		}
	}

  public:
	bitwriter(std::ostream& os) : buffer_(0), n_(0), os_(os) {}
	~bitwriter() { flush(); }
	void operator()(uint64_t x, int n) {
		for (int i = n - 1; i >= 0; --i) {
			uint8_t curbit = (x >> i) & 1;
			writebit(curbit);
		}
	}
	void flush(uint8_t bit = 0) {
		while (n_ > 0) {
			writebit(bit);
		}
	}
};

class bitreader {
	uint8_t buffer_;
	size_t n_;
	std::istream& is_;

	uint8_t readbit() {
		if (n_ == 0) {
			buffer_ = is_.get();
			n_ = 8;
		}
		--n_;
		return (buffer_ >> n_) & 1;
	}

  public:
	bitreader(std::istream& is) : buffer_(0), n_(0), is_(is) {}
	std::istream& operator()(uint64_t& x, int n) {
		x = 0;
		for (int i = 0; i < n; ++i) {
			x = (x << 1) | readbit();
		}
		return is_;
	}
};

template <typename T>
struct frequencies {
	std::unordered_map<T, uint64_t> freqs_;

	void operator()(const T& val) { ++freqs_[val] }
};

struct node {
	uint8_t sym_ = 0;
	uint32_t count_;
	node* left_;
	node* right_;

	node(uint8_t sym, uint32_t count) : sym_(sym), count_(count) {}

	node(node* left, node* right)
		: count_(left->count_ + right->count_), left_(left), right_(right) {}
};

void create_table(std::unordered_map<uint8_t, std::pair<uint32_t, uint32_t>>& table,
				  node* n,
				  uint32_t code,
				  uint32_t len) {
	if (n->left_ == nullptr) {
		table[n->sym_] = std::make_pair(code, len);
	} else {
		create_table(table, n->left_, code << 1, len + 1);
		create_table(table, n->right_, (code << 1) + 1, len + 1);
	}
}

void compress(const std::string& input_path, const std::string& output_path) {
	std::ifstream is(input_path, std::ios::binary);

	if (!is) {
		throw std::runtime_error("Input file not found");
	}

	is.seekg(0, std::ios::end);
	auto pos = is.tellg();
	is.seekg(0, std::ios::beg);
	std::vector<uint8_t> v(pos);
	raw_read(is, v[0], pos);

	frequencies<uint8_t> f;
	for (const auto& x : v) {
		f(x);
	}

	std::vector<std::unique_ptr<node>> memory;
	std::vector<node*> nodes;
	for (auto& [k, v] : f.freqs_) {
		node* n = new node(k, v);
		memory.emplace_back(n);
		nodes.push_back(n);
	}

	auto pred = [](node* a, node* b) { return a->count_ > b->count_; };

	std::sort(begin(nodes), end(nodes), pred);

	while (nodes.size() > 1) {
		node* n1 = nodes.back();
		nodes.pop_back();
		node* n2 = nodes.back();
		nodes.pop_back();

		node* n = new node(n1, n2);
		memory.emplace_back(n);

		auto it = lower_bound(begin(nodes), end(nodes), n, pred);

		nodes.insert(it, n);
	}
	node* root = nodes.back();
	nodes.pop_back();

	std::unordered_map<uint8_t, std::pair<uint32_t, uint32_t>> table;
	create_table(table, root, 0, 0);

	std::ofstream os(output_path, std::ios::binary);
	if (!os) {
		throw std::runtime_error("Output file not found");
	}
	os << "HUFFMAN1";
	bitwriter bw(os);
	bw(table.size(), 8);
	for (const auto& [sym, x] : table) {
		const auto& [code, len] = x;
		bw(sym, 8);
		bw(len, 5);
		bw(code, len);
	}
	bw(v.size(), 32);
	for (const auto& sym : v) {
		const auto& [code, len] = table[sym];
		bw(code, len);
	}
}

void decompress(const std::string& input_path, const std::string& output_path) {}

int main(int argc, char const* argv[]) {
	try {
		if (argc != 4) {
			throw std::runtime_error("Wrong number of parameters");
		}

		std::vector<std::string> params;
		for (size_t i = 0; i < argc; i++) {
			params.push_back(argv[i]);
		}

		if (params[1] == "c") {
			compress(params[2], params[3]);
		} else if (params[1] == "d") {
			decompress(params[2], params[3]);
		} else {
			throw std::runtime_error(
				"Wrong operational mode (must be either 'c' or 'd')");
		}

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
