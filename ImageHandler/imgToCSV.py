## Thomas Parker
## Converts topo images to csv file with pixel intensity values (range 0-255)

import numpy as np
import csv
from PIL import Image

pathToImage = "../Images/theLongDark.jpg"
csvFileName = 'theLongDark.csv'

pic = (Image.open(pathToImage)).convert("L") # converted to greyscale
file = open(csvFileName, 'w')
dataWrite = csv.writer(file, lineterminator = '\n')
data = np.array(pic.getdata()).reshape(pic.size[0], pic.size[1], 1)

for row in data:
    tempRow = []
    for val in row:
        tempRow.append(str(int((val))))
    dataWrite.writerow(tempRow)

file.close()