#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h> 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
// Below helps with wait
#include <sys/types.h>
#include <sys/wait.h>
// using ofstream constructors.
#include <iostream>
#include <fstream>  
#include <signal.h>

using namespace std;

int main(int argc, char** argv) 
{

// Pipe declarations
int gentoPyPipe[2];
int pytoCPP[2];


// Pipe instantiations
pipe(gentoPyPipe);
pipe(pytoCPP);


// Children declarations
pid_t firstChild, secondChild, thirdChild, fourthChild;

// savedstdin/out/err

int savedstdin = dup(0);
int savedstdout = dup (1);
int savedstderr = dup (2);

// how long should we wait based on cmd line wait arg
//=======================================================
std::string l = "-l";

 
int secWait = 0;

// for (int k=1; k < argc; k+=2)// arguments times (less 'main' arg)
// {
//   if (argv[k] == l)
//   { 
//     secWait = atoi(argv[k+1]);
//     if (secWait == 0)
//     {
//       secWait = 5; // default if atoi errors
//     }
//   }
// }


if (secWait == 0)
{
  // cout << "oops" << endl;
  secWait = 5; // standard default if unspecified
}
else if (secWait < 5)
{
  secWait = 5; // reset to default
}
// ======================================================


firstChild = fork();
if(firstChild > 0)
{// In parent 
    // waitpid (firstChild, NULL, 0); // wait for firstChild to complete
    // sleep( 1 ); // wait for rgen
    // create second child here
    // std::cout<<"is this parent (after 1) visible?"<<endl;
    // std::cout<<"giving birth to child #2"<<endl;

    secondChild = fork();
    if(secondChild > 0)
    {// In parent
      // Probably CAN'T wait for this
      // waitpid (secondChild, NULL, 0); // wait for secondChild to complete (Python stay r)
      // sleep( 1 ); // wait 1 second for python
      // create third child here
      // std::cout<<"is this parent (after 2) visible?"<<endl;
      usleep( 100000 );// give everything a bit of time to complete
      // std::cout<<"giving birth to child #3"<<endl;
      // kill(secondChild, SIGKILL);

      thirdChild = fork();
      if(thirdChild > 0)
      {// In parent
        // waitpid (thirdChild, NULL, 0); // wait for thirdChild to complete
        // sleep ( 1 ); // wait 1 second for C++
        // create fourth child here

        // std::cout<<"is this parent (after 3) visible?"<<endl;
        // std::cout<<"giving birth to child #4"<<endl;

        fourthChild = fork();
        if(fourthChild > 0)
        {// In parent
          // waitpid (fourthChild, NULL, 0); // wait for fourthChild to complete
          // NOTE: These sleep begins when the corresponding child is made, not before
          sleep( secWait ); // wait 5 seconds for user input (was 5)
          
          // std::cout<<"is this parent (after 4) visible?"<<endl;

          // if (cin.eof()){
          //     // death for all children
          //     std::cout<<"taking childrens' lives"<<endl;
              
          //     kill(fourthChild, SIGKILL);
          //     kill(thirdChild, SIGKILL);
          //     kill(secondChild, SIGKILL);
          //     kill(firstChild, SIGKILL);
              
          //     std::cout<<"children are dead"<<endl;
          //   }
            // control returns to outermost scope from here (in main)


        }
        else if(fourthChild < 0)
        {// error
          std::cerr<< "fork fourthChild failed\n"<< std::flush;
          return 0;
        }
        else
        {// In fourthChild (usr input) *WRITER*
          // wait for rgen and python to finish before running
          // sleep( 3 ); // wait 3 seconds till program reaches here
          // risk it for the biscuit


          // std::cout<<"enter shortest path command (you have 5 seconds):"<<endl;
          // std::cout<< "thank You Lord thirdChild has executed successfully" << endl;
          // std::cout<< "thank You Lord reached fourthChild successfully" << endl;
          // std::cout<< "Note: Enter shortest path input now!" << endl;
          // sleep( 5 ); // wait 5 seconds for user input

          // close appropriate pipeEnds
          close (gentoPyPipe[0]); // ReadEnd
          close (gentoPyPipe[1]); // WriteEnd also

          // pytoCPP
          close (pytoCPP[0]); // ReadEnd 
          // close (pytoCPP[1]); // WriteEnd also (potentially)


          // redirect stdout to the pipe

          // stdout replaced by WriteEnd of pipeEnds1 (MOST HELPFUL)
          // Hence what would go to stdout, now goes to WriteEnd of pipe1

          /* I.e. Connect the write end of the pipe to standard output. */
          dup2(pytoCPP[1], STDOUT_FILENO);


          while (true)
          {
            std::string input;
            getline (std::cin,input);

            

            if (input != ""){
              std::cout<< input << std::endl;
            }

            // std::cout << "is sleep reached by usr input" <<endl;
            int x = secWait - 2;
            sleep( x ); // ( secWait -2 );// - 2 or 1 ); // (was 4) (changed to 3 by def.) 5 seconds to enter input  // apply l seconds here manditorily

            if (!cin.eof())
            {
              continue;
            }
            else
            {
              break;
            }
            
            //sleep (2);
            sleep( secWait - x );
            // temp
            // sleep (3); // arbitrary (uncoordinated)
            // break;
          }          


          close (pytoCPP[1]); // WriteEnd
          
          //reset
          dup2(savedstdout, STDOUT_FILENO);
          // std::cout<< "fourthChild complete" << endl;
          // std::cout<< "heading to parent" << endl;
        }// End fourthChild

      }
      else if(thirdChild < 0)
      {// error
        std::cerr<< "fork thirdChild failed\n"<< std::flush;
        return 0;
      }
      else
      {// In thirdChild (C++) *READER*

      // wait for rgen and python to finish before running
        // sleep( 2 ); // wait 3 seconds
        // risk having c++ running and waiting for input
        // worked

        // std::cout<< "thank You Lord secondChild has executed successfully" << endl;
        // std::cout<< "thank You Lord reached thirdChild successfully" << endl;

        // close appropriate pipeEnds
        // unused pipes
        // =====================================
        // gentoPyPipe
        close (gentoPyPipe[1]); // WriteEnd 
        close (gentoPyPipe[0]); // ReadEnd also
        // =====================================

        // used pipe
        // pytoCPP
        close (pytoCPP[1]); // WriteEnd 
        // close (pytoCPP[0]); // ReadEnd also (Potentially)


        // redirect stdin from the pipe (pytoCPP)

        // stdin replaced by ReadEnd of pipeEnds1 (MOST HELPFUL)
        // Hence what would go to stdin, now goes to ReadEnd of pipe1

        /* I.e. Connect the read end of the pipe to standard input. */
        dup2(pytoCPP[0], STDIN_FILENO);

        std::string input = "notEmpty";
        while (!cin.eof() || !input.empty())
        {
        system ("./a2-ece650");
        // cout<<"is sleep reached by c++"<<endl;
        input = "";
        cin >> input;
        //sleep(10);
        } 
        // No wait needed until usr input accepted, delay above (maybe just delay for usrinpt)
        // waitpid (firstChild, NULL, 0); // wait for python to complete

        close (pytoCPP[0]); // ReadEnd 

      }// end thirdChild

    }



    else if(secondChild < 0)
    {// error
      std::cerr<< "fork secondChild failed\n"<< std::flush;
      return 0;
    }



    else
    {// In secondChild (PYTHON) *READER* and then *WRITER*

    // waitpid (firstChild, NULL, 0); // wait for rgen to complete

    // wait for rgen to finish before running
    // sleep( 1 );
    // try running even while rgen is working  
      // works

    // std::cout<< "thank You Lord reached secondChild successfully" << endl;

    // close appropriate pipeEnds
    // gentoPyPipe
    close (gentoPyPipe[1]); // WriteEnd 
    // close (gentoPyPipe[0]); // ReadEnd also (Potentially)

    // pytoCPP
    close (pytoCPP[0]); // ReadEnd 
    // close (pytoCPP[1]); // WriteEnd also (Potentially) 




    // redirect stdin from the pipe (gentoPyPipe)

    // stdin replaced by ReadEnd of pipeEnds1 (MOST HELPFUL)
    // Hence what would go to stdin, now goes to ReadEnd of pipe1

    /* I.e. Connect the read end of the pipe to standard input. */
    dup2(gentoPyPipe[0], STDIN_FILENO);



    // redirect stdout to the pipe (pytoCPP)

    // stdout replaced by WriteEnd of pipeEnds1 (MOST HELPFUL)
    // Hence what would go to stdout, now goes to WriteEnd of pipe1

    /* I.e. Connect the write end of the pipe to standard output. */
    dup2(pytoCPP[1], STDOUT_FILENO);


    while (!cin.eof())
    {
    system ("python a1-ece650.py");
    // cout << "is sleep reached by py" << endl;
    // sleep( 10 ); // test if sleep needed
    }


    close (gentoPyPipe[0]); // ReadEnd

    close (pytoCPP[1]); // WriteEnd 


    //reset
    dup2(savedstdout, STDOUT_FILENO);
    dup2(savedstdin, STDIN_FILENO);
    // std::cout<< "secondChild complete" << endl;
    // std::cout<< "heading to thirdChild" << endl;
    // std::cout<< "python finished executing" << endl;



    }

    
    
}
else if(firstChild < 0 )
{
  // Error
  std::cerr<< "fork firstChild failed\n"<< std::flush;
  return 0;
} 
else
{// In firstChild (RGEN) *WRITER*

  // std::cout<< "thank You Lord reached firstChild successfully" << endl;

  // close appropriate pipeEnds
  close (gentoPyPipe[0]); // ReadEnd
  // close (gentoPyPipe[1]); // WriteEnd also (Potentially)

  // pytoCPP
  close (pytoCPP[0]); // ReadEnd 
  close (pytoCPP[1]); // WriteEnd also


  // redirect stdout to the pipe

  // stdout replaced by WriteEnd of pipeEnds1 (MOST HELPFUL)
  // Hence what would go to stdout, now goes to WriteEnd of pipe1

  /* I.e. Connect the write end of the pipe to standard output. */
  dup2(gentoPyPipe[1], STDOUT_FILENO);


  // rgen call
  // ===========================================
  std::string rgenCall = "./rgen";

  for (int i = 1; i < argc; i++)
  {
    rgenCall += " ";
    rgenCall += argv[i];
  }

  while (!cin.eof())
  {
    system(rgenCall.c_str()); // run rgen
    sleep( secWait ); // (was 5)
  }

  


  close (gentoPyPipe[1]); // WriteEnd
  
  //reset
  dup2(savedstdout, STDOUT_FILENO);
  // std::cout<< "firstChild complete" << endl;
  // std::cout<< "heading to secondChild" << endl;
  

}

while (!cin.eof()){
waitpid (firstChild, NULL, 0); // wait for rgen to complete
// waitpid (secondChild, NULL, 0); // wait for rgen to complete
// waitpid (thirdChild, NULL, 0); // wait for rgen to complete
// waitpid (fourthChild, NULL, 0); // wait for rgen to complete
}

while(true)
{
if (cin.eof()){
  // death for all children
  // std::cout<<"taking childrens' lives"<<endl;
  
  kill(fourthChild, SIGKILL);
  kill(thirdChild, SIGKILL);
  kill(secondChild, SIGKILL);
  kill(firstChild, SIGKILL);
  
  // std::cout<<"children are dead"<<endl;
}

}//endWhile

return 0;
}
