/*
        Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 07
        Due: March 21, 2019                                             Started: March 19, 2019
        Credit: 10 points.
        
        Problem: Write a progam that takes in a memory blocksize from the command-line that will
        then be used to store random values of various sizes into the memory of the given blocksize
        to fill it up and then use those values to get the sum of the random values. The program
        needs to check the given blocksize to make sure it's a multple of 8, not less than or equal
        to 0, or if the memory can be allocated for it. Afterwards, it stores byte (8-bit) size integers
        in memory then finds the sum of those random integers, then it does the exact same thing for 
        half-word (16-bit), word (32-bit), and double-word (64-bit), then printing it all out.

        Solution: When the program starts it first makses sure that the currect amount of arguments
        were give, if they weren't the program prints out the proper way to use it then ends, else
        it goes through to check if the blocksize is a number and if it is if it's a muliple of 8, 
        if both are true then it checks if its a positive number, if any of these don't check it the
        program will bail out citing the specific reason. Now, the program will allocate memory to this
        new block of memory (getmemblock()) that is the size of the give number this can not work giving
        an allocation error and ending the program, after all of this is passed the program goes through
        and fills the memory block with random byte sized (char) data (loadbytedata()) then adds these
        new byte sized integers (sumbytedata()), The same is done with random 2 byte sized (short int)
        data (loadhalfwdata() & sumhalfwdata()), random 4 byte sized (int) data (loadworddata() & 
        sumworddata()), and random 8 byte sized (long long) data (loaddoublewdata() & sumdoublewdata()). 
        After all of the sums have been found it is then printed to the stderr (printresult()), the 
        memory for memory block is then released and the program ends with a EXIT_SUCCESS.

        Data-structure used: A one-dimensional array for the command line arguments and for the memory
        block.

        Accessing functions for the data structure: Standard C functions for accessing arrays and 
        malloc() to allocate the memory for the memory block array.

        Errors handled: Checks the given arguemnt to make sure it is a number, its positive and 
        that its a multiple of 8. The program also recoginzes when the memory is not able to allocate
        memory. 

        Limitations: The program does not work for any numbers at that are not multiples of 8 and at 
        782 and above double-word sum overflows.

        Acknowledgment: We wrote the program together but we had a lot of help from our classmates 
        throughout the making of it.
*/


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
   char *blkptr;
   long long bytesum, doublewsum, halfwsum, wordsum; int size;
   char *getmemblock(int size);
   void loadbytedata(char mem[], int size); void loadhalfwdata(char mem[], int size);
   void loadworddata(char mem[], int size); void loaddoublewdata(char mem[], int size);
   long long sumbytedata(char mem[], int size); long long sumhalfwdata(char mem[], int size);
   long long sumworddata(char mem[], int size); long long sumdoublewdata(char mem[], int size);
   void printresult(long long bytesum, long long hwsum, long long wordsum, long long dwsum);

   if(argc < 2)
   {
      void usage(char *progname); 
      usage("a7"); 
   }
   size = strtol(argv[1], &blkptr, 10);
   if ((size & 7) != 0) {fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A MULTIPLE OF 8.\n"); exit(1);}
   else if (*blkptr != '\0') {fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A NUMBER.\n"); exit(1);}

   if (size <= 0) {void usage(char *progname); usage("a7"); } 
   if(!(blkptr = getmemblock(size))) {fprintf(stderr, "Memory Allocation Fail\n"); exit(1);}

   srand(1);
   loadbytedata(blkptr, size); bytesum = sumbytedata(blkptr, size);
   loadhalfwdata(blkptr, size); halfwsum = sumhalfwdata(blkptr, size);
   loadworddata(blkptr, size); wordsum = sumworddata(blkptr, size);
   loaddoublewdata(blkptr, size); doublewsum = sumdoublewdata(blkptr, size);
   printresult(bytesum, halfwsum, wordsum, doublewsum);
    
   free(blkptr);
   exit(0);   
}


/* Design a module that prints out the directory and the program 
name to the console and then proceeds to terminate the entire program. 
This is a method where it will proceed to take the program name 
and its directory and print it out to the console using the fprintf 
command. After this is done it will proceed to terminate the program 
using the exit(1). This will completely end the program and tell 
you your directory. 
*/
void usage (char *progname)
{
   fprintf(stderr, "./%s <blocksize>\n", progname); exit(1);
}


/* Design a module where the it allocates the bytes to a memory block 
and proceeds return the pointer of the memory block. It is important 
to make sure that the memory block cannot fail. 
This is a method where it will proceed to check if the memory block can 
store the data. If it is found to be true the memory block will store the
data of the bytes and then proceed to return the pointer of the memory 
block in order to send the required data back to the method that called. 
*/

char *getmemblock (int size)
{
   char *str;
   str = (char *) malloc(size);
   return str;
}


/* Design a module that takes in a char array and the size of that 
   array then fills that array with 7-bit, size int values, that 
   uses a random number generator.
   Itterating through the array using a *(char *) to set the value
   using a random number generated in the for loop. Then using the 
   bit-wise operator '&' with 0x7F in order to change the first bit
   to a 0. This continues until we go through the size of the array.
*/
void loadbytedata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      *((char *) & mem[i]) = rand() & 0x7F; 
   }
}


