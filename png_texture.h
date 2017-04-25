#ifndef _PNG_TEXTURE
#define _PNG_TEXTURE

#include <GL/glut.h>
#include <png.h>
#include "constants.h"


class TextureLoader {
public:
    // Constructor
    TextureLoader();
    // Methods
    static void loadTextures();
private:
    static void png_texture_load(const char * file_name, Texture texture, int * width = 0, int * height = 0);
};
#endif // ifndef _PNG_TEXTURE
