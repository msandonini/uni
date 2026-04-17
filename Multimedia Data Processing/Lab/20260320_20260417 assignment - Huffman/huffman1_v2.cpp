/*
In v1 we had memory leakes problems since we used new a bunch of times without
calling the delete. A possible solution is to use, like python does, a specific
data structure which manages pointers by keeping a reference counter, counting
the number of references to the pointer so that it's managed semi-automatically.
In C++ this data structure is called shared pointer, and is implemented in
std::shared_ptr<type>.
In order to create a shared pointer we can do it in 2 ways:

std::shared_ptr<int> p;
auto q = std::make_shared<int>();

A cool thing about these pointers is the fact that they have the concept of
being empty, so there's no problem of trying to write in an unallocated
memory address.
The problem with shared pointers is that they have a cost, since each pointer is
a data structure with its reference counter, so each shared_ptr takes about
double the size of a single pointer.

Another solution to the problem is using unique pointers
(std::unique_ptr<type>), which makes it so that no other pointer can be
referenced to the same address which the unique pointer is referenced to.

auto q = std::make_unique<int>();

By default, each unique pointer has ownership on its referenced memory address.
In order to change the owner of the pointer we have a few functions:

int *tmp = q.release();		// Here q becomes empty, and p is now the owner of
p.reset(tmp);				// the pointer

This is an ugly way of moving a pointer, but fortunately we can use move:

p = move(q);

Basically, unique pointers can be used as regular pointers but in a safer way,
since they are automatically deleted.
*/

#include <bit>
#include <fstream>
#include <map>
#include <memory>
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

	// -- STEP 1: MEMORY POINTER --
	std::vector<std::unique_ptr<node>> memory;
	// By adding this array we give to the unique pointers inside
	// the array the ownership of the node pointers, so we can
	// still use them but in a safer way since we don't need to
	// delete them
	std::vector<node*> nodes;
	for (const auto& [k, v] : f.count_) {
		node* n = new node(k, v);
		memory.emplace_back(n);	 // Emplace back is like the
								 // push_back but which creates an object
								 // before adding it.
								 // This is useful since the memory array
								 // expects a unique_ptr<node> object and
								 // not a node object
		nodes.push_back(n);
	}
	// -- END 1 --

	auto pred = [](node* a, node* b) { return a->count_ > b->count_; };
	std::sort(begin(nodes), end(nodes), pred);

	while (nodes.size() > 1) {
		node* n1 = nodes.back();
		nodes.pop_back();
		node* n2 = nodes.back();
		nodes.pop_back();

		node* n = new node(n1, n2);

		auto it = std::lower_bound(begin(nodes), end(nodes), n, pred);

		nodes.insert(it, n);
	}

	node* root = nodes.back();
	nodes.pop_back();

	std::unordered_map<uint8_t, std::pair<uint32_t, uint32_t>> table;

	create_table(table, root, 0, 0);

	// Output

	std::ofstream os(fileout, std::ios::binary);
	if (!os) {
		return 1;
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
	for (const auto& x : v) {
		const auto& e = table[x];
		bw(e.first, e.second);
	}

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
