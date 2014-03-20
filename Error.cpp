#include "Error.h"

std::string errString(ERR_CODE code)
{
    std::string err;

    switch (code)
    {
        case FILE_NOT_FOUND:
            err = "file not found";
            break;
        case CORRUPTED_FILE:
            err = "file corrupted";
            break;
        case INVALID_EXTENSION:
            err = "invalid file extension";
            break;
        case UNSUPPORTED_FILE_TYPE:
            err = "file type not yet supported";
            break;
        case BAD_BYTES_PER_PIXEL:
            err = "invalid number of bytes per pixel";
            break;
    }

    return err;
}
