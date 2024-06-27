/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computeNormals.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-25 15:05:18 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-25 15:05:18 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GLM_ENABLE_EXPERIMENTAL
#include "../inc/computeNormals.h"
#include <iostream>
#include "../inc/glm/gtx/string_cast.hpp"

const float EPSILON = 0.0001f;
glm::vec3 cameraPos(0.0f, 0.0f, -10.0f);

std::vector<glm::vec3> computeNormals(const std::vector<Vertex>& vertices, const std::vector<Face>& faces)
{
    std::vector<glm::vec3> normals(vertices.size(), glm::vec3(0.0f));

    for(size_t faceIndex = 0; faceIndex < faces.size(); faceIndex ++)
    {
        const auto& face = faces[faceIndex];

        for (size_t i = 0; i < face.v.size() - 2; i++)
        {
            glm::vec3 v0 = glm::vec3(vertices[face.v[0]- 1].x, vertices[face.v[0]- 1].y, vertices[face.v[0]- 1].z);
            glm::vec3 v1 = glm::vec3(vertices[face.v[i + 1]- 1].x, vertices[face.v[i + 1]- 1].y, vertices[face.v[i + 1]- 1].z);
            glm::vec3 v2 = glm::vec3(vertices[face.v[i + 2]- 1].x, vertices[face.v[i + 2]- 1].y, vertices[face.v[i + 2]- 1].z);

            glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

            normals[face.v[0] - 1] += normal;
            normals[face.v[i + 1] - 1] += normal;
            normals[face.v[i + 2] - 1] += normal;
        }
    }

    for (size_t i = 0; i < normals.size(); i++)
    {
        if(glm::length(normals[i]) != 0.0f)
        {
            normals[i] = glm::normalize(normals[i]);
        }
        else
            std::cout << "Zero length normal detected: " << glm::to_string(normals[i]) << std::endl;  
    }

    for (const auto& normal : normals)
    {
        // Check for NaN or infinite values
        if (glm::isnan(normal.x) || glm::isnan(normal.y) || glm::isnan(normal.z) ||
            glm::isinf(normal.x) || glm::isinf(normal.y) || glm::isinf(normal.z))
        {
            std::cout << "Invalid normal detected: " << glm::to_string(normal) << std::endl;
        }

        // Check for normals that are not unit length
        float length = glm::length(normal);
        if (fabs(length - 1.0f) > EPSILON)
        {
            std::cout << "Non-unit normal detected: " << glm::to_string(normal) << std::endl;
            std::cout << "Length before normalization: " << length << std::endl;
        }
    }
    return normals;
}