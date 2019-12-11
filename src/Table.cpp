#include "Table.hpp"

Table::Table(float scalex, float scaley, float scalez)
{
    shaderProgramId = shaderProgramIdColored;
    glUseProgram(shaderProgramId);
    m = load_obj_file("../data/Minimalist Dining Table.obj");

    //m = load_obj_file("../data/stegosaurus.obj");

    rotationCenter = vec3();
    rotation = mat4();
    translation = vec3();

    mat4 transform = mat4(scalex, 0.0f, 0.0f, 0.0f,
                          0.0f, scaley, 0.0f, 0.0f,
                          0.0f, 0.0f, scalez, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m, transform);

    rotationCenter = vec3(0.0f, -0.5f, -2.0f);

    update_normals(&m);
    fill_color(&m, vec3(1.0f, 1.0f, 1.0f));
    glGenBuffers(1, &vbo);
    PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER, m.vertex.size() * sizeof(vertex_opengl), &m.vertex[0], GL_STATIC_DRAW);
    PRINT_OPENGL_ERROR();

    //attribution d'un autre buffer de donnees
    glGenBuffers(1, &vboi);
    PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);
    PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.connectivity.size() * sizeof(triangle_index), &m.connectivity[0], GL_STATIC_DRAW);
    PRINT_OPENGL_ERROR();

    // Nombre de triangles de l'objet 1
    nbTriangles = m.connectivity.size();

    vec3 min = m.vertex[0].position;
    vec3 max = m.vertex[0].position;
    for (unsigned int idx = 0, N = m.vertex.size(); idx < N; ++idx)
    {
        //x
        if (m.vertex[idx].position.x < min.x)
            min.x = m.vertex[idx].position.x;
        else if (m.vertex[idx].position.x > max.x)
            max.x = m.vertex[idx].position.x;

        //y
        if (m.vertex[idx].position.y < min.y)
            min.y = m.vertex[idx].position.y;
        else if (m.vertex[idx].position.y > max.y)
            max.y = m.vertex[idx].position.y;

        //z
        if (m.vertex[idx].position.z < min.z)
            min.z = m.vertex[idx].position.z;
        else if (m.vertex[idx].position.z > max.z)
            max.z = m.vertex[idx].position.z;
    }
    aabb = AABB(min, max);
}