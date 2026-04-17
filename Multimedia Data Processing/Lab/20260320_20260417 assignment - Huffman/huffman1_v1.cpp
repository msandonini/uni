#include <bit>
#include <fstream>
#include <map>
#include <print>
#include <string>
#include <unordered_map>
#include <vector>

// -- USAGE --

void print_usage() {
	std::println("Usage: ");
	std::println("huffman1 [c|d] <filein> <fileout>");
}

// -- RAW IO --

template <typename T>
std::ostream& raw_write(std::ostream& os, const T& x, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char*>(&x), size);
}

template <typename T>
std::istream& raw_read(std::istream& is, T& x, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char*>(&x), size);
}

// -- IO HELPERS --

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

// -- FREQUENCIES --

template <typename T>
struct frequencies {
	std::map<T, uint32_t> count_;

	void operator()(const T& val) { ++count_[val]; }
};

struct node {
	uint8_t sym_ = 0;
	uint32_t count_;
	node* left_ = nullptr;
	node* right_ = nullptr;

	node(uint8_t sym, uint32_t count) : sym_(sym), count_(count) {}

	node(node* left, node* right)
		: count_(left->count_ + right->count_), left_(left), right_(right) {}
};

// -- FUNCTIONS --

int compress(std::string filein, std::string fileout) {
	std::ifstream is(filein, std::ios::binary);

	if (!is) {
		std::println("Error: unable to open file \"{}\"", filein);
		return 1;
	}

	is.seekg(0, std::ios::end);
	auto pos = is.tellg();
	is.seekg(0, std::ios::beg);
	std::vector<uint8_t> v(pos);
	raw_read(is, v[0], pos);

	// Count frequencies

	frequencies<uint8_t> f;
	for (const auto& x : v) {
		f(x);
	}

	// Create Huffman tree

	std::vector<node*> nodes;
	// --- STEP 3. BEAUTIFY ---
	// for (const auto& x : f.count_) {
	for (const auto& [k, v] : f.count_) {
		// This syntax is called tuple expansion
		/*
		const auto& k = x.first;
		const auto& v = x.second;
		*/

		node* n = new node(k, v);
		nodes.push_back(n);
	}
	// --- END 3 ---

	auto pred = [](node* a, node* b) { return a->count_ > b->count_; };
	std::sort(begin(nodes), end(nodes), pred);

	// --- STEP 4. IMPROVEMENTS ---
	// The insertion works but could be made better.
	// Since to find the position in which to insert the data it goes through
	// all the array, this could be improved by using an ordered list with
	// binary search
	while (nodes.size() > 1) {
		node* n1 = nodes.back();
		nodes.pop_back();
		node* n2 = nodes.back();
		nodes.pop_back();

		node* n = new node(n1, n2);

		/*
		auto it = nodes.begin();
		for (size_t i = 0; i < nodes.size(); ++i) {
			if (nodes[i]->count_ <= n->count_) {
				break;
			}
			++it;
		}
		*/

		// pred is the sorting lambda
		auto it = std::lower_bound(begin(nodes), end(nodes), n, pred);

		nodes.insert(it, n);
	}
	// --- END 4 ---

	// --- STEP 1. CREATION OF HUFFMAN CODES ---

	// We need
	node* root = nodes.back();
	nodes.pop_back();

	// The general idea is to make something that makes it easy to find symbols,
	// so we use a map
	std::unordered_map<uint8_t, std::pair<uint32_t, uint32_t>> table;

	create_table(table, root, 0, 0);

	// --- END 1 ---
	// --- STEP 2. ENCODE OUTPUT STREAM ---

	std::ofstream os(fileout, std::ios::binary);
	if (!os) {
		return 1;
	}

	// Writing the Huffman1 magic code
	os << "HUFFMAN1";  // This works even if we specified std::ios::binary in
					   // output since the binary writing only affects the new
					   // lines (only inserts one newline character instead of
					   // the ususal 2)

	bitwriter bw(os);

	// Writing the table size
	bw(table.size(), 8);

	// Writing the table
	/*
	for (const auto& x : table) {
		// The following works because auto on a table returns a std::pair
		bw(x.first, 8);
		bw(x.second.second, 5);				 // length
		bw(x.second.first, x.second.first);	 // code
	}
	*/
	// We don't want it written like this because it's ugly (see point 3 to
	// understand the syntax)
	for (const auto& [sym, x] : table) {
		const auto& [code, len] = x;
		bw(sym, 8);
		bw(len, 5);
		bw(code, len);
	}

	bw(v.size(), 32);  // This is written as Big-ended since our BW logic
					   // automatically writes in big endian logic

	// Standard binary output to write the Huffman codes
	for (const auto& x : v) {
		const auto& e = table[x];
		bw(e.first, e.second);
	}

	// --- END 2 ---

	return 0;
}

void create_table(
	std::unordered_map<uint8_t, std::pair<uint32_t, uint32_t>>& table, node* n,
	uint32_t code, uint32_t len) {
	if (n->left_ == nullptr) {
		// In this case also the right is nullptr, since we can not have an
		// unbalanced map

		table[n->sym_] = std::make_pair(code, len);
	} else {
		// In this case we need to navigate the tree

		create_table(table, n->left_, code << 1, len + 1);
		create_table(table, n->right_, (code << 1) + 1, len + 1);
	}
}

int decompress(std::string filein, std::string fileout) {
	std::ifstream is(filein, std::ios::binary);

	if (!is) {
		std::println("Error: unable to open file \"{}\"", filein);
		return 1;
	}

	return 0;
}

// -- MAIN --

int main(int argc, char const* argv[]) {
	if (argc != 4) {
		std::println("Error: wrong number of arguments.");
		print_usage();
		return 1;
	}

	std::string mode = argv[1];

	if (mode == "c") {
		return compress(argv[2], argv[3]);
	} else if (mode == "d") {
		return decompress(argv[2], argv[3]);
	} else {
		std::println("Error: provided invalid mode.");
		print_usage();
		return 1;
	}

	return 0;
}
