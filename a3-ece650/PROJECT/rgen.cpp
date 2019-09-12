// an example of reading random numbers from /dev/urandom
// https://stackoverflow.com/questions/35726331/c-extracting-random-numbers-from-dev-urandom
#include <iostream>
#include <fstream>

#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h> 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
// // Below helps with wait
// #include <sys/types.h>
// #include <sys/wait.h>
// // using ofstream constructors.
// #include <iostream>
// #include <fstream>  
#include <stack>

using namespace std;

int coord(int limit) // make it 11
{
  // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
  // (x or y) Random number between -k and k
    // ==================================================
    unsigned int num23 = 10;
    urandom.read((char*)&num23, sizeof(int));
    // std::cout << "Random character: " << num3 << "\n\n";



    // coor = some num 0 to 10
    int coor = num23 % limit + 1;//replace 10 with command line arg + 1

    int forSign = num23 % 2;//replace 10 with command line arg + 1
    if (forSign == 1)
    {
      coor *= -1; // make it negative
    }

    // std::cout << coor <<" is the coordinate \n";
    // ==================================================
    return coor;
}


int main(int argc, char** argv)
{
    // stack to store streets created here
    stack <char> allStreetNames;


    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }


    // Capture command line arguments
  // ==========================================================
  
    // strings
  std::string s = "-s";
  std::string n = "-n";
  std::string l = "-l";
  std::string c = "-c";


  int numbStreets = 0;
  int lineSegs = 0;
  int secWait = 0;
  int coords = 0;

  std::string input;
  //do // rgen do while
  while(!cin.eof())
  {
  for (int k=1; k < argc; k+=2)// arguments times (less 'main' arg)
  {
    if (argv[k] == s) // try strncmp if this fails
    {
      numbStreets = atoi(argv[k+1]);
      // std::cout << "numStreets returns" << numStreets << std::endl;
      if (numbStreets == 0)
      {
        numbStreets = 10; // default if atoi errors
      }
      else if (numbStreets < 2)
      {
        numbStreets = 10; // reset to default
      }

    }
    else if (argv[k] == n)
    {
      lineSegs = atoi(argv[k+1]);
      if (lineSegs == 0)
      {
        lineSegs = 5; // default if atoi errors
      }
      else if (lineSegs < 1)
      {
        lineSegs = 5; // reset to default
      }
    }
    else if (argv[k] == l)
    { 
      secWait = atoi(argv[k+1]);
      if (secWait == 0)
      {
        secWait = 5; // default if atoi errors
      }
      else if (secWait < 5)
      {
        secWait = 5; // reset to default
      }
    }
    else if (argv[k] == c)
    {
      coords = atoi(argv[k+1]);
      if (coords == 0)
      {
        coords = 20; // default if atoi errors
      }
      else if (coords < 1)
      {
        coords = 20; // reset to default
      }
    }
  }

  // DEFAULTS
  // ==================================
  if (numbStreets == 0)
  {
    numbStreets = 10; // standard default if unspecified
  }

  if (lineSegs == 0)
  {
    lineSegs = 5; // standard default if unspecified
  }

  if (secWait == 0)
  {
    secWait = 5; // standard default if unspecified
  }

  if (coords == 0)
  {
    coords = 20; // standard default if unspecified
  }
  // ==================================

  // std::cout << "numStreets is " << numbStreets << "\n"<< std::flush;
  // std::cout << "lineSegs is " << lineSegs << "\n"<< std::flush;
  // std::cout << "secwait is " << secWait << "\n"<< std::flush;
  // std::cout << "coords is " << coords << "\n\n"<< std::flush;

  // ==========================================================


    // // read a random 8-bit value.
    // // Have to use read() method for low-level reading
    // char ch = 'a';
    // urandom.read(&ch, 1);
    // // cast to integer to see the numeric value of the character
    // std::cout << "Random character: " << (unsigned int)ch << "\n";

    // // read another 8-bit value
    // urandom.read(&ch, 1);
    // std::cout << "Random character: " << (unsigned int)ch << "\n";

    // // read a random unsigned int
    // unsigned int num = 42;
    // urandom.read((char*)&num, sizeof(int));
    // std::cout << "Random character: " << num << "\n";


    // read a random 8-bit value.
    // Have to use read() method for low-level reading

    // std::string alpha[2] = {"A","B"};
    
    // char ch = 'a';
    // urandom.read(&ch, 1);
    // // cast to integer to see the numeric value of the character
    // std::cout << "Random character: " << (unsigned int)ch << "\n";

    // // read another 8-bit value
    // urandom.read(&ch, 1);
    // std::cout << "Random character: " << (unsigned int)ch << "\n";

    // // read a random unsigned int
    // unsigned int num = 42;
    // urandom.read((char*)&num, sizeof(int));
    // std::cout << "Random character: " << num << "\n";


    // // read a random unsigned int
    // unsigned int num2 = 10;
    // urandom.read((char*)&num, sizeof(int));
    // std::cout << "Random character: " << num << "\n";

    // std::string s[10];
// "0123456789"
        // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        // "abcdefghijklmnopqrstuvwxyz"
    static const char alphanum[] =
        
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    // num

// (numStreets) Random number between 2 and 10
// ==================================================
unsigned int num3 = 10;
urandom.read((char*)&num3, sizeof(int));
// std::cout << "Random character: " << num3 << "\n\n"<< std::flush;

int numStreets = num3 % numbStreets + 1;// replace 10 with command line arg + 1
if (numStreets<2)
{
  numStreets = 2;
}

long int count = 0;



// altogether
// ==================================================
for (int r = 0; r < numStreets; r++)
{

    



    


    // (x or y) Random number between -k and k
    // ==================================================
    unsigned int num23 = 100;
    urandom.read((char*)&num23, sizeof(int));
    // std::cout << "Random character: " << num3 << "\n\n"<< std::flush;

    // coor = some num 0 to 10
    int coor = num23 % coords + 1;//replace 10 with command line arg + 1

    int forSign = num23 % 2;//replace 10 with command line arg + 1
    if (forSign == 1)
    {
      coor *= -1; // make it negative
    }

    // std::cout << coor <<" is the k coordinate \n"<< std::flush;
    // ==================================================

    

    // (Wait time) Random number between 5 and k
    // ==================================================
    unsigned int num13 = 10;
    urandom.read((char*)&num13, sizeof(int));
    // std::cout << "Random character: " << num3 << "\n\n"<< std::flush;

    int waitTime = num13 % secWait + 1;//replace 10 with command line arg + 1
    if (waitTime<5)
    {
      waitTime = 5;
    }

    // std::cout << waitTime <<" is the wait time \n"<< std::flush;
    // ==================================================


    

    // // TEMP TEST LINE
    // numStreets = 2;

    // std::cout << numStreets <<" is number of streets \n"<< std::flush;
    // ==================================================

    // (streetName) Random letter between 'a' and 'z'
    // ==================================================
    unsigned int num4 = 10;
    urandom.read((char*)&num4, sizeof(int));
    int a = num4 % 26; // replace 27 with command line arg + 1

    // if (a<0)
    // {
    //   a = 0;
    // }

    // std::cout << alphanum[a] <<" is random string \n"<< std::flush;
    // ==================================================


    // (line segments) Random number between 2 and 5
    // ==================================================
    unsigned int num5 = 10;
    urandom.read((char*)&num3, sizeof(int));
    // std::cout << "Random character: " << num5 << "\n"<< std::flush;

    int b = num3 % lineSegs + 1; // replace 6 with command line arg + 1
    if (b<1)
    {
      b = 1;
    }

    // std::cout << b <<" is num line segments \n"<< std::flush;
    // ==================================================


    // (coordRange) Random number between 1 and k (20 by default)
    // ==================================================
    unsigned int num14 = 10;
    urandom.read((char*)&num14, sizeof(int));
    // std::cout << "Random character: " << num3 << "\n\n"<< std::flush;

    int coordRange = num14 % coords + 1;//replace 10 with command line arg + 1
    if (coordRange<1)
    {
      coordRange = 1;
    }

    // std::cout << coordRange <<" is the coordinate range k \n\n"<< std::flush;
    // ==================================================

    // while (!(cin.eof()))
    // {




  unsigned int num7 = 10;
  urandom.read((char*)&num7, sizeof(int));
  int z = num7 % 26; // for 26 letters in alphabet (0 t0 25 array)

  std::cout << "a \"" << alphanum[z] << "\""<< std::flush;

  allStreetNames.push(alphanum[z]);

  // Test line below
  // std::cout << "a \"" << "A" << "\""<< std::flush;
  for (int i = 0; i < b; i++)
  {
    std::cout << " (" << coord(coordRange) <<"," << coord(coordRange) <<")"<< std::flush;
  }
  // usleep(250000);//sleep(1); // sleep(waitTime); // takes long for testing
  std::cout << "\n"<< std::flush;
}
// ==================================================





      // sleep(waitTime);
    // }// endWhile


    



    // char chr = 'a';
    // chr+=x;  // 1
    // // cast to integer to see the numeric value of the character
    // std::cout << "Random character: " << (unsigned int)ch << "\n";



    



    // for (int i = 0; i < len; ++i) {
    //     s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    // }

    // s[len] = 0;

    // generate graph
    std::cout << "g\n"<< std::flush;

    
  
    // getline (std::cin,input);

    sleep(secWait);

    

    // while (true)
    // {
    //   if (cin.eof())
    //   {
    //     input = "end";
    //     break;
    //   }
    //   else
    //   {
    //     continue;
    //   }
    // }
    


    if (allStreetNames.size() > 0)
    {
      // sleep(1); // not necessary
      // pop all streets off the stack
      while(!allStreetNames.empty())
      {
        std::cout << "r \"" << allStreetNames.top() << "\""<< std::endl;
        allStreetNames.pop();
      }
    }




    }// while loop
    

    // close random stream
    urandom.close();
    return 0;
}
