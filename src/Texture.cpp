/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-16 15:22:19 by jdasilva          #+#    #+#             */
/*   Updated: 2024-07-16 15:22:19 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Texture.h"
#include "../inc/checkGLError.h"

GLuint loadTexture(const char* path)
{
    GLuint textureID;
    CHECK_GL_ERROR(glGenTextures(1, &textureID));

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, textureID));
        CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
        CHECK_GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D));

        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        CHECK_GL_ERROR (glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}