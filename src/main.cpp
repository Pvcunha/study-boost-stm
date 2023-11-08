#include <iostream>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>

namespace sc = boost::statechart;

struct EvCount : sc::event<EvCount> {};

struct Active;

struct Counter : sc::state_machine< Counter, Active > {};

struct Odd;
struct Even;

struct Active : sc::simple_state< Active, Counter, Even > {
    public:
        Active(): value(0) { std::cout << "Enters active\n"; };
        ~Active() { std::cout << "exit Active\n"; }

        int getValue() const { return value; }
        int &getValue() { return value; }
    private:
        int value;
};

struct Even: sc::simple_state<Even, Active> {
    public:
        typedef sc::transition< EvCount, Odd >reactions;
        Even() { std::cout << "I'm even!\n"; }
        ~Even() { context< Active >().getValue() += 1; }
};

struct Odd: sc::simple_state< Odd, Active > {
    public:
        typedef sc::transition< EvCount, Even > reactions;
        Odd() { std::cout << "I'm odd :(\n"; }
        ~Odd() { context< Active >().getValue() += 1 ; }
};



int main() {

    Counter machine;
    machine.initiate();
    machine.process_event( EvCount() );
    return 0;
}
