/*
 ============================================================================
 Name        : BRA-console.c
 Author      : Barracuda-marina
 Version     :
 Copyright   : GNU
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int interceptor_to_bullseye_course, bullseye_to_bandit_radial, bandit_altitude, bullseye_to_interceptor_radial, gamma_deg;

double interceptor_to_bullseye_distance, bandit_to_bullseye_distance, gamma_rad, beta_rad, cos_gamma_rad, cos_beta_rad, beta_deg, alfa_deg, distance_to_bandit, interceptor_to_bandit_course;

// Data input with validation

int input_block() {

	printf("---------------------------------------------------\n");
	printf("         Input AWACS data below: \n");
	printf("---------------------------------------------------\n");
	printf("Interceptor course to BullsEye (0-360 degree): ");
	scanf("%i", &interceptor_to_bullseye_course);
	while ((interceptor_to_bullseye_course < 0) || (interceptor_to_bullseye_course > 360))
	{
            printf("Not correct, try again: ");
            scanf("%i", &interceptor_to_bullseye_course);
        }

	printf("Interceptor to BullsEye distance (1-500 nm): ");
	scanf("%lf", &interceptor_to_bullseye_distance);
	while ((interceptor_to_bullseye_distance < 1.0) || (interceptor_to_bullseye_distance > 500.0))
	{
            printf("Not correct, try again: ");
            scanf("%lf", &interceptor_to_bullseye_distance);
        }

	printf("BullsEye radial to Bandit (0-360 degree): ");
	scanf("%i", &bullseye_to_bandit_radial);
    while ((bullseye_to_bandit_radial < 0) || (bullseye_to_bandit_radial > 360))
	{
            printf("Not correct, try again: ");
            scanf("%i", &bullseye_to_bandit_radial);
        }

	printf("Bandit to BullsEye distance (1-500 nm): ");
	scanf("%lf", &bandit_to_bullseye_distance);
	while ((bandit_to_bullseye_distance < 1.0) || (bandit_to_bullseye_distance > 500.0))
	{
            printf("Not correct, try again: ");
            scanf("%lf", &bandit_to_bullseye_distance);
        }

	printf("Bandit Altitude (1- 50000 feet): ");
	scanf("%i", &bandit_altitude);
	while ((bandit_altitude < 1) || (bandit_altitude > 50000))
	{
            printf("Not correct, try again: ");
            scanf("%i", &bandit_altitude);
        }

	printf("Correct. Accepted...\n");
		return 0;
}

// Radian to degree conversion

double rad_to_grad (double rda) {
	double pi, gr;

	pi = 3.14159265359;
	gr = (rda*180)/pi;

	return (gr);
}

// Degree to Radian conversion

double grad_to_rad (double gra) {
	double pi, rd;

	pi = 3.14159265359;
	rd = (gra*pi)/180;

	return (rd);
}


int mathematic_block()	{

// Interceptor Radial

	if 	((interceptor_to_bullseye_course >= 0) && (interceptor_to_bullseye_course <= 179))	{
	bullseye_to_interceptor_radial = (interceptor_to_bullseye_course + 200 - 20);
	}


	if ((interceptor_to_bullseye_course >= 180) && (interceptor_to_bullseye_course <= 359))	{
	bullseye_to_interceptor_radial = (interceptor_to_bullseye_course - 200 + 20);
	}

// Angle between Interceptor and Bandit

	gamma_deg = abs(bullseye_to_bandit_radial - bullseye_to_interceptor_radial);

	if (gamma_deg >= 180) {
		gamma_deg = 360 - gamma_deg;
	}

	if (gamma_deg == 0) {
		gamma_deg = 179;
	}

// Distance from Interceptor to Bandit

	gamma_rad = grad_to_rad(gamma_deg);
	cos_gamma_rad = cos(gamma_rad);

	distance_to_bandit = sqrt(bandit_to_bullseye_distance*bandit_to_bullseye_distance + interceptor_to_bullseye_distance*interceptor_to_bullseye_distance - 2*bandit_to_bullseye_distance*interceptor_to_bullseye_distance*cos_gamma_rad);

// All angles

	cos_beta_rad = (distance_to_bandit*distance_to_bandit + bandit_to_bullseye_distance*bandit_to_bullseye_distance - interceptor_to_bullseye_distance*interceptor_to_bullseye_distance)/(2*distance_to_bandit*bandit_to_bullseye_distance);

	beta_rad = acos(cos_beta_rad);
	beta_deg = rad_to_grad(beta_rad);
	alfa_deg = 180.0 - (gamma_deg + beta_deg);

// Bandit azimuth

	if (bullseye_to_bandit_radial >= interceptor_to_bullseye_course) {

        interceptor_to_bandit_course = interceptor_to_bullseye_course + alfa_deg;
	}

	if (bullseye_to_bandit_radial < interceptor_to_bullseye_course)  {

        interceptor_to_bandit_course = interceptor_to_bullseye_course - alfa_deg;
	}

	return 0;
}


// Debug block

int debug_block() {

    printf("\n");
	printf("\n");
	printf("Debug data: \n");
	printf("\n");
	printf("Interceptor course to BullsEye: %u degree\n", interceptor_to_bullseye_course);
	printf("BullsEye radial to Interceptor: %u degree\n", bullseye_to_interceptor_radial);
	printf("Interceptor distance from BullsEye: %6.1lf nm\n", interceptor_to_bullseye_distance);
	printf("BullsEye radial to Bandit: %u degree\n", bullseye_to_bandit_radial);
	printf("Bandit distance from BullsEye: %6.1lf nm\n", bandit_to_bullseye_distance);
	printf("Bandit Altitude: %u feet\n", bandit_altitude);
	printf("Gamma-angle (Interceptor to Bandit) : %u degree\n", gamma_deg);
	printf("Alfa-angle: %6.0lf degree\n", alfa_deg);
	printf("Beta-angle: %6.0lf degree\n", beta_deg);

	return 0;
}

// Data output

int output_block() {

	printf("--------------- Bandit   B R A --------------------\n");
	printf("---------------------------------------------------\n");
	printf("B: %6.0lf dg\n", interceptor_to_bandit_course);
	printf("R: %6.1lf nm\n", distance_to_bandit);
    printf("A: %6i ft\n", bandit_altitude);
	printf("---------------------------------------------------\n");

	printf("Dismissed!\n");
		return 0;
}

// Clear screen

int main() {

    char cc;

    cc = 'c';
    system("cls");
    while ((cc == 'c')||(cc == 'C')) {

        input_block();
        mathematic_block();
//        debug_block(); /*Uncoment this line for debugging*/
        output_block();
        printf("Press <C>+<Enter> to continue or only <Enter> to exit...");
        getchar();cc = getchar();
        system("cls");
    }
	return EXIT_SUCCESS;
}

