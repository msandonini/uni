#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
using mat = std::vector<std::vector<T>>;

struct y4m_header {
    int w, h;
    std::string c;
    char i;
    int fn, fd;
    int an, ad;
    std::string x;
};

/**
 * The program should only support C420jpeg encoding with progressive
 * interlacing (i.e. no interlacing) and ignore frame rate, aspect ratio or
 * other parameters. In case of an error it must end with false. If the loading
 * of the YUV4MPEG2 stream is successful the function must terminate by
 * returning true.
 */
bool y4m_extract_gray(const std::string& filename,
                      std::vector<mat<uint8_t>>& frames) {
    std::ifstream is(filename, std::ios::binary);
    if (!is) {
        return false;
    }

    std::string line;
    std::getline(is, line);

    std::stringstream ss(line);

    std::string token;
    ss >> token;
    if (token != "YUV4MPEG2") {
        return false;
    }

    y4m_header header;
    while (ss >> token) {
        switch (token.c_str()[0]) {
            case 'H':
                header.h = std::stoi(token.substr(1));
                break;
            case 'W':
                header.w = std::stoi(token.substr(1));
                break;
            case 'C':
                header.c = token.substr(1);
                break;
            case 'I':
                header.i = token.c_str()[1];
                break;
            case 'F':
                int del = token.find(':');
                header.fn = std::stoi(token.substr(1, del));
                header.fd = std::stoi(token.substr(del));
                break;
            case 'A':
                int del = token.find(':');
                header.an = std::stoi(token.substr(1, del));
                header.ad = std::stoi(token.substr(del));
                break;
            case 'X':
                header.x = token.substr(1);
                break;
            default:
                return false;
                break;
        }
    }

    if (header.c != "C420jpeg") {
        return false;
    }
    if (header.i != 'p') {
        return false;
    }

    return true;
}

int main(int argc, char const* argv[]) {
    return 0;
}
