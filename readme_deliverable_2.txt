Capabilities:

Can create a table for users (stores users) and for hives (stores UDP messages, and DB name will be liked to their user IDs)
Can add entries to both types of table
Can query users table for a user given their username and returns a User object, a class which we created
Can query hive table for the most recent n messages
Can check that a username and password match



How to Use:

1. Open the DatabaseUI subproject and run it
2. The first page demonstates hive table capabilities
	–left side adds messages
	-right side gets most recent n messages
	-bottom button prints the current state of the database
3. Click (Options -> Add New User) to get to the next page, which shows the hive table capabilities
	-left side allows for creation of a new user
	-login button test to see whether that the username/password combination {username, mypassword} is present
	-the "username" input and "get user" button allow you to search for a user
		-returns a User object and calls the user's toString method to show that it's gotten the correct data
		*** right now, you must press the "get user" button twice because the callback where the user's properties are set is
		syncronous and has does not finish executing by the time the toString method is called ***

