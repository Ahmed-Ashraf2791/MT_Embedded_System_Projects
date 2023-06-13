/*
 ============================================================================
 Name        : Mini_Project1.c
 Author      : Ahmed Ashraf El-Sayed Bekheet / Diploma 68
 Version     :
 Copyright   : Your copyright notice
 Description : Project C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void Asking_User(void);      // declare function that used many times and in some cases the function is below the function that calls it so it didn't recognize it
void Sensor_Set_Menu(void);  // declare function that used many times and in some cases the function is below the function that calls it so it didn't recognize it

int vechile_speed = 50;        //initial value (global variable)
int room_temperature = 35;     //initial value (global variable)
int engine_temperature = 90;   //initial value (global variable)

void set_controller_temp(void){
	printf("The Measured Current Engine Temperature Using Sensor is\n");
	scanf(" %d",&engine_temperature);
	if((engine_temperature < 100) || (engine_temperature > 150)){
		engine_temperature = 125;
		printf("Engine is ON\n");                           //always ON no need for variable because we choose it to be ON from previous option
		printf("AC is OFF\n");                              // i donot know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Vechile Speed is %d Km/Hr\n",vechile_speed);
		printf("Room temperature is %d C\n",room_temperature);
		printf("Engine Temperature Controller is ON\n");    // i donot know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Engine Temperature: %d C\n\n",engine_temperature);
		Sensor_Set_Menu();
	}
	else{
		printf("Engine is ON\n");                           //always ON no need for variable because we choose it to be ON from previous option
		printf("AC is OFF\n");                              // i donot know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Vechile Speed is %d Km/Hr\n",vechile_speed);
		printf("Room temperature is %d C\n",room_temperature);
		printf("Engine Temperature Controller is OFF\n");   // i donot know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Engine Temperature: %d C\n\n",engine_temperature);
		Sensor_Set_Menu();
	}

}
void set_AC_temp(void){
	printf("The Measured Current Room Temperature Using Sensor is\n");
	scanf(" %d",&room_temperature);
	if((room_temperature < 10) || (room_temperature > 30)){
		room_temperature = 20;
		printf("Engine is ON\n");                               //always ON no need for variable because we choose it to be ON from previous option
		printf("AC is ON\n");                                   //  i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Vechile Speed is %d Km/Hr\n",vechile_speed);
		printf("Room temperature is %d C\n",room_temperature);
		printf("Engine Temperature Controller is OFF\n");       // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Engine Temperature: %d C\n\n",engine_temperature);
		Sensor_Set_Menu();
	}
	else{
		printf("Engine is ON\n");                                //always ON no need for variable because we choose it to be ON from previous option
		printf("AC is OFF\n");                                   // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Vechile Speed is %d Km/Hr\n",vechile_speed);
		printf("Room temperature is %d C\n",room_temperature);
		printf("Engine Temperature Controller is OFF\n");        // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
		printf("Engine Temperature: %d C\n\n",engine_temperature);
		Sensor_Set_Menu();

	}
}

void set_vechile_speed(void){
	char traffic_light;
	printf("the required color is\n");
	scanf(" %c",&traffic_light);                           //take traffic light letter from user or (sensor)
	switch(traffic_light){
	case 'g' : vechile_speed = 100; //case 'g' is to set vechile speed to 100 and display the results and display the menu of requirment 5
	printf("Engine is ON\n");                              //always ON no need for variable because we choose it to be ON from previous option
	printf("AC is OFF\n");                                 // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
	printf("Vechile Speed is %d Km/Hr\n",vechile_speed);
	printf("Room temperature is %d C\n",room_temperature);
	printf("Engine Temperature Controller is OFF\n");      // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
	printf("Engine Temperature: %d C\n\n",engine_temperature);
	Sensor_Set_Menu();
	break;

	case 'o' : vechile_speed = 30;  //case 'o' set vechile speed to 30 and do some processing and display the results and display the menu of requirment 5
	room_temperature = room_temperature*(5/4)+1;
	engine_temperature = engine_temperature*(5/4)+1;
	printf("Engine is ON\n");
	printf("AC is ON\n");                              // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
	printf("Vechile Speed is %d Km/Hr\n",vechile_speed);
	printf("Room temperature is %d C\n",room_temperature);
	printf("Engine Temperature Controller is ON\n");   // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
	printf("Engine Temperature: %d C\n\n",engine_temperature);
	Sensor_Set_Menu();
	break;

	case 'r' : vechile_speed = 0;   //case 'r' set vechile speed to 100 and display the results and display the menu of requirment 5
	printf("Engine is ON\n");                                              //always ON no need for variable because we choose it to be ON from previous option
	printf("AC is OFF\n");                                                 // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
	printf("Vechile Speed is %d Km/Hr\n",vechile_speed);
	printf("Room temperature is %d C\n",room_temperature);
	printf("Engine Temperature Controller is OFF\n");                      // i don't know how to use enum ON/OFF for AC how i print string not int(0 or 1)
	printf("Engine Temperature: %d C\n\n",engine_temperature);
	Sensor_Set_Menu();
	break;

	default : printf("Please choose from small letters g or o or r");      //choose anything not in {'g','r','o'} display in console to choose from the three letters
	}

}


void Choose_Menu(char menu){       //function that used to choose from menu of requirment 5 and do some processsing based on each option and display the results and in each result go back and show menu of requirment 5
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	switch(menu){                  //switch case from option a to d in function Sensor_Set_Menu
	case 'a' :                     //option a view the menu in requirment 1
		Asking_User();             //call the function thats displays the menu in requirment 1
		break;

	case 'b' :   //option b take from user traffic light letter and there is three letters, in each one of them we do some processing , display the results and display the menu of requirment 5
		set_vechile_speed();
		break;

	case 'c' :	 //option c in menu of requirment 5 to set room temp and AC ON/OFF based on some conditions and display the results and display the menu of requirment 5
		set_AC_temp();
		break;

	case 'd' :   //option d in menu of requirment 5 to set engine temp and controller ON/OFF based on some conditions and display the results and display the menu of requirment 5
		set_controller_temp();
		break;

	default : printf("Please choose from option a or b or c or d");
	}
}


void Sensor_Set_Menu(void){          // function that display the menu of requirment 5
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature \n");
	printf("d. Set the engine temperature\n\n");
	char menu;
	scanf(" %c",&menu);
	Choose_Menu(menu);
}

void Options(char option){           // function that diplay the system state based on which option of the three option
	switch(option){
	case 'a' : printf("The Vehicle Engine is ON\n");
	Sensor_Set_Menu();
	break;
	case 'b' : printf("The Vehicle Engine is OFF\n");
	Asking_User();
	break;
	case 'c' : printf("c. Quit The System\n\n");
	exit(1);
	default : printf("Please choose from option a or b or c");
	}
}

void Asking_User(void){             // function that display the menu of requirment 1
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char input;
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf(" %c",&input);
	Options(input);
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	Asking_User();
	return 0;
}



