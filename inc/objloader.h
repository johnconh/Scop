/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objloader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-13 18:01:15 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-13 18:01:15 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJLOADER_H
# define OBJLOADER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct Vertex
{
    float x, y, z;

};

struct Face
{
    std::vector<unsigned int> v;
};

struct Material
{
    std::string name = "";
    float Ns;
    float Ni;
    float d;
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    int illum;
};

void loadOBJ(const char * path, std::vector<Vertex> & out_vertices, std::vector<Face> & out_uvs, Material & out_materials);
#endif