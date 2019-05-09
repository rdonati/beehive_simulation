How to run our code:

1. Open TheBeesKnees folder
2. To generate the data, open the main.cpp file of the Beehive subproject
    - In the line that reads: Beehive b("testID", 1, 10), the first parameter is the HiveID, the second is the month, and the third is the number of boards.
	- Run the main method and it will generate a file called example.txt
3. Navigate to the build folder and move this file to the UDPHandler subproject (still in the build folder)
4. Open UDPHandler project
5. Run main.cpp



How to Read the Output:

	Each custer represents one UDP message and looks like this:

	0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  
	----  B---  ----  ----  ----  ----  ----  ----  ----  --BB  13:43:16.285
	----  ----  ---B  ----  ----  ----  ----  ----  ----  ----  



	The top line of numbers 0-2 are path states, which keep track of the state of each path.. here is a key

	0 = Dormant (no bee activity)
	1 = Going out (bee has gone from the inside of the hive into the path)
	2 = Going in (bee has gone from the outside of the hive into the path)

	The time on the right is a timestamp for that USP message.

	Each ---- is one of the the ten boards.
		 ----

	The gates are lined up as you would interpret them on the hive with the inside of the hive being on top and the outside being on the bottom. For example:
		--B-
		----
	Would indicate that a bee is coming from the inside of the hive and triggering the inner gate.

	At the very bottom, we print the total number of bees in, the total number of bees out, and the number of exceptions (e.g. bees poking their heads in and out).

