/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-10 15:45:53 by jdasilva          #+#    #+#             */
/*   Updated: 2024-07-10 15:45:53 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3
{
    float x, y, z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

#endif