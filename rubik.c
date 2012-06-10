/* Author Sam Muir
3/23/2010 */
#include "cube.h"
#include "middle.h"
#include "top.h"
#include "finalize.h"
#include "start.h"
#include <stdlib.h>

unsigned char solve(void);
void to_sensor(void);


unsigned char main(void){
	unsigned char solve_code, m;
	unsigned long int n, soln_lengths[100];
	srand(5464651);
	//from_sensor = whatever
	for(n=0; n<100; n++) soln_lengths[n] = 0;
	for(n=0; n<10; n++){
		set_bottom(5);
		read_cube();
		for(m=0;m<50;m++){
			turn_face(rand() % 18);
		}
		to_sensor();
		solve_code = solve();
		if(solve_code != 0){
			solve_code = 0;
		} else {
			soln_lengths[bestsolution_length]++;
		}
	}
	return (solve_code != 0);
}

unsigned char solve(void){
	unsigned char j,k,l,m, good;
	bestsolution_length = 100;
	if(sanity_check_colors()==0) return 1;		//check color counts.
	for(j=0; j<6; j++){
		for(l=0; l<19;l++){
			for(m=0;m<19;m++){
				set_bottom(j);		//set which side to consider the bottom
				read_cube();		//read colors into corner/edge arrays.
				if(j==0 && l==0){
					if(sanity_check_pieces()==0) return 2;		//check pieces the first time.
				}
				solution_pos = 0;

				if(l < 18) {
					turn_face(l);		//initial face turn.
					if(m < 18){
						if((l%6)!=(m%6)) turn_face(m);	//secondary face turn.
						else continue;
					}
				}
				else {
					m = 19;		//Only look at option with no sides initially turned once.
				}

				cross_bottom();			//solve the cross of colors on the bottom. Each of these 4 edges should also match other side it touches
				middle();				//solve bottom corner pieces and middle edge pieces.
				if(top_color()==1) return 3;	//make top side all the correct color
				top_sides();					//finish cube, making top pieces move to correct places.
				trim_solution(j);				//trim any extra moves made along the way, convert moves to have correct bottom.
				trim_solution(5);				//Trim again, in case more moves can be trimmed (possible)
				good = check_solution();		//Check to see if cube is solved.
				if(good == 1){
					if(solution_pos < bestsolution_length || j==0){
						for(k=0;k<solution_pos;k++){		//This is the best solution so far. Save it.
							bestsolution[k] = solution[k];
						}
						bestsolution_length = solution_pos;
					}
					if(bestsolution_length < 13){				//a solution less than 12 moves is good enough. stop solving.
						bestsolution[bestsolution_length] = 20;	//signal last move.
						return 0;
					}
				}	
			}//Halley's comment (hope you find that pun funny. doubt anyone will read this anyway.)
		}
	}
	bestsolution[bestsolution_length] = 20;	//Signal last move
	if(bestsolution_length != 100) return 0;	//No solution found. Oh no!
	else return 4;
}

void to_sensor(void){		//for debugging only. converts corner and edge arrays to 6*3*3 color array
	from_sensor[0][1][1] = 0;
	from_sensor[1][1][1] = 1;
	from_sensor[2][1][1] = 2;
	from_sensor[3][1][1] = 3;
	from_sensor[4][1][1] = 4;
	from_sensor[5][1][1] = 5;
	from_sensor[0][0][0] = corners[1][0];
	from_sensor[0][0][2] = corners[2][0];
	from_sensor[0][2][0] = corners[0][0];
	from_sensor[0][2][2] = corners[3][0];
	from_sensor[0][0][1] = edges[2][0];
	from_sensor[0][1][0] = edges[1][0];
	from_sensor[0][1][2] = edges[3][0];
	from_sensor[0][2][1] = edges[0][0];

	from_sensor[5][0][0] = corners[4][0];
	from_sensor[5][0][2] = corners[7][0];
	from_sensor[5][2][0] = corners[5][0];
	from_sensor[5][2][2] = corners[6][0];
	from_sensor[5][0][1] = edges[8][0];
	from_sensor[5][1][0] = edges[9][0];
	from_sensor[5][1][2] = edges[11][0];
	from_sensor[5][2][1] = edges[10][0];

	from_sensor[1][0][0] = corners[0][1];
	from_sensor[1][0][2] = corners[3][1];
	from_sensor[1][2][0] = corners[4][1];
	from_sensor[1][2][2] = corners[7][1];
	from_sensor[1][0][1] = edges[0][1];
	from_sensor[1][1][0] = edges[4][0];
	from_sensor[1][1][2] = edges[7][0];
	from_sensor[1][2][1] = edges[8][1];

	from_sensor[3][0][0] = corners[5][1];
	from_sensor[3][0][2] = corners[6][1];
	from_sensor[3][2][0] = corners[1][1];
	from_sensor[3][2][2] = corners[2][1];
	from_sensor[3][0][1] = edges[10][1];
	from_sensor[3][1][0] = edges[5][0];
	from_sensor[3][1][2] = edges[6][0];
	from_sensor[3][2][1] = edges[2][1];

	from_sensor[2][0][0] = corners[1][2];
	from_sensor[2][0][2] = corners[0][2];
	from_sensor[2][2][0] = corners[5][2];
	from_sensor[2][2][2] = corners[4][2];
	from_sensor[2][0][1] = edges[1][1];
	from_sensor[2][1][0] = edges[5][1];
	from_sensor[2][1][2] = edges[4][1];
	from_sensor[2][2][1] = edges[9][1];

	from_sensor[4][0][0] = corners[3][2];
	from_sensor[4][0][2] = corners[2][2];
	from_sensor[4][2][0] = corners[7][2];
	from_sensor[4][2][2] = corners[6][2];
	from_sensor[4][0][1] = edges[3][1];
	from_sensor[4][1][0] = edges[7][1];
	from_sensor[4][1][2] = edges[6][1];
	from_sensor[4][2][1] = edges[11][1];
}