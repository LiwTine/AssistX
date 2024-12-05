#ifndef ASSISTX_ISRUNNING_H
#define ASSISTX_ISRUNNING_H

class isRunning {
public:
    //bool GetIsRunning() const {return isRunning;}
    void start() { isRunning = true; }
    void stop() { isRunning = false; }

protected:
    bool isRunning = false;
};

#endif //ASSISTX_ISRUNNING_H
