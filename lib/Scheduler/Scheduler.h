#pragma once

#include <Arduino.h>
#include <Stepper.h>
#include "config.h"

// Default id to return if no room in jobs array to add to
constexpr char NO_FREE_ROOM = -1;

class Scheduler {
    using Callback = void (*)();

    public:
        // Construct a scheduler
        Scheduler();
        
        // Create a repeating job, runs cb fn. Returns job id
        int every(uint32_t interval, Callback cb);

        /* JOB CONTROL UTILS */
        // Remove a repeating job
        void cancel(int id); 

        // Temporarily enable/pause a job from executing its cb
        void setEnable(int id, bool enable); 

        // Change interval a job runs at
        void setInterval(int id, uint32_t newInterval);
        
        // Perform scheduling execution
        void run();

    private:
        struct Job {
            // TODO: Check overflow requirements
            uint32_t interval = 0;  // how often to run in milliseconds
            uint32_t last     = 0;  // time when last run
            Callback cb       = nullptr; // function to execute
            bool     enabled  = false; // is paused or not?
        };

        Job _jobs[MAX_JOBS];

        static bool isIDValid(int id);
};