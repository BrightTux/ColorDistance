# ColorDistance

Humans are able to identify basic colors easily, we can easily differentiate between red and blue, or green and yellow. But, how would a computer be able to do so? 

The codes in this repository helps users to measure the distance (or identify colors) based on a sample color-image.
In order to simplify the process, the source code used will loop through 960 different sample color-image, and measure the distance between the "ground truth" value and the sample color-image.


# Installation

1. Install [OpenCV](https://opencv.org/) on your machine
(Windows) Kindly refer to the following documentation provided for the installation process [here](https://docs.opencv.org/2.4/doc/tutorials/introduction/windows_install/windows_install.html)
 
2. Launch IDE of choice and run code


# Usage

1. The program will generate a file "colorIndexes.txt" and a folder called "960HSVimages"
2. If you would like to view the color-measure distance in the browser, rename the `colorIndexes.txt` to `colorIndexes.html`
3. The `colorindexes_withmacro.xlsm` file is used to generate the `colorIndexes_wTable.pdf` file. This excel sheet highlights all the highest value for each row to indicate the closest resemblence of colors 

# Sample Use Case
You may also opt to use the values/mathematical operations from the repository for your work, in my case, i used the values for my research work to identify the colors of a vehicle.

Given an image: 
https://s7.postimg.cc/x9c5vwd8r/20993931_10154813482958093_5329046734260459022_n.jpg

I took the dominant color, and compared it with the list of values to determine the dominant color of this vehicle.


# Screenshot

![Image of Final Product](https://raw.githubusercontent.com/BrightTux/ColorDistance/master/screenshot/excelProduced.JPG)

![Color Samples](https://raw.githubusercontent.com/BrightTux/ColorDistance/master/screenshot/color%20palletes.JPG) 


# Credits

1. https://www.compuphase.com/cmetric.htm for their low-cost estimation of LUV color distance from RGB values.
