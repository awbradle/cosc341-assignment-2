//Andrew Bradley
//COSC 341
//02-02-16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//function computes pi using given series to user specified n
double compute_pi(int n)
{
	//this return ends the recursion and also returns something for invalid n's
	
	double total;
	while(n >= 1)
	{
		if (n % 2 == 0)
		{
			total = total - 4.0/(double)( 2 * n - 1);
		}
		else
		{
			total = total + 4.0/(double)( 2 * n - 1);
		}
		n--;
	}
	return total;
}

//computes the square root for user specified x using given formula
double compute_sqrt(double x)
{
	double last = 1.0;
	int counter;
	for (counter = 0; counter < 10; counter++)
	{
		last = 0.5 * (last + x/last);
	}
	return last;
}

//determines if n is prime. returns 1 on true, 0 on false
int is_prime(int n)
{
	double root = compute_sqrt((double) n) + 1.0;
	int counter;
	//returns 0 for invalid values n
	if(n < 2)
		return 0;
	if(n == 2)
		return 1;
	//checks each value from 2 to floor of square root of n + 1
	for (counter = 2; counter < (int)root; counter++)
	{
	 	if (n % counter == 0)
	 	{
	 		return 0; //if number is not prime
	 	}
	} 
	return 1; //if number is prime
}

//display all primes less than or equal to n
void display_primes(int n)
{
	int counter;
	printf("Prime numbers less than or equal to %d: ",n);
	for (counter = 2; counter <= n; counter++)
	{
		if(is_prime(counter))
		{
			printf("%d, ", counter);
		}
	}
	printf("\n");
}

//Keep track of student scores and prints out the high score, low score, and average
//when a user quits
void process_scores()
{
	printf("Please enter a student name followed by their score: ");
	char student[20];				//the student entered
	int student_score = 0;			//the student's score
	char best[20] = "none";			//the best student and their score
	int best_score = 0;				//the best student's score
	char worst[20] = "none";		//the worst student and their score
	int worst_score =0;				//the worst student's score
	int average_score = 0;			//the average of the scores entered
	int number_scores_entered = 0;	//number of student scores entered
	
	//First value entered. Is used to prime best and worst student value
	scanf("%s %d", student, &student_score);
	//These prime the variables with the first entered student
	strcpy(best,student);	//copy first student into the best student
	strcpy(worst,student);	//copy first student into the worst student
	best_score = worst_score = student_score;
	
	while(strcmp(student,"q") != 0 && strcmp(student,"Q") != 0)
	{
		printf("Enter a student name followed by their score. Enter 'q 0' to quit.\n");
		number_scores_entered++;
		average_score += student_score;
		if (student_score > best_score)
		{
			best_score = student_score;
			strcpy(best,student);
		}
		if (student_score < worst_score)
		{
			worst_score = student_score;
			strcpy(worst,student);
		}
		scanf("%s %d", student, &student_score);
	}	
	
	average_score = average_score / number_scores_entered;
	printf("best student: %s\n", best);
	printf("best score: %d\n", best_score);
	printf("worst student: %s\n", worst);
	printf("worst score: %d\n", worst_score);
	printf("average score: %d\n", average_score); 
	
	
}

//Computes a tax rate for incomes based on the rules given.
double compute_tax(int income, char *status, char state)
{	
	double out_of_state = 0; //out of state modifier
	
	//This block of if statements validate data.
	if(income <= 0)
	{
		return -1.0;
	}
	if(strcmp (status, "single") != 0  && strcmp (status, "married") != 0 &&
		strcmp (status, "SINGLE") != 0  && strcmp (status, "MARRIED") != 0)
	{	
		return -1.0;
	}
	if (state != 'i' && state != 'I' && state != 'o' && state != 'O')
	{
		return -1.0;
	}
	
	//if out of state, set -3% modifier to tax rate
	if (state == 'o' || state == 'O')
	{
		out_of_state = -.03;
	}
	//Calculate single tax rate
	if (strcmp (status, "single") ==0 || strcmp (status, "SINGLE") ==0)
	{
		if (income < 30000)
		{	
			return ((double)income * (.2 + out_of_state));
		}
		else
		{
			return ((double)income * (.25 + out_of_state)); 	
		}
	}
	//Calculate married tax rate
	if (strcmp (status, "married") ==0 || strcmp (status, "MARRIED") ==0)
	{
		if (income < 50000)
		{	
			return ((double)income * (.1 + out_of_state));
		}
		else
		{
			return ((double)income * (.15 + out_of_state));
		}
	}
	//For any missed invalid data
	return -1.0;
}

