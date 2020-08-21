img_to_conv = 'images/combo'

import cv2

def write_data(f, img, x, y):
    b = int(img[y, x, 0] / 8)
    g = int(img[y, x, 1] / 8)
    r = int(img[y, x, 2] / 8)
    c = (r << 11) + (g << 6) + (b << 1)
    data = c.to_bytes(2, byteorder='big')
    f.write(data)
    
def conv_img_part(f, img, n):
    n -= 1
    i = int(n % 3)
    j = int(n / 3)
    for y in range(j * 32, j * 32 + 32):
        for x in range(i * 64, i * 64 + 64):
            write_data(f, img, x, y)

with open('doinmom' + '.bin', 'wb') as f:
    for frame in range(9):
        img_to_conv = f'doinmom-conv\\frame_{frame}_delay-0.04s'
        print (img_to_conv)
        img = cv2.imread(img_to_conv + '.png', cv2.IMREAD_UNCHANGED)

        conv_img_part(f, img, 9)
        conv_img_part(f, img, 6)
        conv_img_part(f, img, 3)
        conv_img_part(f, img, 7)
        conv_img_part(f, img, 8)
        conv_img_part(f, img, 5)
        conv_img_part(f, img, 2)
        conv_img_part(f, img, 1)
        conv_img_part(f, img, 4)