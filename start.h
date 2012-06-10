/* Author Sam Muir
3/23/2010 */
#ifndef _START
#define _START

#include "cube.h"

void cross_bottom(void);
unsigned char sanity_check_colors(void);
unsigned char sanity_check_pieces(void);

void cross_bottom(void){
	unsigned char i, j, k, bestedgematches, currentedgematches, curredge, bestedge, refedge = 0, edgesdone = 0, turns, face, dest, empty, oldedgesdone, done;
	unsigned char doneedges[4];
	bestedgematches = 0;
	for(i=0; i<4; i++){
		currentedgematches = 0;
		if(edges[i+8][0] == 5){
			currentedgematches++;
			for(j=i+1; j<4; j++){			
				if(edges[j+8][0] == 5){
					curredge = (4 + edges[j+8][1] - edges[i+8][1]) % 4;  //how many edges in a clockwise direction this second edge should be.
					if(curredge == (j-i)) currentedgematches++;  //we have a match!
				}
			}
		}
		if(currentedgematches > bestedgematches){
			bestedgematches = currentedgematches;
			bestedge = i;
		}
	}

	if(bestedgematches > 0) {			//at least one edge matches.
		refedge = (4 + edges[bestedge+8][1] - (bestedge+1)) % 4;		//how many clockwise turns the cross is from being correct.
		doneedges[edgesdone] = bestedge+8;
		edgesdone++;
		for(i=bestedge+1; i<4; i++){
			dest = (( i+1) + refedge) % 4;
			if(dest == 0) dest = 4;
			if(edges[i+8][1] == dest && edges[i+8][0] == 5){  //edge is where we want it to be. freebie.
				doneedges[edgesdone] = i+8;
				edgesdone++;
				continue;
			}
		}
	}

	while(edgesdone < 4){
		oldedgesdone = edgesdone;
		for(j = 0; j < 4; j++){
			if(edges[j+4][1] == 5){		//edge found on middle slice, bottom side facing out.
				if((j==0)||(j==3)){		//non-bottom side faces 'f' face
					dest = (edges[j+4][0] - 1);  //required refedge.
				} else {		//non-bottom side faces 'b' face
					dest = (edges[j+4][0] + 1) % 4; //required refedge.
				}
				if(edgesdone > 0){		//no need to rotate bottom if no match on bottom yet.
					if(refedge > dest) dest +=4;
					if(refedge != dest){			//rotate to required refedge. update.
						turn_face(5 + (6*(dest - refedge - 1)));
						for(i=0; i<edgesdone; i++){
							doneedges[i] -= (dest - refedge);        //Update completed edge array.
							if(doneedges[i] < 8) doneedges[i] += 4;
						}
					}
				} 
				refedge = dest % 4;			//set reference edge to destination (move completed).
				switch(j){
					case 0: turn_face(13); 
							doneedges[edgesdone] = 8;
							break;
					case 1: turn_face(3); 
							doneedges[edgesdone] = 10;
							break;
					case 2: turn_face(15); 
							doneedges[edgesdone] = 10;
							break;
					default: turn_face(1);
							doneedges[edgesdone] = 8;
				}
				edgesdone++;
			} else if(edges[j+4][0] == 5){ // edge found on middle (ud) slice, bottom side facing forward/back
				
				if(j < 2){		//non-bottom side faces 'l' face
					dest = (edges[j+4][1] + 2) % 4;  //required refedge.
				} else {		//non-bottom side faces 'r' face
					dest = (edges[j+4][1]) % 4; //required refedge.
				}
				if(edgesdone > 0){
					if(refedge > dest) dest +=4;
					if(refedge != dest){			//rotate to required refedge. update.
						turn_face(5 + (6*(dest - refedge - 1)));
						for(i=0; i<edgesdone; i++){
							doneedges[i] -= (dest - refedge);        //Update completed edge array.
							if(doneedges[i] < 8) doneedges[i] += 4;
						}
					}
				} 
				refedge = dest % 4;								//update reference value.
				switch(j){
					case 0: turn_face(2); 
							doneedges[edgesdone] = 9;
							break;
					case 1: turn_face(14); 
							doneedges[edgesdone] = 9;
							break;
					case 2: turn_face(4); 
							doneedges[edgesdone] = 11;
							break;
					default: turn_face(16);
							doneedges[edgesdone] = 11;
				}
				edgesdone++;
			}
		}
		if(edgesdone > oldedgesdone) continue;

		for(j = 0; j < 4; j++){
			if(edges[j][1] == 5){						//found a bottom edge on the top face facing out.
				if(edgesdone == 0)  {
					dest = (j+2)%4;		//pick a convinient reference.
					refedge = (4 + edges[j][0] - dest) % 4;
				}
				else dest = (edges[j][0] - refedge + 4) % 4;
				if (dest == 0) dest = 4;		//destination face
				face = j+1;						//face edge was found on.
				if(((dest + face) % 2) == 0){	//current face and destination face are same or opposite.
					k = face + 1;
					if(k > 4) k = 1;
					empty = 1;
					for(i=0; i<edgesdone; i++){			//check one possible face to see if it is a good one to rotate (not yet completed)
						if(doneedges[i] == (k + 7)) empty = 0;
					}
					if(empty == 0){		//clockwise one face from where edge was found is not good to rotate. rotate to opposite one.
						turn_face(12); //rotate top counterclockwise.
						face--;			//update location of current face.
						if(face == 0) face = 4;
					} else {
						turn_face(0); //rotate top clockwise.
						face++;				//update location of current face.
						if(face > 4) face = 1;
					}
				} 			
				//current face and destination face are now orthogonal.
				empty = 1;
				for(i=0; i<edgesdone; i++){			//check one face to see if it is empty for rotating.
					if(doneedges[i] == (face + 7)) empty = 0;
				}
				if((dest == 4 && face == 1) || (dest < face && !(dest == 1 && face == 4))){
					turn_face(face);					//turn current face clockwise
					turn_face(dest + 12);				//turn dest face counterclockwise
					if(empty == 0) turn_face(face + 12); //restore current face if necessary.
				} else {
					turn_face(face + 12);				//turn current face counterclkwise
					turn_face(dest);					//turn dest face clockwise
					if(empty == 0) turn_face(face);		 //restore current face if necessary
				}
				doneedges[edgesdone] = dest + 7;
				edgesdone++;
			}
		}
		if(edgesdone > oldedgesdone) continue;

		for(j = 0; j < 4; j++){
			if(edges[j][0] == 5){		//found a bottom edge on the top face facing up.
				if(edgesdone == 0){
					turns = 0;
					refedge = (4 + edges[j][1] - (j+1)) % 4;
				}
				else turns = (8 + edges[j][1] - (j+1) - refedge) % 4;
				if(refedge == 0){
					if(turns > 0) turn_face((turns-1)*6); //turn U face
					face = 1 + j + turns;
					if(face > 4) face-=4;
				} else {
					dest = (turns + refedge) % 4;
					if(refedge > dest) dest +=4;
					if(refedge != dest){			//rotate to required refedge. update.
						turn_face(5 + (6*(dest - refedge - 1)));
						for(i=0; i<edgesdone; i++){
							doneedges[i] -= (dest - refedge);        //Update completed edge array.
							if(doneedges[i] < 8) doneedges[i] += 4;
						}
						refedge = dest % 4;								//update reference value.
					}
					face = 1 + j;
				}
				turn_face(6+face);	//turn side face twice, moving edge to bottom.
				doneedges[edgesdone] = face + 7;
				edgesdone++;
			}
		}
		if(edgesdone > oldedgesdone) continue;

		for(j=0; j<4; j++){
			done = 0;
			for(i=0; i<edgesdone; i++){
				if(doneedges[i] == j+8) done = 1;
			}
			if(done == 0){
				if(edges[j+8][0] == 5 || edges[j+8][1] == 5) {
					turn_face(j+1);								//move edge piece up into UD slice.
					break;
				}
			}
		}	
	}
	if(refedge != 0) turn_face(5 + ((4 - refedge) - 1)*6);		//turn bottom to match edges with center pieces.
}

