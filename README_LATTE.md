# latte
An online Speech processing engine built on barista. Uses gtkmm for gui purposes.

## barista
Barista is an open-source framework for concurrent speech processing 
developed and maintained by the 
[Signal Analysis and Interpretation Lab](http://sail.usc.edu) (SAIL) at USC.
Also built on Kaldi (http://kaldi-asr.org) 

Requires installation of barista.

## Installing barista
     cd /install/directory
     git init
     git clone https://github.com/usc-sail/barista.git

Please read 'README.md' file under the top level barista folder and 
follow the instructions to setup barista and required libraries.

## latte source files
     git clone https://github.com/dorbala/latte.git

After cloning, either
   place the individual files in the required repositories in the installed barista repo

Or use the tar file latte.tar.gz under latte:
   cd path/to/latte
   cp latte.tar.gz barista/
   tar -xvf latte.tar.gz

NOTE: it will replace some of the files in the barista repo. The original files will be renamed as *.orig

## Running latte
    cd barista/
    make install
    cd barista/egs/live
    ./run.sh

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
