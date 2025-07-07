#pragma once

#include "module.h"
#include "config.h"


class SungrowPidModule : public DeviceModule {
public:
    SungrowPidModule();

    void pre_init() override;
    void pre_setup() override;
    void setup() override;
    void tick() override;

private:
    double integral = 0.0;
    double previous_error = 0.0;
};