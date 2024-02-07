#include "ppm.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (8000 * 8000 * 3)

struct ppm *ppm_read(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        error_exit("ppm_read: soubor se neotevrel!\n");
    }

    char format[3] = {0};
    int xsize, ysize, rgb;

    // Reads format of file
    if (fscanf(file, "%2c\n", format) != 1) {
        warning("ppm_read: nelze precist data!\n");
        fclose(file);
        return NULL;
    };

    // Check format
    if (strcmp("P6", format) != 0) {
        warning("ppm_read: spatny format1!\n");
        fclose(file);
        return NULL;
    }

    // Load size, color
    if (fscanf(file, "%d %d\n%d\n", &xsize, &ysize, &rgb) != 3) {
        warning("ppm_read: spatny format2!\n");
        fclose(file);
        return NULL;
    }

    size_t image_size = 3 * xsize * ysize;

    if (MAX < image_size) {
        warning("ppm_read: prekrocena velikost\n");
        fclose(file);
        return NULL;
    }

    // Load into memory
    struct ppm *image = malloc(sizeof(struct ppm) + image_size);
    if (image == NULL) {
        warning("ppm_read: nedostatek pameti!\n");
        fclose(file);
        return NULL;
    }

    image->xsize = xsize;
    image->ysize = ysize;

    while (fread(image->data, image_size, 1, file) != 1) {
        warning("ppm_read: chyba cteni obrazku!\n");
        fclose(file);
        ppm_free(image);
        return NULL;
    }

    fclose(file);
    return image;
}

void ppm_free(struct ppm *p) {
    free(p);
    return;
}
