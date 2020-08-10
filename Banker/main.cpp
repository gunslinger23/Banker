//
//  main.cpp
//  Banker
//
//  Created by Gunslinger on 2020/8/10.
//  Copyright © 2020 Gunslinger. All rights reserved.
//

#include <iostream>
#include "Banker.h"

int main(int argc, const char * argv[]) {
    // Init
    Banker bank;
    ResourceID r1 = bank.RegResource(9);
    ResourceID r2 = bank.RegResource(3);
    ResourceID r3 = bank.RegResource(6);
    ThreadID p1 = bank.RegThread();
    ThreadID p2 = bank.RegThread();
    ThreadID p3 = bank.RegThread();
    ThreadID p4 = bank.RegThread();
    bank.SetMaxResources(p1, r1, 3);
    bank.SetMaxResources(p1, r2, 2);
    bank.SetMaxResources(p1, r3, 2);
    bank.SetMaxResources(p2, r1, 6);
    bank.SetMaxResources(p2, r2, 1);
    bank.SetMaxResources(p2, r3, 3);
    bank.SetMaxResources(p3, r1, 3);
    bank.SetMaxResources(p3, r2, 1);
    bank.SetMaxResources(p3, r3, 4);
    bank.SetMaxResources(p4, r1, 4);
    bank.SetMaxResources(p4, r2, 2);
    bank.SetMaxResources(p4, r3, 2);
    
    // Test request
    // p1
    bank.Perform(p1, r1, 1);
    // p2
    bank.Perform(p2, r1, 5);
    bank.Perform(p2, r2, 1);
    bank.Perform(p2, r3, 1);
    // p3
    bank.Perform(p3, r1, 2);
    bank.Perform(p3, r2, 1);
    bank.Perform(p3, r3, 1);
    // p4
    bank.Perform(p4, r3, 2);
    
    //test
    bank.Perform(p2, r1, 1);
    bank.Perform(p2, r2, 0);
    bank.Perform(p2, r3, 1);
    
    bank.Perform(p1, r1, 1);
    bank.Perform(p1, r3, 1);
    
    bank.Perform(p3, r3, 1);

    return 0;
}
