#include "../inc/checkGLError.h"

void checkGLError(const char* statement, const char* file, int line) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error " << error << " after " << statement
                  << " at " << file << ":" << line << std::endl;
    }
}
