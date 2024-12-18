#ifndef ASSISTX_CORE_INTERFACE_H
#define ASSISTX_CORE_INTERFACE_H


class CoreAssistantInterface {
public:
    virtual void initialize() = 0;

    virtual void executeProcessing() = 0;

    virtual ~CoreAssistantInterface() = default;
};

#endif //ASSISTX_CORE_INTERFACE_H
