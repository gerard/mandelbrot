#include <stdio.h>
#include <complex.h>
#include <assert.h>

typedef enum {
    RGB_RED = 0,
    RGB_GREEN,
    RGB_BLUE,
} rgb_t;

const int size_x = 640;
const int size_y = 480;
const float orig_x = 640*2/3;
const float orig_y = 480*1/2;

static int mand_esc_time(int x, int y)
{
    const int bailout = 256;
    int i;

    complex c = ((x - orig_x)/(size_x/3)) + ((orig_y - y)/(size_y/2))*I;
    complex z = 0;

    for(i = 0; i < bailout; i++) {
        z = z*z + c;
        if(creal(z) > 2 || cimag(z) > 2) break;
    }
    
    /* Return zero if think the point is in the set */
    return i == bailout ? 0 : i;
}

int main(int argc, char *argv[])
{
    unsigned char pixel_black[3] = { 0, 0, 0 };
    unsigned char pixel_white[3] = { 255, 255, 255 };
    unsigned int esc_time; 
    char *filename = argc > 1 ? argv[1] : "out.ppm";
    FILE *f = fopen(filename, "w");
    int i, j;

    fprintf(f, "P6\n");
    fprintf(f, "#The comment string\n");
    fprintf(f, "%d %d\n", size_x, size_y);
    fprintf(f, "%d\n", 255);
    for(i = 0; i < size_y; i++) {
        for(j = 0; j < size_x; j++) {
            esc_time = mand_esc_time(j, i);
            if(esc_time) {
                unsigned char pixel[3] = { esc_time, 256-esc_time, 255 };
                fwrite(pixel, sizeof(pixel_white), 1, f);
            } else {
                fwrite(pixel_black, sizeof(pixel_black), 1, f);
            }
        }
    }
    fclose(f);

    return 0;
}