unsigned char sanity_check_colors(void){
	unsigned char i,j,k, good=1;
	unsigned char colors[] = {0,0,0,0,0,0};
	for(i=0;i<6;i++){							//centers of each face should be different colors
		if(colors[from_sensor[i][1][1]] > 0) good = 0;
		colors[from_sensor[i][1][1]]++;
	}
	for(i=0;i<6;i++){
		for(j=0;j<3;j++){
			for(k=0;k<3;k++){
				if(j!=1 || k!=1) colors[from_sensor[i][j][k]]++; //count number of cubie faces of each color.
			}
		}
	}
	for(i=0;i<6;i++){					//should be 9 of each color.
		if(colors[i] != 9) good = 0;
	}
	return good;
}

unsigned char sanity_check_pieces(void){
	unsigned char i, j,  good=1;
	unsigned char piece, piece2;
	for(i=0;i<8;i++){	//corner should have one from each of these sets: (0,5) (1,3) (2,4)
		piece = 0;
		for(j=0; j<3; j++){
			switch(corners[i][j]){
				case 0:
				case 5:	piece += 1; break;
				case 1:
				case 3: piece += 2; break;
				default: piece += 4; break;
			}
		}
		if(piece != 7) good = 0;
	}
	for(i=0;i<12;i++){					//edges should have colors from different axes on them.
		switch(edges[i][0]){
			case 0:
			case 5:	piece = 1; break;
			case 1:
			case 3: piece = 2; break;
			default: piece = 4; break;
		}
		switch(edges[i][1]){
			case 0:
			case 5:	piece2 = 1; break;
			case 1:
			case 3: piece2 = 2; break;
			default: piece2 = 4; break;
		}
		if(piece == piece2) good = 0;
	}
	return good;
}

#endif