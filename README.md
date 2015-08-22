#cmake-qt5-example
A quick and simple example for using Qt 5 and Cmake.

It is essentially for my own usage, but I'd be happy if it is useful to someone else.
I am open to improvement and contributions.

### usage

    mkdir build
    cd build
    cmake ..
    make
    ./myAplication
    
### hint
Install [entr](http://entrproject.org/)  

cd to "bin" and enter:
```bash
    ls * | entr ./qtCmdline -p
```
Every time "qtCmdline" changes "entr" calls `qtCmdline -q` - nice for testing!
     
