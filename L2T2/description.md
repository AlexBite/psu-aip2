In this solution, we define the function calculateMaxGold that takes a vector columns representing the number of gold coins on each column and an integer k representing the maximum jump distance.

We use dynamic programming to calculate the maximum amount of gold the Grasshopper can collect at each column. We maintain two arrays: dp to store the maximum gold collected up to each column and path to store the previous column index in the optimal path.

We iterate through each column, starting from the second column, and calculate the maximum gold by considering the maximum gold from the previous reachable columns within the jump distance k. We update the dp array and store the previous column index in the path array.

After calculating the maximum gold for all columns, we construct the optimal path by following the path array from the last column to the first column.

In the main function, we prompt the user to enter the number of columns, the maximum jump distance, and the number of gold coins on each column. Then, we call the calculateMaxGold function to determine the optimal path