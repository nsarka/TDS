
//class Timer { .... public: start()}

class Timer{
    public:
        //Initializes variables
        Timer();

        //Clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the Timer's time
        unsigned int getTick();

        //Checks status of Timer
        bool isStarted();
        bool isPaused();

    private:
        //The clock time when the Timer is started
        unsigned int startTicks;

        //The ticks stored when the timer was paused
        unsigned int pausedTicks;

        //The timer status
        bool paused;
        bool started;
}