/* Design a module that takes in a char array and the size of 
   that array then fills that array with 15-bit, size/2 int values,
   that uses a random number generator. 
   Itterating through the array using a *(short in *) to set 
   the value using a random number generated in the for loop. 
   Then using the bit-wise operator '&' with 0x7FFF in order to 
   change the first bit to a 0. This continues until we go through
   the size/2 of the array.
*/
void loadhalfwdata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i += 2)
   {
      *((short int *) & mem[i]) = rand() & 0x7FFF;    
   } 
}


/* Design a module that fills up the memory array with
   random 31-bit, size / 4 int values using random number
   generator.
   loops thorugh the memory array (mem[]) size times, with
   each interation adding 4 to i to match the byte size of
   word (int). the actual value of mem[i] is set to a random
   value that has its sign bit removed with bitwise operations.
*/
void loadworddata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i += 4)
   {    
      *((int *) & mem[i]) = rand() & 0x7FFFFFFF;   
   }
}

/* Design a module that fills up the memory array with
   random 63-bit, size / 8 int values using random number
   generator.
   loops through the memory array(mem[]) size times, with
   each iteration adding 8 to i to match the byte size of
   double-word (long long). The actual value of mem[i] is 
   set to a random value but becaues it's a long long it 
   needs two rand values to fill it out by filling out 
   the first half with a random int and the rest with
   another random int. This gives a complete random long
   long that you then put into memory.
*/
void loaddoublewdata (char mem[], int size)
{
   int i; 
   for (i = 0; i < size; i += 8)
   {
      *((long long *) & mem[i]) = ((long long) rand() << 31) | rand();   
   }
}

/* Design a module that returns the sum of all the byte 
   data in a char array. Using a long long sum to store 
   the sum of the char array. This module uses a for loop 
   to itterate through the character array and uses a *(char*)
   to get the value of each byte and then adds it to the 
   sum. Once the entire array has been processed the sum 
   is returned.
*/
long long sumbytedata (char mem[], int size)
{
   long long sum = 0; 
   int i;
   for (i = 0; i < size; i++)
   {
      sum += *(char *) & mem[i];   
   }
   return sum;
}

/* Design a module that returns the sum of all the
   halfword data in a char array.
   Using a long long sum to store the sum of the char 
   array. This module uses a for loop to itterate through
   the character array and uses a *(short in*) to get the 
   value of each halfword and then adds it to the sum. 
   Once the entire array has been processed the sum is 
   returned.
*/
long long sumhalfwdata (char mem[], int size)
{
   long long sum = 0;
   int i;
   for (i = 0; i < size; i += 2)
   {
      sum += *(short int*) & mem[i];   
   }
   return sum;
}
 
/* Design a module that finds the sum of the ints
   (with no sign bits, 31-bit values) that are in 
   the memory[].
   Starts a sum outside of the loop, then loops 
   through the memory (mem[]) adding only each int
   value by setting the loop to add 4 to i every 
   interation and casting the mem[i] to int. Returns
   the sum of all ints in the
   memory.
*/
long long sumworddata (char mem[], int size)
{
   long long sum = 0;
   int i;
   for (i = 0; i < size; i += 4)
   {
      sum += *(int *) & mem[i];   
   }
   return sum;
}

/* Design a module that finds the sum of the long
   longs (with no sign bits, 63-bit values) that 
   are in the memory[].
   Starts a sum outside of the loop, then loops 
   thorugh the memory (mem[]) adding only each
   long long value by setting the loop to add 8
   to i every interation and casting the mem[i]
   to long long. Returns the sum of all
   long longs in the memory.
*/
long long sumdoublewdata(char mem[], int size)
{
   long long sum = 0;
   int i;
   for (i = 0; i < size; i += 8)
   {
      sum += *(long long *) & mem[i];   
   }
   return sum;
}

/*Design a module that prints out each sum of data for the following:
bytes, half-words, words, and double-words to the console. 
This is a method where it will proceed to acquire all the sums
previously added up for: bytes, half-words, words, and double-words and 
display them in the console. Upon doing calling each of the sums separately 
and placing them on separate lines the code will finish. 
*/
void printresult(long long bytesum, long long hwsum, long long wordsum, long long dwsum)
{
    fprintf(stderr, "\n%-20s : %-10lld\n", "Sum of bytes", bytesum);
    fprintf(stderr, "%-20s : %-10lld\n", "Sum of half-words", hwsum);
    fprintf(stderr, "%-20s : %-10lld\n", "Sum of words", wordsum);
    fprintf(stderr, "%-20s : %-10lld\n\n","Sum of double-words", dwsum);
}
