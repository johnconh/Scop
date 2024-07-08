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
#include "../inc/Matrix.h"

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
    float Ns = 96.078431f;
    float Ni = 1.0f;
    float d  = 1.0f;
    Vector3 Ka = {1.0f, 1.0f, 1.0f};
    Vector3 Kd = {1.0f, 1.0f, 1.0f};
    Vector3 Ks = {1.0f, 1.0f, 1.0f};
    int illum = 2;
};

void loadOBJ(const char * path, std::vector<Vertex> & out_vertices, std::vector<Face> & out_uvs, Material & out_materials);
#endif