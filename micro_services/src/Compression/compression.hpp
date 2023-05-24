#ifndef COMPRESSION_DEFINE
#define COMPRESSION_DEFINE

#include <iostream>
#include <stdexcept>

#include <zipper/unzipper.h>
#include <zipper/zipper.h>

#include "../settings/settigns.hpp"

namespace compression_alg {
    bool compress(const char* name_service, const std::string& path_from,
        const std::string& path_to, const char* password);
    bool decompress(const char* name_service, const std::string& path_from,
        const std::string& path_to, const char* password);
}

#endif