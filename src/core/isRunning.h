#ifndef ASSISTX_ISRUNNING_H
#define ASSISTX_ISRUNNING_H

class isRunning {
public:
    //bool GetIsRunning() const {return isRunning;}
    static void startRun() { _isRunning = true; }
    static void stopRun() { _isRunning = false; }

    static bool _isRunning;
};

#endif //ASSISTX_ISRUNNING_H
