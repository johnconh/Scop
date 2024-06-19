/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkGLError.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 17:51:28 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-19 17:51:28 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_GL_ERROR_H
#define CHECK_GL_ERROR_H

#include <GL/glew.h>
#include <iostream>

void checkGLError(const char* statement, const char* file, int line);

#define CHECK_GL_ERROR(statement) do { \
    statement; \
    checkGLError(#statement, __FILE__, __LINE__); \
} while (0)

#endif