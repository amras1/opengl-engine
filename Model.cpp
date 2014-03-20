#include "Model.h"

ERR_CODE Model::__loadMODEL(const std::string &name)
{
    FILE *file = file_open(name.c_str(), "rb");

    if (!file)
        return FILE_NOT_FOUND;

    unsigned char num_mats, shininess;
    fread(&num_mats, sizeof(unsigned char), 1, file);
    float r, g, b, a;
    unsigned int i, c;
    Material mat;

    for (i = 0; i < num_mats; ++i)
    {
        fread(&r, sizeof(float), 1, file);
        fread(&g, sizeof(float), 1, file);
        fread(&b, sizeof(float), 1, file);
        mat.diff.set(r, g, b, 1.0);
        fread(&r, sizeof(float), 1, file);
        fread(&g, sizeof(float), 1, file);
        fread(&b, sizeof(float), 1, file);
        mat.spec.set(r, g, b, 1.0);
        fread(&r, sizeof(float), 1, file);
        fread(&g, sizeof(float), 1, file);
        fread(&b, sizeof(float), 1, file);
        mat.ambient.set(r, g, b, 1.0);
        fread(&a, sizeof(float), 1, file);
        mat.diff.setAlpha(a);
        mat.spec.setAlpha(a);
        mat.ambient.setAlpha(a);
        fread(&shininess, sizeof(unsigned char), 1, file);
        mat.shininess = shininess;
        materials.push_back(mat);
    }

    unsigned int num_faces;
    fread(&num_faces, sizeof(unsigned int), 1, file);
    float x, y, z;
    unsigned char num_vertices;
    Face face;

    for (i = 0; i < num_faces; ++i)
    {
        fread(&face.mat_index, sizeof(unsigned char), 1, file);
        fread(&num_vertices, sizeof(unsigned char), 1, file);

        for (c = 0; c < num_vertices; ++c)
        {
            fread(&x, sizeof(float), 1, file);
            fread(&y, sizeof(float), 1, file);
            fread(&z, sizeof(float), 1, file);
            face.vertices.push_back(Point3f(x, y, z));
        }

        faces.push_back(face);
    }

    fclose(file);
    return NONE;
}

ERR_CODE Model::load(const std::string &file)
{
    std::string file_extension = extension(file);

    if (strieq(file_extension, "MODEL"))
        return __loadMODEL(file);

    else
        return INVALID_EXTENSION;
}

void Model::render() const
{
    int size = faces.size(), num_points;
    Color3f col;

    for (int i = 0; i < size; ++i)
    {
        col = materials[faces[i].mat_index].diff;
        showCol3f(col);
        num_points = faces[i].vertices.size();

        switch (num_points)
        {
        case 3:
            glBegin(GL_TRIANGLES);
            break;
        case 4:
            glBegin(GL_QUADS);
            break;
        default:
            glBegin(GL_POLYGON);
        }

        for (int c = 0; c < num_points; ++c)
            vertex3f(faces[i].vertices[c]);

        glEnd();
    }
}
