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

bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line))
    {
        std::istringstream sline(line);
        std::string type;
        sline >> type;

        if(type == "v")
        {
            glm::vec3 vertex;
            sline >> vertex.x >> vertex.y >> vertex.z;
            out_vertices.push_back(vertex);
        }
        else if(type == "f")
        {
            unsigned int vertexIndex[4];
            for(int i = 0; i < 4; i++)
            {
                sline >> vertexIndex[i];
                out_uvs.push_back(out_vertices[vertexIndex[i] - 1]);
            }
        }
        else if (type== "usemtl")
        {
            std::string material;
            sline >> material;
        }
        else if (type == "s")
        {
            std::string smooth;
            sline >> smooth;
            if (smooth == "off")
            {
                std::cout << "Smoothing disabled" << std::endl;
            }
            else
            {
                std::cout << "Smoothing enabled" << std::endl;
            }
        }
    }
    return true;
}