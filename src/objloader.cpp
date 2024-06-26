/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objloader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-13 18:07:12 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-13 18:07:12 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/objloader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <iomanip>

void loadMTL(const char * path, Material & out_materials)
{
    std::filesystem::path p(path);
    p.replace_extension(".mtl");

    std::ifstream file(p.string());
    if (!file.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "newmtl")
        {
            std::string name;
            iss >> name;
            out_materials.name = name;
        }
        else if (type == "Ns")
        {
            float Ns;
            iss >> Ns;
            out_materials.Ns = Ns;
        }
        else if (type == "Ni")
        {
            float Ni;
            iss >> Ni;
            out_materials.Ni = Ni;
        }
        else if (type == "d")
        {
            float d;
            iss >> d;
            out_materials.d = d;
        }
        else if (type == "Ka")
        {
            float r, g, b;
            iss >> r >> g >> b;
            out_materials.Ka = glm::vec3(r, g, b);
        }
        else if (type == "Kd")
        {
            float r, g, b;
            iss >> r >> g >> b;
            out_materials.Kd = glm::vec3(r, g, b);

        }
        else if (type == "Ks")
        {   
            float r, g, b;
            iss >> r >> g >> b;
            out_materials.Ks = glm::vec3(r, g, b);
        }
        else if (type == "illum")
        {
            int illum;
            iss >> illum;
            out_materials.illum = illum;
        }
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Material name: " << out_materials.name << std::endl;
    std::cout << "Ns: " << out_materials.Ns << std::endl;
    std::cout << "Ni: " << out_materials.Ni << std::endl;
    std::cout << "d: " << out_materials.d << std::endl;
    std::cout << "Ka: " << out_materials.Ka[0] << ", " << out_materials.Ka[1] << ", " << out_materials.Ka[2] << std::endl;
    std::cout << "Kd: " << out_materials.Kd[0] << ", " << out_materials.Kd[1] << ", " << out_materials.Kd[2] << std::endl;
    std::cout << "Ks: " << out_materials.Ks[0] << ", " << out_materials.Ks[1] << ", " << out_materials.Ks[2] << std::endl;
    std::cout << "illum: " << out_materials.illum << std::endl;
}

void loadOBJ(const char * path, std::vector<Vertex> & out_vertices, std::vector<Face> & out_faces, Material & out_materials)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v")
        {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            out_vertices.push_back(vertex);
        }
        else if (type == "f")
        {
            Face face;
            unsigned int v;
            while(iss >> v)
                face.v.push_back(v);
            out_faces.push_back(face);
        }
        else if (type == "usemtl")
        {
            loadMTL(path, out_materials);
        }
    }


    // std::cout << "Loaded " << out_vertices.size() << " vertices" << std::endl;
    // std::cout << "Loaded " << out_faces.size() << " faces" << std::endl;

    // for (size_t i = 0; i < std::min(size_t(5), out_vertices.size()); i++)
    // {
    //     std::cout << std::fixed << std::setprecision(6);
    //     std::cout << "Vertex " << i << ": " << out_vertices[i].x << " " << out_vertices[i].y << " " << out_vertices[i].z << std::endl;
    // }

    // size_t start = out_vertices.size() > 5 ? out_vertices.size() - 5 : 0;
    // for (size_t i = start; i < out_vertices.size(); i++)
    // {
    //     std::cout << std::fixed << std::setprecision(6);
    //     std::cout << "Vertex " << i << ": " << out_vertices[i].x << " " << out_vertices[i].y << " " << out_vertices[i].z << std::endl;
    // }

    // for (size_t i = 0; i < std::min(size_t(5), out_faces.size()); i++)
    // {
    //     std::cout << "Face " << i << ": ";
    //     for (size_t j = 0; j < out_faces[i].v.size(); j++)
    //         std::cout << out_faces[i].v[j] << " ";
    //     std::cout << std::endl;
    // }
    // start = out_faces.size() > 5 ? out_faces.size() - 5 : 0;
    // for (size_t i = start; i < out_faces.size(); i++)
    // {
    //     std::cout << "Face " << i << ": ";
    //     for (size_t j = 0; j < out_faces[i].v.size(); j++)
    //         std::cout << out_faces[i].v[j] << " ";
    //     std::cout << std::endl;
    // }
}



