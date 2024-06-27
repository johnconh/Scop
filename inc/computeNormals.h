/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computeNormals.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-25 15:01:23 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-25 15:01:23 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTENORMALS_H
#define COMPUTENORMALS_H

#include <vector>
#include <glm/glm.hpp>
#include <objloader.h>

std::vector<glm::vec3> computeNormals(const std::vector<Vertex>& vertices, const std::vector<Face>& faces);

#endif