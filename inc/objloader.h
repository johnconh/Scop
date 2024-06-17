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

struct Vertex
{
    float x, y, z;

};

struct Face
{
    std::vector<unsigned int> v;
};


void loadOBJ(const char * path, std::vector<Vertex> & out_vertices, std::vector<Face> & out_uvs);

#endif