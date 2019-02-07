**Please read this text before compiling the code**

1. Complie the C file, rand_input.c. Then enter ./rand_input in your terminal to run the code.
   (The purpose of this C file is to create a input file with 10X10 matrix of random numbers (range: 0-100))

2. Complie the C file, avg_grd_cal.c, then run the code to get avrage grade of all homeworks of all chapters. 


**My idea of developing Average Grade Calculator (avg_grd_cal.c)**

1. Create a function (double Average (homework number)): this function will read input file, and it will find one homework of each student based on parameter(homework number). Then sum homework grade of all students, and return the average. 

2. In the main function, it has one "Director" parent process creates the 5 Manager children (5 chapters), then each Manager sub-parent process creates the two Worker children (total is 10 homeworks). Each Worker children will pass their homework number to the function (double Average (homework number)). After get return value from function, it will print it's homework number and average grade. 
Before the next Manager starts, I use usleep(10000) to wait present Manager finish.
