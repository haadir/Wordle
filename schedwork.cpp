

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, vector<size_t> shiftsRemain, DailySchedule& sched,int row, int col);
bool isValid (int row, int col, DailySchedule& sched, const AvailabilityMatrix& avail);
// int shiftCount (int row, int col, DailySchedule& sched);


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

    //might need to change
    
    //vector containing how many shifts remain for each worker
    // vector<size_t> shiftsRemain;
    // for (unsigned int i = 0; i < avail[row].size(); i++) {
    //     shiftsRemain.push_back(maxShifts);
    // }
		// for (unsigned int i = 0; i < avail.size(); i++) { //# of days
		// 	for (unsigned int j = 0; j < dailyNeed; j++) { //# of workers needed per day
		// 		sched[i][j] = INVALID_ID;
		// 	}
		// }
		vector<Worker_T> worker(dailyNeed,INVALID_ID);
    vector<size_t> shiftsRemain(avail[0].size(), maxShifts); 
		//initialize sched matrix
    for (size_t i = 0; i<avail.size(); i++){
        sched.push_back(worker); 
    }

    return helper(avail, dailyNeed, shiftsRemain, sched, 0, 0);
}

bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, vector<size_t> shiftsRemain, DailySchedule& sched, int row, int col) {
    
    //if done
    //if (col == dailyNeed) return true;
		if (row == sched.size()) {
			return true;
		}
		
    //loop thru each row/worker and check their availabity
    for(unsigned int i = 0; i < avail[row].size(); i++) {
			//check if valid
			if (isValid(row, i, sched, avail)) {
				if (shiftsRemain[i] > 0) {
					sched[row][col] = i;
					shiftsRemain[i]--;
					if (col == sched[row].size()-1) {
						if (helper(avail, dailyNeed, shiftsRemain, sched, row + 1, 0)) return true;
					}	
					else if (col < sched[row].size()) {
						if (helper(avail, dailyNeed, shiftsRemain, sched, row, col + 1)) return true;
					}	
					sched[row][col] = INVALID_ID;
					shiftsRemain[i]++;
				}
			}
		}
		return false;
}

bool isValid (int row, int col, DailySchedule& sched, const AvailabilityMatrix& avail) {

		//cout << "VALID CALLED" << endl;
		//check if they are in avail
		// int worker = sched[row][col];
		if (avail[row][col] == 1) {
			//cout << "VALID END T" << endl;
			return true;
		}
		//cout << "VALID END F" << endl;
		return false;


		// 	//check if same person exists in same row
		// 	for (unsigned int i = 0; i < col; i++) {
    //     if (sched[currDay][i] == worker) return true;
				
    // 	}

		// }

		// //check if total time on sched exceeds max shifts
		// if (shiftCount(row, col, sched)) {

		// }

    // return false;
}

// int shiftCount (int row, int col, DailySchedule& sched) {

// }

//change isValid
//check rows and cols of sched if its greater maxShifts then return false

// if(row == 9) return true;
// if( board[row][col] == 0 ){
//     for(int i = 1; i <= 9; i++) {
//         board[row][col] = i;
//         if(isValid(row, col)) {
//             if(col == 8) { if(solveHelper(row + 1, 0) == true) return true; }
//             else { if(solveHelper(row, col + 1) == true) return true; }
//         }
//     }
//     board[row][col] = 0;
// } else {
//     if(col == 8) { if(solveHelper(row + 1, 0) == true) return true; }
//     else { if(solveHelper(row, col + 1) == true) return true; }
// }
// return false;



