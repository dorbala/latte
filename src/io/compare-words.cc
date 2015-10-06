#include "compare-words.h"
#include <ctime>
#include <fstream>
#include <vector>
#include <pthread.h>
#include "namespace_test.h"

using namespace std;
using namespace cppa;

bool bar::newSignal=0;
string newLine;
std::vector<std::string> sentences; 
int num_words;

class myWindow: public Gtk::Window
{
    public:
        myWindow();
        virtual ~myWindow() {};
 
    protected:
        Gtk::Label myLabel;
        void myDisplay();
};

myWindow::myWindow() :
        myLabel()
{
    void myDisplay();

    set_title("Read out this line please.");
    add(myLabel);

    myLabel.show();
    Glib::Thread::create(sigc::mem_fun(*this, &myWindow::myDisplay), true);
}

void myWindow::myDisplay()
{
    myLabel.set_text(newLine);
    while (true) 
	if (bar::newSignal==0) 
		sleep(1);
	else {
		myLabel.set_text(newLine);	
		sleep(1);
		bar::newSignal=0;
	}

}

void show_window() {

    myWindow my_window;
    Gtk::Main::run(my_window);

}


behavior CompareWords::Run(){
  return (
    on<atom("PROCESS"), string >() >> [=](string filename) {
      aout << "Usage: press enter to start processing." << endl;
      char c = cin.get(); 


      /* read from file and store sentences into a vector */
      ifstream fh;
      fh.open(filename);
      sentences.clear();
      std::string line, line_split, buffer;
      std::stringstream lineStream;
      
      if (fh.is_open()) {
      	while ( getline (fh,line)) {

	    buffer.append(line);

	    line.clear();
	    line = buffer;
	    buffer.clear();

            lineStream.str(line);	

      	    while ( getline (lineStream,line_split,'.') ) {
		if (line.substr(line.length()-line_split.length(), line_split.length()).compare(line_split) == 0) { 
			buffer = line_split;
		 	buffer.append(" ");	
		} else {
		   sentences.push_back(line_split);
		   cout << sentences.at(sentences.size()-1) << endl;
		}
	    }
	    lineStream.clear();
	}
        fh.close();
      }

    if (Glib::thread_supported())
        Glib::thread_init();
    else
    {
        cerr << "Threads aren't supported!" << endl;
        exit(1);
    }

    std::thread t(show_window);

    num_words = 0;
    newLine.clear();
    int j=0; 
    newLine = sentences.at(j);

    /* write to a file line by line */
    ofstream decode_fh;
    decode_fh.open( (*this).decode_file, ios_base::app);
    decode_fh << "Original: " << newLine << endl;
    decode_fh.close();

    stringstream tempStream;
    string temp_str,temp2;
    tempStream.str(newLine);

    while ( getline(tempStream,temp_str,' ')) num_words++; 
    tempStream.clear();
    temp_str.clear();

    while(j<sentences.size()) {

       	  aout << " ++  " << name << ": Sending toggle. " << endl;
          send(subscribers, atom("TOGGLE"));

	  aout << " ++ " << name << ": Sleeping... " << endl;
   	  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
       	  aout << " ++  " << name << ": Sending toggle. " << endl;
          send(subscribers, atom("TOGGLE"));

	  cout << "# of words in current line: " << num_words << endl;		  

	  if (num_words <= bar::decoded_words && num_words != 0) {

		bar::newSignal=1;
		num_words = 0; // clear the number of words stored from previous line
	  	j++; // move to the next sentence 
	  	newLine.clear();
	  	newLine = sentences.at(j);
		
		/* write the current line to report */
    		decode_fh.open(decode_file, ios_base::app);
    		decode_fh << "\nOriginal: " << newLine << endl;
    		decode_fh.close();

		/* count number of words in the current line */
  	  	tempStream.str(newLine);
  	  	while ( getline(tempStream,temp_str,' ')) num_words++; 
  	  	tempStream.clear();
  	  	temp_str.clear();

		/* reset the number of decoded words */
		bar::decoded_words = 0;
	  }
	  else {
		/* insufficient words recorded, display a continue prompt */
		bar::newSignal=1;
	        newLine+= "\nPlease continue reading.. if you finished, read the line again.";
	  }

      }
    },
    on(atom("QUIT")) >> [=]() {
      self->quit(exit_reason::user_shutdown);
    }
  );
}
