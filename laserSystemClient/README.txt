HOW TO USE laserSystemClientClass:

- Add the directory in main with:
	#include <laserSystemClientClass/lasersystemclient.h>
- Create an object with of the class with:
	laserSystemClient laserPositionClient("127.0.0.1");    //Use the IP of the USE server
- Create a data struct with 4 float with:
	laserSystemClient::positionData d;
- Finally, call the method every time you want to get data:
	d = laserPositionClient.getData();                     //Store the info in the struct previously create