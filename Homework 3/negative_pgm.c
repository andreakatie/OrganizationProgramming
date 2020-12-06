//2-D array version of brighten_pgm.c

//code to be converted to pgm compatability

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void readppm(unsigned char *buffer, int *bufferlen,
	     char *header, int *headerlen,
	     unsigned *rows, unsigned *cols, unsigned *chans, char *file)
{
    char *aline = NULL;
    size_t linelen;
    FILE *filep;
    char magic[2];
    unsigned col, row, sat, channels = 3;
    int nread = 0, toread = 0, fd = 0;
    *headerlen = 0;

    filep = fopen(file, "r");

    // read and validate header
    if ((*headerlen += getline(&aline, &linelen, filep)) < 0) {
	perror("getline");
	exit(-1);
    }
    strcat(header, aline);
    sscanf(aline, "%s", magic);
    //if(strncmp(magic, "P6", 2) == 0) channels=3; else channels=1;
    if (strncmp(magic, "P5", 2) == 0)
	channels = 1;
    else
	channels = 1;

    // ignore comment line or print for debug
    if ((*headerlen += getline(&aline, &linelen, filep)) < 0) {
	perror("getline");
	exit(-1);
    }
    strcat(header, aline);

    if ((*headerlen += getline(&aline, &linelen, filep)) < 0) {
	perror("getline");
	exit(-1);
    }
    sscanf(aline, "%u %u", &col, &row);
    strcat(header, aline);
    *bufferlen = row * col * channels;
    toread = *bufferlen;
    *rows = row, *cols = col, *chans = channels;

    if ((*headerlen += getline(&aline, &linelen, filep)) < 0) {
	perror("getline");
	exit(-1);
    }
    sscanf(aline, "%u", &sat);
    strcat(header, aline);

    printf("%s", header);

    printf("read %d bytes, buffer=%p, toread=%d\n", nread, buffer, toread);

    if ((nread = fread(buffer, 1, (col * row * channels), filep)) == 0) {
	if (feof(filep)) {
	    printf("completed readppm\n");
	} else {
	    perror("readppm");
	    exit(-1);
	}
    }

    buffer += nread;
    toread = toread - nread;
    printf("read %d bytes, buffer=%p, toread=%d\n", nread, buffer, toread);

    printf("readppm done\n\n");
    close(filep);
}


void writeppm(unsigned char *buffer, int bufferlen,
	      char *header, int headerlen, char *file)
{
    FILE *filep;
    int nwritten = 0, towrite = 0;

    filep = fopen(file, "w");

    printf("wrote %d bytes, header=%p, towrite=%d\n", nwritten, header,
	   towrite);

    if ((nwritten = fwrite(header, 1, headerlen, filep)) == 0) {
	if (feof(filep)) {
	    printf("completed writeppm header\n");
	} else {
	    perror("writeppm header");
	    exit(-1);
	}
    }

    header += nwritten;
    towrite = towrite - nwritten;
    printf("wrote %d bytes, header=%p, towrite=%d\n", nwritten, header,
	   towrite);

    towrite = 0;
    nwritten = 0;

    printf("wrote %d bytes, buffer=%p, towrite=%d\n", nwritten, buffer,
	   towrite);

    if ((nwritten = fwrite(buffer, 1, bufferlen, filep)) == 0) {
	if (feof(filep)) {
	    printf("completed writeppm\n");
	}			//break; }
	else {
	    perror("writeppm");
	    exit(-1);
	}
    }

    buffer += nwritten;
    towrite = towrite - nwritten;
    printf("wrote %d bytes, buffer=%p, towrite=%d\n", nwritten, buffer,
	   towrite);

    close(filep);
}


#define PIXIDX ((i*col*chan)+(j*chan)+k)
#define SAT (255)
#define K 4.0
#define IMAGE_LW 640

//Standard PSF used
double PSF[9] =
    { -K / 8.0, -K / 8.0, -K / 8.0, -K / 8.0, K + 1.0, -K / 8.0, -K / 8.0,
-K / 8.0, -K / 8.0 };

void main(int argc, char *argv[])
{
    char header[512];
    //The array size below can be changed as needed; if repeating pixels occur in the image, the array is too small
    unsigned char img[640 * 480], newimg[640 * 480];	//img[640*480], newimg[640*480];
    unsigned char imgBuffer[IMAGE_LW][IMAGE_LW],
	newimgBuffer[IMAGE_LW][IMAGE_LW],
	finalimgBuffer[IMAGE_LW][IMAGE_LW];
    int bufflen, hdrlen;
    unsigned row = 0, col = 0, chan = 0, pix;
    int i, j, k;
    double alpha = 1.25;
    unsigned char beta = 25;

    double convolved = 0;

    header[0] = '\0';
    readppm(img, &bufflen, header, &hdrlen, &row, &col, &chan, argv[1]);

    //Used in main to safely read from the buffer; otherwise a segmentation fault can occur
    for (i = 1; i <= row; i++) {
	for (j = 1; j <= col; j++) {
	    imgBuffer[i][j] = img[((i - 1) * col) + (j - 1)];
	    newimgBuffer[i][j] = (pix =
				  (unsigned) (imgBuffer[i][j])) >
		SAT ? SAT : pix;
	    newimgBuffer[i][j] -= SAT;
	}
    }

    for (j = 0; j <= col; j++) {
	newimgBuffer[0][j] = newimgBuffer[1][j];
	newimgBuffer[row + 1][j] = newimgBuffer[row][j];
    }

    for (i = 0; i <= row; i++) {
	newimgBuffer[i][0] = newimgBuffer[i][1];
	newimgBuffer[i][col + 1] = newimgBuffer[i][col];
    }
    //Comment out the for loop below this line along with line 182 (uncomment out lines 183 and 187 as well) for only a graymap image
    for (i = 1; i <= row; i++) {
	for (j = 1; j <= col; j++) {
	    convolved = 0;
	    convolved += (PSF[0] * (double) newimgBuffer[i - 1][j - 1]);
	    convolved += (PSF[1] * (double) newimgBuffer[i - 1][j]);
	    convolved += (PSF[2] * (double) newimgBuffer[i - 1][j + 1]);
	    convolved += (PSF[3] * (double) newimgBuffer[i][j - 1]);
	    convolved += (PSF[4] * (double) newimgBuffer[i][j]);
	    convolved += (PSF[5] * (double) newimgBuffer[i][j + 1]);
	    convolved += (PSF[6] * (double) newimgBuffer[i + 1][j - 1]);
	    convolved += (PSF[7] * (double) newimgBuffer[i + 1][j]);
	    convolved += (PSF[8] * (double) newimgBuffer[i + 1][j + 1]);

	    convolved < 0.0 ? 0.0 : convolved;
	    convolved > 255.0 ? 255.0 : convolved;
	    finalimgBuffer[i][j] = (unsigned) convolved;
	}
    }

    for (i = 1; i <= row; i++) {
	for (j = 1; j <= col; j++) {
	    newimg[(i * col) + j] = finalimgBuffer[i][j];
	    //newimg[(i * col) + j] = newimgBuffer[i][j];
	}
    }

    //writeppm(newimg, bufflen, header, hdrlen, "negative.pgm");
    writeppm(newimg, bufflen, header, hdrlen, "negativeconv.pgm");
}
