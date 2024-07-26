/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-26 14:48:10 by jdasilva          #+#    #+#             */
/*   Updated: 2024-07-26 14:48:10 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
    float x, y;

    Vector2(float x, float y) : x(x), y(y) {}

    Vector2(): x(0), y(0) {}
};

#endif