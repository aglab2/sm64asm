from PIL import Image
import os

input_path = "./hints/done"
output_path = "./hints_converted"

# Iterate over all files in the folder
for filename in os.listdir(input_path):
    file_path = os.path.join(input_path, filename)
    # Check if the current path is a file
    if os.path.isfile(file_path):
        # Open the image
        image = Image.open(file_path)

        # Convert the image to RGBA mode
        img_rgba = image.convert("RGBA")

        # Create an empty byte array to store the converted pixels
        pixels = bytearray()

        # Iterate through each pixel and convert to RGBA5551 format
        for pixel in img_rgba.getdata():
            r, g, b, a = pixel
            # Perform conversion to RGBA5551 format using bit manipulation
            rgba5551 = ((r >> 3) << 11) | ((g >> 3) << 6) | ((b >> 3) << 1) | (a >> 7)
            # Append the converted pixel to the byte array
            pixels.append((rgba5551 >> 8) & 0xFF)
            pixels.append(rgba5551 & 0xFF)

        # Save the raw pixel data in a binary file
        with open(os.path.join(output_path, filename + ".bin"), "wb") as file:
            file.write(pixels)
