#ifndef ERROR_H
#define ERROR_H
#include <string>

enum ERR_CODE
{
    NONE,
    FILE_NOT_FOUND,
    CORRUPTED_FILE,
    INVALID_EXTENSION,
    UNSUPPORTED_FILE_TYPE,
    BAD_BYTES_PER_PIXEL
};

#define CHECK __attribute__((warn_unused_result))
#define ERR_RET ERR_CODE CHECK

std::string errString(ERR_CODE code);

#endif
