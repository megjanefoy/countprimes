#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

/*
 * Title: Lab 6
 * Semester: COP4338 - Spring 2021
 * Author Megan Jane Thompson
 *
 * This program creates n numbers of processes to find all
 * prime numbers 0 to 50000
 *
 */


/*
 * This method checks if the number is a prime number and
 * This returns true if prime, false if not prime.
 *
 * @int num	 the number to be checked
 * @int id	 the process id number
 * @return   1 if true, 0 if false
 */
int check_prime(int num, int id) {
	int i;
	int flag = 0;

	if(num == 0 || num == 1){				//do not count 0 or 1 as prime number
		return 0;
	}
	else{
		for (i = 2; i <= num/2; ++i){
			if (num % i == 0){				//checks to see if number divides evenly
				flag = 1;					//sets flag if number is not prime
				i = num;					//breaks the loop
			}
		}
	}
	if(flag == 0){							//number is prime
		printf("Process ID#%d found Prime Number %d.\n", id, num);
		fflush (stdout);
		return 1;							//return true
	}
	else{
		fflush (stdout);
		return 0;							//return false
	}
}

int main (int argc, char *argv[]) {
	int count;           					//solutions found by this proc
	double elapsed_time;  					//time to find, count solutions
	int global_count;     					//total number of solutions
	int id;               					//process rank
	int p;                					//number of processes
	int i;

	/*obtain mpi information*/
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	/* Start timer */
	MPI_Barrier (MPI_COMM_WORLD);
	elapsed_time = - MPI_Wtime();

	/*loop until 50,000*/
	count = 0;
	for (i = id; i <= 50000; i += p){
		count += check_prime(i, id);
	}

	/*consolidate prime number counts*/
	MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0,
			MPI_COMM_WORLD);

	/* Stop timer */
	elapsed_time += MPI_Wtime();

	/*end mpi*/
	MPI_Finalize();
	if (!id) {								//master prints execution time
		printf ("Execution time %8.6f\n", elapsed_time);
		fflush (stdout);
	}
	if (!id){								//master prints total number of primes found
		printf ("There are %d prime numbers from 0 to 50000.\n", global_count);
		fflush (stdout);
	}
	return 0;
}

