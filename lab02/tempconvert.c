#include <stdio.h>

void fahrenheit2celsius(float fFahrenheitIn)

{ float fCelsius = (fFahrenheitIn - 32) * 5 / 9;
       
printf("%.2f degrees Celsius\n", fCelsius);

	return;
}

void celsius2fahrenheit(float fCelsiusIn)
{
	float fFahrenheit = (fCelsiusIn * 9 / 5) + 32;
	
	printf("%.2f degrees Fahrenheit\n", fFahrenheit);

	return;
			
}

	int main(void) 
{
	float fCelsius = 0;
	int selection = 0;

	do
	{
       	printf("Welcome to the Temperature Converter\n");
	printf("Select from one of the following options: \n");
       	printf("1. Convert from Fahrenheit to Celsius\n");
       	printf("2. Convert from Celsius to Fahrenheit\n"); 
	printf("3. Exit the Converter.\n");
      
	scanf("%d", &selection);

	if (selection == 1)
	{
		float temperature = 0.0;
	
		printf("Enter a temperature in Fahrenheit: ");
		scanf("%f", &temperature);

		fahrenheit2celsius(temperature);
	
	}
	else if (selection == 2)
	{
		float temperature = 0.0;

		printf("Enter a temperature in Celsius: ");
		scanf("%f", &temperature);

		celsius2fahrenheit(temperature);

	}
	else if (selection == 3)
	{
		printf("Goodbye\n");
		return 0;
	}
	else
		printf("You did not enter a valid selection. Try again.\n");

	}while(selection != 3);
       
	return 0;
       	}
