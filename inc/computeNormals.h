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

#include <iostream>
#include <cmath>
#include <vector>
#include "Vertex.h"
#include "Vector3.h"

void computeNormals(const std::vector<Vertex>& inputVertices, std::vector<Vertex>& outputVertices);

#endif