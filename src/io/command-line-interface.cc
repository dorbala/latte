#include "command-line-interface.h"
#include <ctime>
#include <fstream>
#include <vector>
#include <pthread.h>

using namespace std;
using namespace cppa;

class FileChooser : public Gtk::FileChooserDialog {
public:

    static std::string getFileName() {
        FileChooser dialog("Select file", Gtk::FILE_CHOOSER_ACTION_OPEN);
        kit.run(dialog);
        std::string ret = dialog.chosenFile;
        return ret;
    }
protected:
    static Gtk::Main kit;
    std::string chosenFile;

    FileChooser(const Glib::ustring& title, Gtk::FileChooserAction action = Gtk::FILE_CHOOSER_ACTION_OPEN) :
    Gtk::FileChooserDialog(title, action) {
        chosenFile = std::string("");
        add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
        add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
        signal_response().connect(sigc::mem_fun(*this,
                &FileChooser::on_my_response));
    }

    void on_my_response(int response_id) {
        chosenFile = get_filename();
        hide();
    }
};
Gtk::Main FileChooser::kit(false);

behavior CommandLineInterface::Run(){
  return (
    on(atom("START")) >> [=]() {
      std::string filename = FileChooser::getFileName();
      aout << "File: " << filename << endl;	

      send(subscribers,atom("PROCESS"),filename);
    
    },
    on(atom("REFRESH")) >> [=]() {

	aout << "in refresh! " << endl;

    },
    on(atom("QUIT")) >> [=]() {
      self->quit(exit_reason::user_shutdown);
    }
  );
}
