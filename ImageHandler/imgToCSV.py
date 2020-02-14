## Thomas Parker
## Converts topo images to csv file with pixel intensity values (range 0-255)

import numpy as np
import csv
from PIL import Image

pic = (Image.open("../Images/everest.jpg")).convert("L") # converted to greyscale
file = open('everest.csv', 'w')
dataWrite = csv.writer(file, lineterminator = '\n')
data = np.array(pic.getdata()).reshape(pic.size[0], pic.size[1], 1)

for row in data:
    tempRow = []
    for val in row:
        tempRow.append(str(int((val))))
    dataWrite.writerow(tempRow)

file.close()