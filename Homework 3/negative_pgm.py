import sys

def readppm(buffer, bufferlen, header, headerlen, rows, cols, chans, file):
    aline = None;
    magic = ['','']
    col = 3
    row = 3
    sat = 3
    channels = 3
    nread = 0
    toread = 0
    fd = 0
    headerlen = 0

    filep = open(fileName, "r")

    #if (headerlen += getline(aline, linelen, filep)) < 0: ## getline wont work
     #   errno, strerror = e.args
      #  print("I/O error [{0}]: {1}".format(errno,strerror))

    header += aline
    #sscanf(aline, "%s", magic)
    #if magic == P6:
    #   channels = 3
    #else
    #   channels = 1

    if magic == "P5":
        channels = 1
    else:
        channels = 1

    header += col
    header += row
    header += aline
    bufferlen = row * col * channels
    toread = bufferlen
    rows = row
    cols = col
    chans = channels

    aline += sat
    header += aline

    print(header)
    print("read %d bytes, buffer=%x, toread=%d\n" % (nread, hex(id(buffer)), toread))

    buffer += nread
    toread -= nread
    print("read %d bytes, buffer=%x, toread=%d\n" % (nread, hex(id(buffer)), toread))
    print("readppm done\n\n")

    filep.close()

def writeppm(buffer, bufferlen, header, headerlen, file):
    nwritten = 0
    towrite = 0

    filep = open(file, "w")

    print("wrote %d bytes, header=%x, towrite=%d\n" % (nwritten, hex(id(header)), towrite))

    header += written
    towrite -= nwritten
    print("wrote %d bytes, header=%x, towrite=%d\n" % (nwritten, hex(id(header)), towrite))

    towrite = 0
    nwritten = 0

    print("wrote %d bytes, header=%x, towrite=%d\n" % (nwritten, hex(id(header)), towrite))

    buffer += nwritten
    towrite -= nwritten
    print("wrote %d bytes, header=%x, towrite=%d\n" % (nwritten, hex(id(header)), towrite))

    filep.close()

def main(argc, argv):
    K = 4.0
    IMAGE_LW = 640
    SAT = 255 
    PSF = [-K/8.0, -K/8.0, -K/8.0, -K/8.0, -K/1.0, -K/8.0, -K/8.0, -K/8.0, -K/8.0, -K/8.0]
    aplha = 1.25
    beta = '25'
    i = 1

    file = input()
    header[0] = '\0'
    readppm(img, bufflen, header, hdrlen, row, col, chan, argv[1])

    while i <= row:
        j = 1
        while j <= col:
            imgBuffer[i][j] = img[((i-1)*col) + (j-1)]
            # newimgBuffer[i][j] = (pix = imgBuffer[i][j]) > if sat is true
            # eval sat, if not eval pix?
            newimgBuffer[i][j] -= SAT

    j = 0
    while j <= col:
        newimgBuffer[0][j] = newimgBuffer[1][j]
        newimgBuffer[row+1][j] = newimgBuffer[row][j]

    i = 0
    while i <= row:
        newimgBuffer[i][0] = newimgBuffer[i][1]
        newimgBuffer[i][col+1] = newimgBuffer[i][col]

    i = 1
    #comment out loop below and *** and uncomment second newimg and first writeppm
    while i <= row:
        j = 1
        while j <= col:
            convolved = 0
            convolved += (PSF[0] * newimgBuffer[i - 1][j - 1])
            convolved += (PSF[1] * newimgBuffer[i - 1][j])
            convolved += (PSF[2] * newimgBuffer[i - 1][j + 1])
            convolved += (PSF[3] * newimgBuffer[i][j - 1])
            convolved += (PSF[4] * newimgBuffer[i][j])
            convolved += (PSF[5] * newimgBuffer[i][j + 1])
            convolved += (PSF[6] * newimgBuffer[i + 1][j - 1])
            convolved += (PSF[7] * newimgBuffer[i + 1][j])
            convolved += (PSF[8] * newimgBuffer[i + 1][j + 1])

        #convolved > and < stmts?
        finalimgBuffer[i][j] = convolved

    j = 1
    while i <= row:
        j = 1
        while j <= col:
            newimg[(i*col)+j] = finalimgBuffer[i][j]
            #newimg[(i*col)+j] = newimgBuffer[i][j]

    #writeppm(newimg, bufflen, header, hdrlen, "negative.pgm")
    writeppm(newimg, bufflen, header, hdrlen, "negaviteconv.pgm")
    
