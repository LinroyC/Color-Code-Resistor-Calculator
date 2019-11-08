// Welcome to our Resistor Color Code Calculator.
// Created by Linroy Cruz & Jacky Yuan
// Enjoy!! :)

#include "stdafx.h"
#include <iostream>
#include <math.h>


char *colors[] = { "Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Gray", "White" };
char option, restart;
short b1, b2;
float b3, real, imaginary, mag, angle;
int powb3, resist, multiplier;



int main(){

start:
    system("cls");
    printf("                       *RESISTOR COLOR CODE CALCULATOR*\n");
    printf("\n");
    printf("Enter 1 for color bands to value.\nEnter 2 for value to color bands.\nEnter 3 for rectangular to polar conversion.\nEnter 4 for polar to rectangular conversion (experimental/radians).\nEnter 5 to exit.\n");
    scanf_s("%d", &option);

    asm{
        MOV CL, option;
        CMP CL, 01;
        JE btv;
        CMP CL, 02;
        JE vtb;
        CMP CL, 03;
        JE retopo;
        CMP CL, 04;
        JE potore;
        CMP CL, 05;
        JE end;
    }
    printf("Enter only 1, 2 or 3, program will restart\n");
    system("pause");
    goto start;

btv:
    system("cls");
    printf("The colored bands are coded as follows:\n\n\t");

    printf("COLOR\t\t\tCODE\n\t");
    printf("-----\t\t\t----\n\n");
    printf("\tBlack-------------------> 0\n");
    printf("\tBrown-------------------> 1\n");
    printf("\tRed---------------------> 2\n");
    printf("\tOrange------------------> 3\n");
    printf("\tYellow------------------> 4\n");
    printf("\tGreen-------------------> 5\n");
    printf("\tBlue--------------------> 6\n");
    printf("\tViolet------------------> 7\n");
    printf("\tGray--------------------> 8\n");
    printf("\tWhite-------------------> 9\n");

    printf("\nFirst band: ");
    scanf_s("%d", &b1);
    printf("Second band: ");
    scanf_s("%d", &b2);
    printf("Third band: ");
    scanf_s("%f", &b3);

    asm{
        MOV BX, b1;        //moves b1 into bx
        CMP BX, 00;        //compares b1 value to 0
        JL errorbtv;    //if <0, show error
        CMP BX, 9d;        //compares b1 value to 9
        JG errorbtv;    //if >9, show error

        MOV BX, b2;
        CMP BX, 00;
        JL errorbtv;
        CMP BX, 9d;
        JG errorbtv;

        MOV EBX, b3;
        CMP EBX, 00;
        JL errorbtv;
        CMP BX, 7d;
        JG errorbtv;
        JMP startbtv;
    }

errorbtv:
    printf("Incorrection option, please re-enter band colors\n");
    system("pause");
    goto btv;

startbtv:
    b3 = pow(10, b3);
    powb3 = (int)b3;
    asm{
        MOV EAX, 10;        //puts 10 in eax register
        MOV ECX, 0;            //clears out ecx register
        MOV CX, b1;            //moves first band into cx
        MUL CX;                //multiplies first band with eax value, 10
        MOV CX, b2;            //moves second band into cx
        ADD EAX, ECX;        //adds second band into eax(first band)
        MOV ECX, powb3;        //moves third band (multiplier) into ecx
        MUL ECX;            //multiplies the multiplier with current value
        MOV resist, EAX;    //throws result in resist
    }

    printf("Resistance: %d ohms\n", resist);
    system("pause");
    printf("\nTo enter new values: Enter 1\n");
    printf("To go back to the main menu: Enter 2\n");
    printf("To exit: Enter anything\n");
    scanf_s("%d", &restart);

    asm{
        MOV CL, restart;
        CMP CL, 01;
        JE btv;
        CMP CL, 02;
        JE start;
        JMP end;
    }

vtb:
    system("cls");
    printf("Converting value to band color: \n");
    printf("Enter 1st digit [0-9] : ");
    scanf_s("%d", &b1);
    printf("Enter 1st digit [0-9] : ");
    scanf_s("%d", &b2);
    printf("Enter multiplier as an power of 10 [0-7] : ");
    scanf_s("%d", &multiplier);

    asm{
        MOV BX, b1;        //moves b1 into bx
        CMP BX, 00;        //compares b1 value to 0
        JL errorvtb;    //if <0, show error
        CMP BX, 9d;        //compares b1 value to 9
        JG errorvtb;    //if >9, show error

        MOV BX, b2;
        CMP BX, 00;
        JL errorvtb;
        CMP BX, 9d;
        JG errorvtb;

        MOV EBX, multiplier;
        CMP EBX, 00;
        JL errorvtb;
        CMP BX, 7d;
        JG errorvtb;
        JMP startvtb;
    }

errorvtb:
    printf("Incorrection option, please re-enter band colors\n");
    system("pause");
    goto vtb;

startvtb:
    printf("Color code is : %s %s %s\n", colors[b1], colors[b2], colors[multiplier]);
    system("pause");
    printf("\nTo enter new values: Enter 1\n");
    printf("To go back to the main menu: Enter 2\n");
    printf("To exit: Enter anything\n");
    scanf_s("%d", &restart);

    asm{
        MOV CL, restart;
        CMP CL, 01;
        JE vtb;
        CMP CL, 02;
        JE start;
        JMP end;
    }

retopo:
    system("cls");
    printf("Rectangular to polar\n\n");
    printf("Enter real value: ");
    scanf_s("%f", &real);
    printf("Enter imaginary value: ");
    scanf_s("%f", &imaginary);

    asm{
        FLD real;
        FLD real;
        FMUL;
        FLD imaginary;
        FLD imaginary;
        FMUL;
        FADD;
        FST mag;
    }
    mag = pow(mag, .5);
    angle = atan(imaginary / real) * 180 / 3.14;
    printf("magnitude is: %f\nangle is %f\n", mag, angle);
    system("pause");
    printf("\nTo enter new values: Enter 1\n");
    printf("To go back to the main menu: Enter 2\n");
    printf("To exit: Enter anything\n");
    scanf_s("%d", &restart);

    asm{
        MOV CL, restart;
        CMP CL, 01;
        JE retopo;
        CMP CL, 02;
        JE start;
        JMP end;
    }

potore:
    system("cls");
    printf("Polar to Rectangular\n\n");
    printf("Enter magnitude: ");
    scanf_s("%f", &mag);
    printf("Enter angle: ");
    scanf_s("%f", &angle);
    real = mag*cos(angle);
    imaginary = mag*sin(angle);
    printf("Real value is: %f\nImaginary is %f\n", real, imaginary);
    system("pause");
    printf("\nTo enter new values: Enter 1\n");
    printf("To go back to the main menu: Enter 2\n");
    printf("To exit: Enter anything\n");
    scanf_s("%d", &restart);

    asm{
        MOV CL, restart;
        CMP CL, 01;
        JE potore;
        CMP CL, 02;
        JE start;
        JMP end;
    }


end:
    exit(0);
}
