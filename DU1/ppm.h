
#ifndef PPM_H
#define PPM_H

// test
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[]; // RGB bajty, celkem 3*xsize*ysize
};

struct ppm *ppm_read(const char *filename);

void ppm_free(struct ppm *p);

#endif
