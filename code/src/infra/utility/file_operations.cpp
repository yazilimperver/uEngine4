#include "file_operations.h"
#include <fstream>

std::vector<std::byte> FileOperations::LoadFile(std::string_view filepath) {
    std::ifstream ifs(filepath.data(), std::ios::binary | std::ios::ate);

    if (!ifs) {
        throw std::runtime_error(std::string(filepath.data()) + ": " + std::strerror(errno));
    }

    auto end = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto size = std::size_t(end - ifs.tellg());

    if (size == 0) 
        return {};

    std::vector<std::byte> buffer(size);

    if (!ifs.read((char*)buffer.data(), buffer.size())){
        throw std::runtime_error(std::string(filepath.data()) + ": " + std::strerror(errno));
    }

    return buffer;
}
