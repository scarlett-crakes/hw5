#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    std::vector<int> currentShifts;
    for(int i = 0; i < avail.size(); i++)
    {
        currentShifts.push_back(0);
        std::vector<Worker_T> workerIDS;
        sched.push_back(workerIDS); //days
        for(int j = 0; j < dailyNeed; j++)
        {
            
            sched[i].push_back(INVALID_ID); 
                
        }
    }
    AvailabilityMatrix new_avail = avail;
    return scheduleHelper(new_avail, dailyNeed, maxShifts, sched, currentShifts, 0, 0);

}

bool scheduleHelper(
    AvailabilityMatrix& avail, // n x k
    const size_t dailyNeed, //d
    const size_t maxShifts, //m
    DailySchedule& sched, std::vector<int> currentShifts, int index_row, int index_col
)
{
    //if schedule rows = n which is avail rows 0 0 0 2 nxd
    //set up
    //cout << index_row << " " << avail.size() << endl;
    if(index_row == avail.size()) 
    {
        return true;
    }
    else if(index_col >= dailyNeed)
    {
      index_col = 0; 
      return scheduleHelper(avail, dailyNeed, maxShifts, sched, currentShifts, index_row+1, index_col);
    }
    for(int i = 0; i < avail[0].size(); i++) //number of k workers
    {
            //cout << index_row << " " << i << endl;
        if(avail[index_row][i] == 1 && currentShifts[i] < maxShifts) 
        {
            //cout << "yay" << endl; 

            sched[index_row][index_col] = i; 
            currentShifts[i] += 1; 
            avail[index_row][i] = 0;
            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, currentShifts, index_row, index_col+1))
            {
              return true;
            }
            avail[index_row][i] = 1;
            currentShifts[i] -= 1; 
            sched[index_row][index_col] = INVALID_ID;
        }
        //make sure it doesn't go over d and updating index correctly
    }
}

