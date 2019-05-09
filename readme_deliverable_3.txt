Features:
A GUI with an audio representation of bees moving in and out of a hive
A GUI that allows users to navigate through widgets
	*note: this is not yet integrated with the database
An alert system that detects Swarms and Robs

How to use audio representation:
1. In the CustomerGUI main.cpp file main method, make sure that the following sections are commented out:
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.show();
    WelcomeNewUser wnu;
    wnu.show();*/

    BeeChimes bc;
    bc.show();

    return a.exec();
}
2. Run the CustomerGUI project
3. Press play. This will play through the hard coded simulation
4. Pressing pause will pause the music. Pressing stop will stop and reset the music. Sliding the volume bar will adjust the volume level.

How to use the widget navigation
Note: since this is not currently integrated with the database, this explains how to navigate through the various screens.
1. Log in with username: bees password: bees
2. Press View Hive on the Home Screen
3. Press Select Hive to navigate to the Hive Screen
4. Press View Data to view the Data Screen
5. Press Back to go back to the Hive Screen
6. Press Edit Hive to go to the Edit Hive Screen
7. Press Submit Changes to go back to the Hive Screen
8. Press Back to go back to the Find Hive Screen
9. Press Home to go back to the Home Screen
10. Press Add Hive to go to the Add Hive Screen
11. Press Add or Cancel to go back to the Home Screen
12. Press Logout to go back to the Login Screen
13. Press New User to go to the New User Screen
14. Press Create User to go back to the Login Screen
	*note: since this is not yet integrated to the database you cannot login with this username and password
15. Press Forgot Passsword to go to the Forgot Password Screen
16. Press Reset Password to go back to the Login Screen

How to run the alert system
1. Run Beehive.main to generate UDP Messages
2. Go to build file for Beehive and retrieve the "example.txt" file which should have UDP messages
3. Copy the "example.txt" file into the AlertSystem folder in the build folder
4. Run the AlertSystem.main file and watch alerts pop up
5. Press close to continue the alerts