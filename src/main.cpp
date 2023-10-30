#include <iostream>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>

using namespace std;
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