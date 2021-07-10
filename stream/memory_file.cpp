#include "memory_file.hpp"

using namespace nt::stream;

MemoryFile::MemoryFile(const std::string& contents) :
      file(nullptr),
      buffer(nullptr)
{
    _size     = contents.length() + 1;
    buffer    = new char[size];
    _filename = "__in_memory_file__";
    _type     = "plain/text";

    contents.copy(buffer, size - 1);

    file = fmemopen(buffer, size, "r");

    if (file == nullptr) {
        switch (errno) {
        default:
            throw nt::error::runtime();
        }
    }
}

MemoryFile::~MemoryFile() noexcept
{
    if (file != nullptr) {
        fclose(file);
    }

    if (buffer != nullptr) {
        delete[] buffer;
    }
}
