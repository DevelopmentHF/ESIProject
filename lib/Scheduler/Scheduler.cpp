#include "Scheduler.h"

Scheduler::Scheduler() {

}

// TODO: Store times in permenant memory...
// and which day its on etc.
int Scheduler::every(uint32_t interval, Callback cb) {
    // search for a free space in jobs list and fill it in
    for (int i = 0; i<MAX_JOBS; i++) {
        // a free job is defined by being disabled and with no callback set
        if (!_jobs[i].enabled && _jobs[i].cb == nullptr) {
            // create a new job
            _jobs[i].interval = interval;
            _jobs[i].last = millis();
            _jobs[i].enabled = true;
            _jobs[i].cb = cb;

            return i;
        }
    }

    return NO_FREE_ROOM; // failed to fit the job in.
}

void Scheduler::cancel(int id) {
    if (!Scheduler::isIDValid(id)) {return;}

    _jobs[id] = Job{}; // reset to default state. see Scheduler.h
}

void Scheduler::setEnable(int id, bool enable) {
    if (!Scheduler::isIDValid(id)) {return;}

    _jobs[id].enabled = enable;

    // reset last time of running when reactivating a job
    if (enable) {
        _jobs[id].last = millis();
    }
}

void Scheduler::setInterval(int id, uint32_t newInterval) {
    if (!Scheduler::isIDValid(id)) {return;}

    _jobs[id].interval = newInterval;
}

void Scheduler::run() {
    const uint32_t now = millis();

    // go thru each job, run it :)
    for (int i = 0; i < MAX_JOBS; i++) {
        Job &currentJob = _jobs[i];

        // skip empty or paused jobs
        if (!currentJob.enabled || currentJob.cb == nullptr) {continue;}

        // check timing
        if ((now - currentJob.last) >= currentJob.interval) {
            currentJob.last = now;
            currentJob.cb();
        }

    }
}

bool Scheduler::isIDValid(int id) {
    return !(id < 0 || id >= MAX_JOBS);
}