#include "command-line-interface.h"
#include <ctime>
#include <fstream>
#include <vector>
#include <pthread.h>

using namespace std;
using namespace cppa;

class FileDialog : public Gtk::FileChooserDialog {
public:

    static std::string getFileName() {
        FileDialog dialog("Select file", Gtk::FILE_CHOOSER_ACTION_OPEN);
        kit.run(dialog);
        std::string ret = dialog.selectedFile;
        return ret;
    }
protected:
    static Gtk::Main kit;
    std::string selectedFile;

    FileDialog(const Glib::ustring& title, Gtk::FileChooserAction action = Gtk::FILE_CHOOSER_ACTION_OPEN) :
    Gtk::FileChooserDialog(title, action) {
        selectedFile = std::string("");
        add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
        add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
        signal_response().connect(sigc::mem_fun(*this,
                &FileDialog::on_selection));
    }

    void on_selection(int selection_id) {
        selectedFile = get_filename();
        hide();
    }
};
Gtk::Main FileDialog::kit(false);

behavior CommandLineInterface::Run(){
  return (
    on(atom("START")) >> [=]() {
      std::string filename = FileDialog::getFileName();
      aout << "File: " << filename << endl;	

      send(subscribers,atom("PROCESS"),filename);
    
    },
    on(atom("QUIT")) >> [=]() {
      self->quit(exit_reason::user_shutdown);
    }
  );
}
