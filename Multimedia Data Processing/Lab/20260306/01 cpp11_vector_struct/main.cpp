#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

static int cmp_int32(const void* a, const void* b) {
    int32_t ia = *(const int32_t*)a;
    int32_t ib = *(const int32_t*)b;
    return (ia > ib) - (ia < ib);
}

struct vector {
    int32_t* data_;
    size_t n_;
    size_t cap_;

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
        data_ = new int32_t[n];
    }

    // Copy constructor
    vector(const vector& other) {
        printf("vector(const vector& other)\n");
        n_ = other.n_;
        cap_ = other.cap_;
        data_ = new int32_t[n_];
        for (size_t i = 0; i < n_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    // Move constructor
    vector(vector&& other) {
        // La sintassi vector&& è chiamata r-value reference, ed è usata per
        // spostare la proprietà di un valore temporaneo che verrebbe distrutto
        // ad un altro oggetto (ottimizzando la fine di funzioni che devono
        // creare un oggetto dal momento che non devono fare una copia di tutti
        // i dati)

        printf("vector(vector&& other)\n");
        n_ = other.n_;
        cap_ = other.cap_;
        data_ = other.data_;
        other.data_ = nullptr;
    }

    // Rule of 4: costruttore, costruttore di copia, assegnamento, e distruttore
    // sono necessari. Se non scritti li scrive automaticamente il compilatore
    ~vector() { delete[] data_; }

    void push_back(int32_t val) {
        if (n_ == cap_) {
            size_t new_cap = (cap_ == 0) ? 4 : cap_ * 2;
            int32_t* tmp = new int32_t[new_cap];
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

    void sort() { qsort(data_, n_, sizeof(int32_t), cmp_int32); }

    size_t size() const { return n_; }

    int at(size_t pos) const {
        assert(pos < n_);
        return data_[pos];
    }

    // Assignment operator
    vector& operator=(const vector& rhs) {
        if (this == &rhs) {
            return *this;
        }
        n_ = rhs.n_;
        cap_ = rhs.cap_;
        delete[] data_;
        data_ = new int32_t[n_];
        for (size_t i = 0; i < n_; ++i) {
            data_[i] = rhs.data_[i];
        }
        return *this;
    }

    /*
    // Questo non funziona perché scritto in questo modo l'operatore [] ritorna
    // un valore int e non una reference ad un valore int

    int operator[](size_t pos) const
    {
        return data_[pos];
    }
    */

    /*
    // Il doppio overloading di seguito funziona perché è come scrivere 2
    // funzioni distinte, una per `vector` e l'altra per `const vector`

    const int& operator[](const vector *this, size_t pos)
    int& operator[](vector *this, size_t pos)
    */
    const int& operator[](size_t pos) const { return data_[pos]; }
    int& operator[](size_t pos) { return data_[pos]; }
};

// Questo prototipo funziona senza problemi, però copia il vettore v ogni volta
// che viene chiamato, che può causare problemi in caso di vettori molto grandi
// bool write_to_file(const char *fname, vector v) {
bool write_to_file(const char* fname, const vector& v) {
    FILE* fout = fopen(fname, "w");
    if (!fout) {
        return 1;
    }
    for (size_t i = 0; i < v.size(); i++) {
        fprintf(fout, "%d\n", v[i]);
    }
    fclose(fout);
}

vector read_from_file(const char* in_name) {
    /*
    // Problema con questo ritorno: ritornare un oggetto ritorna una copia di
    // quell'oggetto, e si appoggia sulla RVO (Return Value Optimization)
    // implementata nel compilatore
    FILE* fin = fopen(in_name, "r");
    if (!fin) {
        return vector();
    }
    */

    vector arr;

    FILE* fin = fopen(in_name, "r");
    if (!fin) {
        // Ritornare questo invece che vector() si appoggia sulla NRVO (Named
        // Return Value Optimization)
        return arr;
    }

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
        arr.push_back(val);
    }

    fclose(fin);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }

    const char* in_name = argv[1];
    const char* out_name = argv[2];

    vector arr = read_from_file(in_name);

    vector x(3);  // vector x(arr);

    for (size_t i = 0; i < 3; ++i) {
        x[i] = arr[i];
    }

    arr.sort();

    write_to_file(out_name, arr);

    return 0;
}