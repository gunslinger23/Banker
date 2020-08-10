//
//  Banker.h
//  Banker
//
//  Created by Gunslinger on 2020/8/10.
//  Copyright © 2020 Gunslinger. All rights reserved.
//

#ifndef Banker_h
#define Banker_h

#define MAX_THREAD 100
#define MAX_RESOURCE 100

#define SUCCESS "✅"
#define FAILURE "❌"

typedef int ThreadID;
typedef int ResourceID;

class Banker {
private:
    // resource id
    int resources;
    // thread id
    int threads;
    
    // banker
    int available[MAX_RESOURCE];
    int max[MAX_THREAD][MAX_RESOURCE];
    int allocation[MAX_THREAD][MAX_RESOURCE];
    bool finish[MAX_THREAD];
    
    // return thread need resource
    int need(int thread, int resource) {
        return max[thread][resource] - allocation[thread][resource];
    }
    
    // to finish thread
    // return is finish successful
    bool toFinish(int thread) {
        // check available resource is enough to finish thread
        for (int i = 0; i < resources; i++)
            if (need(thread, i) > available[i])
                return false;
        
        free(thread);
        finish[thread] = true;
        return true;
    }
    
    // check is all thread safe to finish now
    bool isSafe() {
        Banker tmp = *this;
        
        // Try finish
        for (int i = 0; i < threads; i++) {
            if (!tmp.finish[i] && tmp.toFinish(i)) {
                i = -1;
            }
        }
        
        // Check finish
        for (int i = 0; i < threads; i++)
            if (!tmp.finish[i])
                return false;
        return true;
    }
    
    // request resource
    void request(int thread, int resource, int num) {
        if (available[resource] >= num && need(thread, resource) >= num )
        {
            available[resource] -= num;
            allocation[thread][resource] += num;
        }
    }
    
    // free thread resource
    void free(int thread) {
        for (int i = 0; i < resources; i++) {
            available[i] += allocation[thread][i];
            allocation[thread][i] = 0;
        }
    }
    
public:
    Banker() : resources(0), threads(0) {
    }
    
    ResourceID RegResource(int avail) {
        int index = resources++;
        available[index] = avail;
        return static_cast<ResourceID>(index);
    }
    
    ThreadID RegThread() {
        int index = threads++;
        finish[index] = false;
        memset(max[index], 0, sizeof(max[index]));
        memset(allocation[index], 0, sizeof(allocation[index]));
        return static_cast<ThreadID>(index);
    }
    
    void SetMaxResources(ThreadID thread, ResourceID resource, int maxResource) {
        max[thread][resource] = maxResource;
    }
    
    bool RequstResource(ThreadID thread, ResourceID resource, int num) {
        if (num > available[resource] || num > need(thread, resource))
            return false;
        
        // Check first
        if (!isSafe())
            return false;
        
        // Try request in temp
        Banker tmp = *this;
        tmp.request(thread, resource, num);
        if (!tmp.isSafe())
            return false;
        
        // Now we can request resource 😄
        request(thread, resource, num);
        return true;
    }
    
    bool IsSafe() {
        return isSafe();
    }
    
    // For test 😍
    void Perform(ThreadID thread, ResourceID resource, int num) {
        std::printf("Thread %d request resource %d(%d) %s\n", thread+1, resource+1, num, RequstResource(thread, resource, num) ? SUCCESS : FAILURE);
    }
};

#endif /* Banker_h */
