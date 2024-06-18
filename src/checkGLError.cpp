/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkGLError.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-18 16:54:05 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-18 16:54:05 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/checkGLError.h"

void checkGLError(const char* statement, const char* file, int line) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error " << error << " after " << statement
                  << " at " << file << ":" << line << std::endl;
    }
}