//Solves a quadratic equation and returns the solutions in the solution pointers
int quadratic(double a, double b, double c, double *solution1, double *solution2)
{
	//Case of no solutions
	if ((b * b) - (4.0 * a * c) < 0)
	{
		*solution1 = 0.0;
		*solution2 = 0.0;
		return 0; //no solution
	}
	*solution1 = (-b + sqrt(b*b - 4.0 * a * c)) / (2.0 * a);
	*solution2 = (-b - sqrt(b*b - 4.0 * a * c)) / (2.0 * a);
	return 1; //solutions exist
}

//Recursive factorial function returns n * (n - 1) * .. * 1
int factorial(int n)
{
	//Ends recursion and provides return value for n < 1
	if (n <= 1)
	{
		return 1;
	}
	return n * factorial(n-1);
}

//Function counts the number of lines and characters in a file, including EOF.
//Returns those results in *characters and *lines for *file specified.
//user passes file name with *file pointer
void file_count(char *file, int *characters, int *lines)
{
	FILE *fp;
	fp = fopen(file, "r");
	char ch;
	//Counts each character including EOF. Counts each line.
	while (ch != EOF)
	{
		ch = getc(fp);
		*characters = *characters + 1;
		if (ch == '\n' || ch == EOF)
		{
			*lines = *lines + 1;
		}
	}
	fclose(fp); //close file
}	

//Uses three dynamic arrays to sort a file's lines by student id number.
//File Specified by *infile. Writes the sorted information to file specified by *outfile.
void file_sort(char *infile, char *outfile)
{
	FILE *students_in;
	FILE *students_out;
	students_in = fopen(infile, "r");
	students_out = fopen(outfile, "w");
	//inputs number of students to student_number
	int student_number;
	fscanf(students_in,"%d", &student_number);
	
	//create an array of string names, int ages, double GPAs
	int *id = (int*)malloc(student_number * sizeof(int));
	char *grade = (char*)malloc(student_number * sizeof(char));
	double *gpa = (double*)malloc(student_number * sizeof(double));
	
	//this loop loads the three arrays with names, ages, and GPAs
	int counter;
	for(counter = 0; counter < student_number; counter++)
	{
		fscanf(students_in,"%d %c %lf", &id[counter],&grade[counter],&gpa[counter]);
	}
	//this sorts the arrays with a bubble sort
	int change = 1; //keep track of if arrays are in order;
	//temp variables facilitate switching array data for the sort
	int temp_id;
	char temp_grade;
	double temp_gpa;
	while (change != 0) //loops until student id numbers are sorted
	{
		change = 0; //reset check if it is sorted
		for (counter = 0; counter < student_number - 1; counter++)
		{	
			if (id[counter] > id [counter+1])
			{
				temp_id = id[counter];
				temp_grade = grade[counter];
				temp_gpa = gpa[counter];
				id[counter] = id[counter+1];
				grade[counter] = grade[counter+1];
				gpa[counter] = gpa[counter+1];
				id[counter+1] = temp_id;
				grade[counter+1] = temp_grade;
				gpa[counter+1] = temp_gpa;
				change = 1; //causes loop to run again because data changed position
			}
		}	
	}
	fprintf(students_out,"%d\n",student_number); //write student number to outfile
		//writes student data to file specified in outfile
		for(counter = 0; counter < student_number; counter++)
		{
			fprintf(students_out,"%d %c %lf\n", id[counter],grade[counter],gpa[counter]);
		}
	//free memory, close file
	free(id);
	free(grade);
	free(gpa);
	fclose(students_in);
	fclose(students_out);
}

