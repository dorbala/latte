#include "compare-words.h"
#include <ctime>
#include <fstream>
#include <vector>
#include <pthread.h>
#include "namespace_test.h"

using namespace std;
using namespace cppa;
bool bar::hideSig=0;
string newtext;
int j=0;
std::vector<std::string> line_vec; 
int num_words;

class myLabel: public Gtk::Window
{
    public:
        myLabel();
        virtual ~myLabel() {};
 
    protected:
        Gtk::Label m_label;
        string labeltext;
        void myprocess1();
};

myLabel::myLabel() :
        m_label()
{
    void myprocess1();

    set_title("Read out this line please.");
    add(m_label);

    m_label.show();

    Glib::Thread::create(sigc::mem_fun(*this, &myLabel::myprocess1), true);
}

void myLabel::myprocess1()
{
    m_label.set_text(newtext);
    while (true) 
	if (bar::hideSig==0) 
		sleep(1);
	else {
		m_label.set_text(newtext);	
		sleep(1);
		bar::hideSig=0;
	}

}

void run_label() {

    myLabel mylabel;
    Gtk::Main::run(mylabel);

}


behavior CompareWords::Run(){
  return (
    on<atom("PROCESS"), string >() >> [=](string filename) {
      aout << "Usage: press enter to start processing." << endl;
      char c = cin.get(); 
      ifstream fh;
      fh.open(filename);
      line_vec.clear();
      std::string line, line_split, buffer;
      std::stringstream sentence;
      
      if (fh.is_open()) {
      	while ( getline (fh,line)) {
	    buffer.append(line);
	    line.clear();
	    line = buffer;
	    buffer.clear();

            sentence.str(line);	
      	    while ( getline (sentence,line_split,'.') ) {
		if (line.substr(line.length()-line_split.length(), line_split.length()).compare(line_split) == 0) { 
			buffer = line_split;
		 	buffer.append(" ");	
		} else {
		   line_vec.push_back(line_split);
		   cout << line_vec.at(line_vec.size()-1) << endl;
		}
	    }
	    sentence.clear();
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

    std::thread t(run_label);
    stringstream temp;
    string temp_str,temp2;
    ofstream decode_fh;
    
   // for the first time
    num_words = 0;
    newtext.clear();
    newtext = line_vec.at(j);
    decode_fh.open( (*this).decode_file, ios_base::app);
    decode_fh << "Original: " << newtext << endl;
    decode_fh.close();
    temp.str(newtext);
    while ( getline(temp,temp_str,' ')) num_words++; 
    temp.clear();
    temp_str.clear();
    while(true) {
       	  aout << " ++  " << name << ": Sending toggle. " << endl;
          send(subscribers, atom("TOGGLE"));

	  aout << " ++ " << name << ": Sleeping... " << endl;
   	  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
          send(subscribers, atom("TOGGLE"));

	  cout << " current word size: " << num_words << endl;		  
	  if (num_words <= bar::decoded_words && num_words != 0) {
	  	j++;
		bar::hideSig=1;
		num_words = 0;
	  	newtext.clear();
	  	newtext = line_vec.at(j);
    		decode_fh.open(decode_file, ios_base::app);
    		decode_fh << "\nOriginal: " << newtext << endl;
    		decode_fh.close();
  	  	temp.str(newtext);
  	  	while ( getline(temp,temp_str,' ')) num_words++; 
  	  	temp.clear();
  	  	temp_str.clear();
		bar::decoded_words = 0;
          	//send(subscribers, atom("TOGGLE"));
	  }
	  else {
		bar::hideSig=1;
	        newtext+= "\nPlease continue reading.. if you finished, read the line again.";
	  }

      }
    },
    on(atom("QUIT")) >> [=]() {
      self->quit(exit_reason::user_shutdown);
    }
  );
}
