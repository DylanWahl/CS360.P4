#include <iostream>
#include <pthread.h>
#include <string>
#include <stdio.h>
#include <queue>
#include <list>
#include <unistd.h>
#include <getopt.h>

using namespace std;

queue<string> handleArgs(int argc, char** argv);
void storeKeyAndValue(string store_key, string value);
void storeKeyAndFileContents(string store_key, string file);
string retrieveKeyValue(string retrieve_key);
string retrieveKeyAndCopyToFile(string retreive_key, string file);

int main(int argc, char** argv)
{
  string store_key = "";
  string retrieve_key= "";
  string value="";
  string file="";
  queue<string> argQueue =  handleArgs(argc,argv);

  //Max for queue is 4 values, since we also store a descriptor before the actual value of the arg
  // E.g. argQueue = ["s", "store_value", 'f', "file_name"]
  
  if(argQueue.empty() || argQueue.size() > 4) //Queue should have at most 4 args, and should not be empty
    {
      cout << endl <<"key-store <--store key> | <--retrieve key> <value | --file file_path> [--help]" << endl;
      exit(EXIT_SUCCESS);
    }
  
  if(!argQueue.empty())
    {
      string first_desc = argQueue.front();
      argQueue.pop();

      // If our first descriptor is a store flag...
      if(first_desc == "s")
	{
	  // The next arg will be the key for the store
	  store_key = argQueue.front();
	  argQueue.pop();

	}
      else if(first_desc == "r")
	{
	  {
	    // The next arg will be the key for the store
	    retrieve_key = argQueue.front();
	    argQueue.pop();
	  }
	  
	}

       // Get the descriptor flag for the second arg
	  string second_desc = argQueue.front();
	  argQueue.pop();
      
      // If it's a value, run storeKeyAndValue
      if(second_desc == "v")
	{
	      value = argQueue.front();
	      argQueue.pop();
	    }
      
      // Or if its a file, run storeKeyAndFileContents
      else if(second_desc == "f")
	    {
	      file = argQueue.front();
	      argQueue.pop();
	    }
    }
  
  if(store_key != "")
    {
      if(value != "")
	{
	  storeKeyAndValue(store_key, value);
	}

      else if(file != "")
	{
	  storeKeyAndFileContents(store_key, file);
	}
    }
  else if(retrieve_key != "")
    {
      // Retrieve
        if(file == "")
	{
	  retrieveKeyValue(retrieve_key); 
	}

	else if(file != "")
	{
	  retrieveKeyAndCopyToFile(retrieve_key, file);
	}
    }
  else
    {
      cerr << "ERROR" << endl;
      exit(EXIT_FAILURE);
    }
  
  exit(EXIT_SUCCESS);
}


queue<string> handleArgs(int argc, char** argv){

  //store, retrieve, and file all require arguments, so are followed by a colon in optString. Help does not require one.
  const char* const optString = "s:r:f:h";
  queue<string> argQueue;
  const option fullOpts[] =
    {
      {"store", required_argument, NULL, 's'},
      {"retrieve", required_argument, NULL, 'r'},
      {"file", required_argument, NULL, 'f'},
      {"help", no_argument, NULL, 'h'}
    };

  while(true)
    {
      const int opt = getopt_long(argc, argv, optString, fullOpts, NULL);
      
      if(opt == -1)
	{
	  return argQueue;
	}

      switch(opt)
	{
	case 'h':
	  {
	    cout << endl <<"key-store <--store key> | <--retrieve key> <value | --file file_path> [--help]" << endl;
	    exit(EXIT_SUCCESS);
	  }
	case 's':
	  {
	    string str = "--file";
	    string arg3(argv[3]); 
	    cout <<"Got command to STORE: " <<  optarg << endl;
	    argQueue.push("s");
	    string store_key = optarg;
	    argQueue.push(store_key);

	    if(arg3.compare(str) != 0 )
	      {
		argQueue.push("v");
		string store_value = argv[3];
		argQueue.push(store_value);
	      }
	    
	    break;
	    
	  }

	case 'r':
	  {
	    cout << "Got command to RETRIEVE: " << optarg << endl;
	    argQueue.push("r");
	    string retrieve_value = optarg;
	    argQueue.push(retrieve_value);
	    break;
	  }

	case 'f':
	  {
	    cout << "Got FILE arg: " << optarg << endl;
	    argQueue.push("f");
	    string file_value = optarg;
	    argQueue.push(file_value);
	    break;
	  }
	  
	default:
	  {
	    // If they didn't add any args, print help signature and exit
	    cout << endl <<"key-store <--store key> | <--retrieve key> <value | --file file_path> [--help]" << endl;
	    exit(EXIT_SUCCESS);
	  }
	}
    }

  return argQueue;
}
  
void storeKeyAndValue(string store_key,string value)
{
  cout << "Reached store Key and Value" << endl;
}
void storeKeyAndFileContents(string store_key,string file)
{
  cout << "Reached store Key and File" <<endl; 
}
string retrieveKeyValue(string retrieve_key)
{
  cout << "reached retrieve Key and Value," << endl; 
}
string retrieveKeyAndCopyToFile(string retreive_key,string  file)
{
  cout << "reached retrieve key and file" << endl;
}
