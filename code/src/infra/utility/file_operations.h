#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include <vector>
#include <string_view>

class FileOperations {
public:
	static std::vector<std::byte> LoadFile(std::string_view filepath);
};

#endif // !FILE_OPERATIONS

