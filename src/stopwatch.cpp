#include <iostream>
#include <ctime>
#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>

namespace sc = boost::statechart;

struct EvStartStop : sc::event< EvStartStop > {};
struct EvReset : sc::event< EvReset > {};


struct IElapsedTime {
    virtual double ElapsedTime() const = 0;
};

struct Active;
struct StopWatch : sc::state_machine< StopWatch, Active > {
    double ElapsedTime() const {
        return state_cast< const IElapsedTime & >().ElapsedTime();
    }
};

struct Stopped;

// Active eh um estado que esta no contexto de stop watch
// e possui um estado inicial interno que eh o terceiro parametro (stopped)
struct Active : sc::simple_state < Active, StopWatch, Stopped > {
    public:
        typedef sc::transition< EvReset, Active > reactions;
        Active () : elapsedTime_( 0.0 ) { std::cout << "Entrei em Active\n";}
        ~Active () { std::cout << "Saindo de Active\n";}

        double getElapsedTime() const { return elapsedTime_; }
        double &getElapsedTime() { return elapsedTime_; }
    private:
        double elapsedTime_;
};

// Running eh um simple state que tem como contexto o estado Active
struct Running : IElapsedTime, sc::simple_state< Running, Active > {
    public:
        // um estado pode definir um numero arbitrario numero de "reacoes"
        // uma transicao consiste no evento e para qual estado sera o seguinte
        typedef sc::transition< EvStartStop, Stopped > reactions;
        Running() : startTime_( std::time(nullptr) ) { std::cout << "Entrando em Running\n"; }
        ~Running() { 
            std::cout << "Saindo de running\n" << std::difftime(std::time(nullptr), startTime_); 
            context< Active >().getElapsedTime() = ElapsedTime();
        }
        virtual double ElapsedTime() const {
            return context< Active >().getElapsedTime() + std::difftime( std::time( nullptr ), startTime_);
        }
    private:
        std::time_t startTime_;

};

struct Stopped : IElapsedTime, sc::simple_state< Stopped, Active > {
    typedef sc::transition< EvStartStop, Running > reactions;
    Stopped() { std::cout << "Entrando em Stopped\n"; }
    ~Stopped() { std::cout << "Saindo de Stopped\n"; }

    virtual double ElapsedTime() const {
        return context< Active >().getElapsedTime();
    }
};


