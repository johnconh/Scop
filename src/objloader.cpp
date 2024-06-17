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

void loadOBJ(const char * path, std::vector<Vertex> & out_vertices, std::vector<Face> & out_faces)
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