//Loads student data into array of student structures, sorts the student information
//by student name. Prints the average GPA, names of students with a GPA >= 2.0
//and the data of all students sorted by name
void file_student(char *infile)
{
	FILE *students_in;
	students_in = fopen(infile, "r");
	int student_number;
	fscanf(students_in,"%d", &student_number);
	
	//student structure stores name, age, and GPA read from file.
	struct student
	{
		char name[20];
		int age;
		double gpa;
	};
	//create array of student structures
	struct student *my_students = 
		(struct student*)malloc(student_number * sizeof(struct student));
	
	//read student information into student array
	int counter;
	double average_gpa;
	for(counter = 0; counter < student_number; counter++)
	{
		fscanf(students_in,"%s %d %lf", my_students[counter].name,
			&my_students[counter].age,&my_students[counter].gpa);
		average_gpa = average_gpa + my_students[counter].gpa;
		
	}
	
	average_gpa = average_gpa / (double)student_number;
	//sort students by name using bubble sort
	int change = 1;
	struct student temp_student;
	while (change != 0)
	{
		change = 0;
		for (counter = 0; counter < student_number - 1; counter++)
		{	
			if (strcmp(my_students[counter].name,my_students[counter+1].name) > 0)
			{
				temp_student = my_students[counter+1];
				my_students[counter+1] = my_students[counter];
				my_students[counter] = temp_student;
				change = 1; 
			}
		}	
	}
	printf("Average GPA: %lf\n",average_gpa);
	printf("\nStudents with at least 2.0 GPA\n");
	for(counter = 0; counter < student_number; counter++)
	{
		if(my_students[counter].gpa >= 2.0)
		{
			printf("Name: %s \n", my_students[counter].name);
		}
	}
	printf("\nStudent Information in Ascending Order\n");
	for(counter = 0; counter < student_number; counter++)
	{
		printf("Name: %s Age: %d GPA: %lf\n", my_students[counter].name,
			my_students[counter].age,my_students[counter].gpa);
	}
	free(my_students);
	fclose(students_in);
}
int main()
{
	int selection;;
	//Loop with switch statement drives the user interface
	//User keeps entering options until they quit
	do
	{
	printf("Please Select an Option\n");
	printf("1-Computing pi\n");
	printf("2-Computing Square Root\n");
	printf("3-Displaying Primes\n");
	printf("4-Processing Grades\n");
	printf("5-Computing Tax\n");
	printf("6-Solving Quadratic\n");
	printf("7-Computing Factorials\n");
	printf("8-Counting File\n");
	printf("9-Sorting File\n");
	printf("10-Student File\n");
	printf("11-Quit\n");
	scanf("%d",&selection);
	
	switch(selection)
	{
		case 1: //Compute pi
		{
			int n;
			printf("How many terms of pi do you wish to compute: ");
			scanf("%d",&n);
			printf("pi to %d terms is %lf\n",n,compute_pi(n));
			break;
		}
		case 2: //Compute square root
		{
			double n;
			printf("Which square root do you wish to compute: ");
			scanf("%lf",&n);
			printf("the square root of %lf is %lf\n",n,compute_sqrt(n));
			break;
		}
		case 3: //Display primes
		{
			int n;
			printf("Enter an number to calculate primes up to: ");
			scanf("%d",&n);
			display_primes(n);
			break;
		}
		case 4: //Process grades
		{
			process_scores();
			break;
		}
		case 5: //Compute tax
		{
			int income;
			char status[10];
			char state;
			printf("What is your income: ");
			scanf("%d",&income);
			printf("In state or out of state: ");
			scanf("\n%c",&state);
			printf("Are you single or married: ");
			scanf("%s",status);
			printf("Your taxes are: %lf\n",compute_tax(income,status,state));
			break;
		}
		case 6: //Solving quadratic
		{
			double solution1;
			double solution2;
			double a;
			double b;
			double c;
			int solutions;
			printf("enter a: ");
			scanf("%lf",&a);
			printf("enter b: ");
			scanf("%lf",&b);
			printf("enter c: ");
			scanf("%lf",&c);
			solutions = quadratic(a,b,c,&solution1,&solution2);
			if (solutions)
			{
				printf("Solution 1: %lf\n",solution1);
				printf("Solution 2: %lf\n",solution2);
			}
			else
			{
				printf("There were no solutions\n");
			}
			break;
		}
		case 7: //Computing factorial
		{
			int n;
			printf("Enter the factorial to compute: ");
			scanf("%d",&n);
			printf("%d! is %d\n",n, factorial(n));
			break;
		}
		case 8: //counting file
		{
			char input_file[50];
			int characters;
			int lines;
			printf("Enter the file name to open: ");
			scanf("%s",input_file);
			file_count(input_file,&characters,&lines);
			printf("Number of lines: %d\n",lines);
			printf("Number of characters including EOF: %d\n",characters);
			break;
		}
		case 9: //sorting file
		{
			char input_file[50];
			char output_file[50];
			printf("Enter the input file name: ");
			scanf("%s",input_file);
			printf("Enter the output file name: ");
			scanf("%s",output_file);
			file_sort(input_file,output_file);
			printf("Operation Complete\n");
			break;
		}
		case 10: //student file
		{
			char input_file[50];
			printf("Enter the input file name: ");
			scanf("%s",input_file);
			file_student(input_file);
			printf("Operation Complete\n");
			break;
		}
		case 11: //quit
		{
			break;
		}
		
		default: //Error for incorrect entries
			printf("Your entry is invalid. Please try again\n");
	}
	}while(selection != 11); //do until user quits
	return 0;
}