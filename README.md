# latte
An online Speech processing engine built on barista. Uses gtkmm for the gui handles.

## barista
Barista is an open-source framework for concurrent speech processing 
developed and maintained by the 
[Signal Analysis and Interpretation Lab](http://sail.usc.edu) (SAIL) at USC.
Barista is a wrapper inturn, on Kaldi. (http://kaldi-asr.org) 

The first step is to do download the source code of barista, from the public repo on github.
## Download barista
     cd /install_directory_path/
     git clone https://github.com/usc-sail/barista.git

latte requires installation of barista. But before installing barista, the following changes are to be made to ensure a smooth run of the system.
## Download latte source files
     cd /top_directory_barista/barista/
     git clone https://github.com/dorbala/latte.git
     cp latte/latte.tar.gz .
     tar xvzf latte.tar.gz
This will update the required files in their respective places. They are also availale to view in latte/ folder.
NOTE: The original finals are available in the latte/ folder with '-orig' extension.

## Download portaudio
One of the main problems you might encounter while running is the setting up of portaudio.
Before starting the build, I recommend downloading portaudio from the http://portaudio.com/download.html and replacing the file at barista/tools/kaldi/tools.
If you are doing this you'd need to change the install_portaudio.sh to the apt tgz name under barista/tools/kaldi/tools.

## Dependencies
Latte requires gtkmm3 library, if that isn't already installed on your system, please do.
    sudo apt-get install gtkmm-3.0-dev

## Installing barista
Please read 'README.md' file under the top level barista folder and 
follow the instructions to setup barista and required libraries.

## Running latte
    cd barista/
    make install
    cd barista/egs/live
    ./run.sh
    
## Possible errors while running
Might fail if the barista/egs/models are not set up. 
Please make sure the models directory is rightly given in barista/egs/live/conf/actors.ini or you can get them from barista git too.

## Implementation Notes
When run, a dialog pops up that lets the user choose a text file to be processed.
The text in the file will be displayed line by line.
The user is expected to read out the lines displayed. (sometimes, prompted to repeat the lines)
When the program detects that the line is processed, it changes the display and puts out the next line from the file.

Eventually, a file 'report.txt' contains the original and decoded lines as processed by the GMM decoder.

## Caveats
The way the program runs right now is through continually checking if the number of received words
is equal to the number of words displayed. If yes, then it writes to the output file both the received and the 
displayed text.
This is not a very smooth implementation and can be improvised.

## Kaldi Language Models
To run speech recognition, the program requires trained language and acoustic models.
For the demo purpose, already available and trained models are used for running this program.
If the user wants, he can give his own models by specifying them at barista/egs/live/conf/actors.ini

## Pending Work
Huge scope for improvisation. 
- Detecting the silences and transitioning smoothly
- Word error reports
- Reading pdfs will be added in the next version

AUTHOR: Shyama Dorbala (dspshyama@gmail.com)
