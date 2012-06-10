/* Author Sam Muir
3/23/2010 */
#ifndef _FINALIZE
#define _FINALIZE

#include "cube.h"

unsigned char check_solution(void);
unsigned char convert_move_bottom(unsigned char oldbottom, unsigned char move);
void trim_solution(unsigned char oldbottom);

unsigned char check_solution(void){
			unsigned char good = 1, p;
			if(!(edges[8][0] == 5 && edges[9][0] == 5 && edges[10][0] == 5 && edges[11][0] == 5 && edges[8][1] == 1 && edges[9][1] == 2 && edges[10][1] == 3 && edges[11][1] == 4)) good = 0;
			if(!(edges[4][0] == 1 && edges [4][1] == 2 && edges[5][0] == 3 && edges[5][1] == 2 && edges[6][0] == 3 && edges[6][1] == 4 && edges[7][0] == 1 && edges[7][1] == 4)) good = 0;
			for(p=0;p<4;p++){
				if(corners[p][0] != 0) good = 0;
				if(edges[p][0] != 0) good = 0;
				if(edges[p][1] != (p+1)) good = 0;
				if(p>1){
					if(corners[p][2] != 4) good = 0;
				} else {
					if(corners[p][2] != 2) good = 0;
				}
				if(p==0 || p==3){
					if(corners[p][1] != 1) good = 0;
				} else {
					if(corners[p][1] != 3) good = 0;
				}
			}
			for(p=4;p<8;p++) if(corners[p][0] != 5) good = 0;
			if(corners[4][1] != 1) good = 0;
			if(corners[4][2] != 2) good = 0;
			if(corners[5][1] != 3) good = 0;
			if(corners[5][2] != 2) good = 0;
			if(corners[6][1] != 3) good = 0;
			if(corners[6][2] != 4) good = 0;
			if(corners[7][1] != 1) good = 0;
			if(corners[7][2] != 4) good = 0;
			return good;
}

unsigned char convert_move_bottom(unsigned char oldbottom, unsigned char move){
		//converts a move with a different bottom to bottm = 5 (correct bottom)
		//input can only be clockwise rotations (moves 0-5)
	switch(oldbottom){
		case 5: return move;
		case 4:
			switch(move){
				case 0: return 2;
				case 1: return 1;
				case 2: return 5;
				case 3: return 3;
				case 4: return 0;
				default: return 4;	//case 5 = bottom rotated
			}
		case 2:
			switch(move){
				case 0: return 4;
				case 1: return 1;
				case 2: return 0;
				case 3: return 3;
				case 4: return 5;
				default: return 2;	//case 5
			}		
		case 0:
			switch(move){
				case 0: return 5;
				case 1: return 3;
				case 2: return 2;
				case 3: return 1;
				case 4: return 4;
				default: return 0;	//case 5
			}
		case 1:
			switch(move){
				case 0: return 3;
				case 1: return 0;
				case 2: return 2;
				case 3: return 5;
				case 4: return 4;
				default: return 1;	//case 5
			}
		default:
			switch(move){
				case 0: return 1;
				case 1: return 5;
				case 2: return 2;
				case 3: return 0;
				case 4: return 4;
				default: return 3;	//case 5
			}
	}
}

void trim_solution(unsigned char oldbottom){
	unsigned char i, type, order, j, k, num_removed;
	for(i=0; i<solution_pos; i++){
		type = solution[i] % 6;
		order = (solution[i] / 6) + 1;
		for(j=i+1; j<solution_pos; j++){
			if((solution[j] % 6) != type) break;
			order = (order + (solution[j] / 6) + 1) % 4;
		}
		num_removed = (j-1) - i;
		if(order == 0){
			i--;
			num_removed++;
		} else {
			solution[i] = ((order - 1) * 6) + convert_move_bottom(oldbottom, type);
		}
		if(num_removed > 0){
			for(k=i+1; k<(solution_pos-num_removed);k++){
				solution[k] = solution[k + num_removed];
			}
			solution_pos -= num_removed;
		}
	}


}
#endif