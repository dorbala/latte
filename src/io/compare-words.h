#ifndef BARISTA_COMPARE_WORDS_H_
#define BARISTA_COMPARE_WORDS_H_

#include "base/module-base.h"
#include <gtkmm.h>

/*

Gets input from both gmm decoder and command line ifc.
gmm decoder -> sends decoded words
command line ifc -> sends 



*/




class CompareWords : public ModuleBase {
public:
  CompareWords(const std::string& name_, 
                       const cppa::group_ptr& subscribers_, 
                       const boost::property_tree::ptree& config) :
    ModuleBase(name_, subscribers_) {    
    decode_file = config.get<std::string>(name + ".decode_filename");
    running_state = Run();
  }
  
  cppa::behavior Run();

private:
  std::string decode_file;
};

#endif
