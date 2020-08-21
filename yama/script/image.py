img_to_conv = 'images/combo'

import cv2

def write_data(f, img, x, y):
    b = int(img[y, x, 0] / 8)
    g = int(img[y, x, 1] / 8)
    r = int(img[y, x, 2] / 8)
    c = (r << 11) + (g << 6) + (b << 1) + 1
    data = c.to_bytes(2, byteorder='big')
    f.write(data)
    
def conv_img_part(f, img, n):
    n -= 1
    i = int(n / 3)
    j = int(n % 3)
    for y in range(j * 32, j * 32 + 32):
        for x in range(i * 64, i * 64 + 64):
            write_data(f, img, x, y)

def conv_img(typ, f):
    img = cv2.imread(f'{typ}\\1.png', cv2.IMREAD_UNCHANGED)
    conv_img_part(f, img, 5)
    conv_img_part(f, img, 1)
    conv_img_part(f, img, 8)
    conv_img_part(f, img, 7)
    conv_img_part(f, img, 2)
    conv_img_part(f, img, 6)
    conv_img_part(f, img, 3)
    conv_img_part(f, img, 9)
    conv_img_part(f, img, 4)

    img = cv2.imread(f'{typ}\\2.png', cv2.IMREAD_UNCHANGED)
    conv_img_part(f, img, 5)
    conv_img_part(f, img, 1)
    conv_img_part(f, img, 8)
    conv_img_part(f, img, 7)
    conv_img_part(f, img, 2)
    conv_img_part(f, img, 6)
    conv_img_part(f, img, 3)
    conv_img_part(f, img, 9)
    conv_img_part(f, img, 4)
   
    img = cv2.imread(f'{typ}\\3.png', cv2.IMREAD_UNCHANGED)
    conv_img_part(f, img, 8)  # 12840
    conv_img_part(f, img, 9)  # 13840
    conv_img_part(f, img, 7)  # 14840
    conv_img_part(f, img, 12) # 15840
    conv_img_part(f, img, 10) # 16840
    conv_img_part(f, img, 11) # 17840
    conv_img_part(f, img, 13) # 18840
    conv_img_part(f, img, 15) # 19840
    conv_img_part(f, img, 14) # 1a840
    conv_img_part(f, img, 6)  # 1b840
    conv_img_part(f, img, 5)  # 1c840
    conv_img_part(f, img, 4)  # 1d840
    conv_img_part(f, img, 2)  # 1e840
    conv_img_part(f, img, 1)  # 2f840
    conv_img_part(f, img, 3)  # 20840

# 160BE40
with open('credits.bin', 'wb') as f:
    types = ['d', 'g0', 'g1', 'g2', 'g3', 'g4', 'g5', 'g6', 'g7', 'g8', 'g9', 'p', 'p0', 'p1', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 'proofreading', 'm0', 'm1', 'm2', 's0', 's1', 's2', 's3', 's4', 'over']
    for typ in types:
        conv_img(typ, f)

#with open('init.bin', 'wb') as f:
#    conv_img('init', f)