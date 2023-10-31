#include <iostream>
#include "stopwatch.cpp"
#include <time.h>
// #include <boost/statechart/state_machine.hpp>
// #include <boost/statechart/simple_state.hpp>

// ref
// https://www.boost.org/doc/libs/1_82_0/libs/statechart/doc/tutorial.pdf

/*
namespace sc = boost::statechart;

struct Greeting;

// os parametros dentro do <> indicam a maquina a qual pertence e 
// para onde ela vai ao ser iniciada
struct Machine : sc::state_machine< Machine, Greeting > { };

struct Greeting : sc::simple_state< Greeting, Machine > {
    Greeting() { std::cout << "Hello World!\n";}
    ~Greeting() {std::cout << "Goodbye World\n";}
};

int main() {
    Machine basicMachine;

    basicMachine.initiate();

    return 0;
}
*/

int main () {
    StopWatch myWatch;
    myWatch.initiate();
    std::cout << myWatch.ElapsedTime() << "\n";
    sleep(1);
    myWatch.process_event( EvStartStop() );
    std::cout << myWatch.ElapsedTime() << "\n";
    myWatch.process_event( EvStartStop() );
    std::cout << myWatch.ElapsedTime() << "\n";
    myWatch.process_event( EvStartStop() );
    std::cout << myWatch.ElapsedTime() << "\n";
    myWatch.process_event( EvReset() );
    std::cout << myWatch.ElapsedTime() << "\n";
    return 0; 
}