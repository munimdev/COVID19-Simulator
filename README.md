Open Sem2_Project(.exe) in the release folder 
to run program

All code written by us was done so in C++. We 
included the use of a library which was written 
in Python, so our .exe file requires Python and
some of its libraries to run.

# Requirements

Requirements to run the program/the executable:
Python 3.9, and two Python libraries: matplotlib
and NumPy

Including almost all code files (.cpp and .h are all
included). The program was made in the Qt IDE, so 
the Qt-specific files are not added.

# Instructions

- Enter parameters on the right side of the screen

- Press the Red "Start Virus Simulation" button on 
the bottom-right

- This should open a new window which will start 
plotting a graph

- In case you feel the need to end the plotting 
early and start a new plot, press the "Terminate 
Plotting" button at the top middle (it may be 
hidden by the graph window, so drag it down
to access the button)

- Enter new parameters and repeat, or close the
parameters window (closing the graph window will
not do anything). Ensure graph window has 
terminated plotting before closing.

# Project Demo
![demo](https://github.com/munimdev/COVID-19-Simulator/blob/main/Project%20Demo.gif)

# Additional Notes

- Maximum allowed population is 10 million, which can
feasibly run on most computers. However, we suggest
to not go past 2-5 million, as it may cause the program
to run slowly.

- Resizing or using the tools on the graph window
may cause the program to crash, so be wary.

- The parameters set by default worked best for us.
Try other combinations as you please, though.

- In case the program crashes, close the window,
rerun the .exe, and it should work fine again.

- Including the "healthy" line may make it so that 
other values do not show much change, especially if a 
very large population is set. This is because the
graph scales the y-axis according to maximum value
plotted.

- You may have to press "Terminate Plotting" more
than once for it to work. Mixed effectiveness on 
different devices. 
