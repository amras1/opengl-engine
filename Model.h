#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Error.h"
#include "Point.h"
#include "Color.h"
#include "Image.h"

struct Face
{
    unsigned char mat_index, normal_index;
    std::vector<Point3f> vertices;
};

struct Material
{
    Color4f diff, spec, ambient;
    unsigned char shininess;
};

class Model
{
private:
    std::vector<Face> faces;
    std::vector<Material> materials;
    ERR_RET __loadMODEL(const std::string &);
public:
    ERR_RET loadMODEL(const std::string &file)
    {
        if (strieq(extension(file), "MODEL"))
            return __loadMODEL(file);
        else
            return INVALID_EXTENSION;
    }
    ERR_RET load(const std::string &);
    void render() const;
};

#endif
