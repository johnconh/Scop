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

#include "../inc/computeNormals.h"

void computeNormals(const std::vector<Vertex>& inputVertices,  std::vector<Vertex>& outputVertices)
{
    outputVertices.clear();
    outputVertices.reserve(inputVertices.size());

    for(const auto& vertex: inputVertices)
    {
        float length = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
        if (length != 0)
        {
            outputVertices.push_back({vertex.x / length, vertex.y / length, vertex.z / length});
        }
        else
            outputVertices.push_back(vertex);
    }

    // for(const auto& vertex: outputVertices)
    // {
    //     std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
    // }
}