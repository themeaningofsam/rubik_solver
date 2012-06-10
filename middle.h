/* Author Sam Muir
3/23/2010 */
#ifndef _MIDDLE
#define _MIDDLE

#include "cube.h"


unsigned char cornersdone[4] = {0,0,0,0};
unsigned char stage2_table[23][9] = {//lookup table for stage two moves. Source:http://www.ws.binghamton.edu/fridrich/Mike/middle.html
	//moves are flipped so top and bottom are switched. comments give reference numbers to moves on website.
	{20,20,20,20,20,20,20,20,20},	    //0
	{7,6,16,7,4,6,1,12,1},				//2	
	{7,6,1,0,13,0,1,6,1},				//1
	{13,0,13,12,14,0,2,7,20},			//3
	{0,4,12,16,12,13,0,1,20},			//8
	{4,12,10,1,4,13,20,20,20},			//9
	{13,12,1,0,13,12,1,20,20},			//10	
	{7,12,7,12,7,6,7,20,20},			//5b
	{0,13,0,1,6,13,0,1,20},				//4
	{13,0,1,4,6,16,20,20,20},			//7
	{0,13,12,1,12,4,0,16,20},			//6
	{4,6,16,12,4,0,16,20,20},		//16
	{6,7,6,1,0,13,0,7,20},		//15
	{16,1,4,13,20,20,20,20,20},		//11	
	{0,13,0,1,12,13,12,1,20},		//13
	{4,3,2,12,14,15,16,20,20},		//14a	
	{12,4,6,16,0,13,12,1,20},		//12
	{6,13,12,7,16,13,4,20,20},		//21
	{0,4,6,10,1,4,13,20,20},		//22
	{12,4,12,16,0,13,12,1,20},		//20
	{12,4,6,16,6,4,12,16,20},		//17
	{12,4,0,16,6,4,12,16,20},		//19
	{13,12,1,20,20,20,20,20,20}		//18
};

unsigned char find_corner(unsigned char correctplace);
unsigned char find_edge(unsigned char correctplace);
unsigned char find_move(unsigned char cornercorrect, unsigned char edgeplace, unsigned char cornerrot, unsigned char edgerot);
void middle(void);
void release_pieces(void);



unsigned char find_corner(unsigned char correctplace){		//correct place must be between 4 and 7
	unsigned char i, j, goodcorner, p1, p2, p3;
	p1 = 5;				//possible corner color.
	p2 = correctplace - 3;
	p3 = correctplace - 2;
	if(p3 == 5) p3 = 1;
	for(i=0; i<8; i++){
		goodcorner = 1;
		for(j=0; j<3; j++){
			if(!(corners[i][j] == p1 || corners[i][j] == p2 || corners[i][j] == p3)) goodcorner = 0;
		}
		if(goodcorner == 1) return i;
	}
	return 8;		//should never occur.
}


unsigned char find_edge(unsigned char correctplace){		//correctplace must be between 4 and 7.
	unsigned char i, j, goodedge, p1, p2;
	p1 = correctplace - 3;
	p2 = correctplace - 2;
	if(p2 == 5) p2 = 1;
	for(i=0; i<8; i++){
		goodedge = 1;
		for(j=0; j<2; j++){
			if(!(edges[i][j] == p1 || edges[i][j] == p2)) goodedge = 0;
		}
		if(goodedge == 1) return i;
	}
	return 12;		//should never occur.
}


unsigned char find_move(unsigned char cornercorrect, unsigned char edgeplace, unsigned char cornerrot, unsigned char edgerot){
	if(cornercorrect == 1){			//corner in right spot
		if(edgeplace == 7){			//edge in right spot
			if(edgerot == 0){		//edge is correctly oriented
				switch(cornerrot){
					case 0: return 0;	//move 0 (no move necessary)
					case 1: return 25;	//move 2 flipped. (flip = add 23)
					default: return 2;	//move 2
				}
			}else{
				switch(cornerrot){
					case 0: return 1;	//move 1 
					case 1: return 26;	//move 3 flipped. (flip = add 23)
					default: return 3;	//move 3
				}
			}
		} else {
			if(edgeplace == 0){		//edge is above its color. edgeplace should only equal 0 or 3.
				switch(cornerrot){
					case 0: return 4;
					case 1: return 6;	
					default: return 28;	//move 5 flipped
				}
			}else{
				switch(cornerrot){
					case 0: return 27;	//move 4 flipped
					case 1: return 5;	
					default: return 29;	//move 6 flipped
				}
			}
		}
	} else {
		if(edgeplace == 7){  //edge is in right place but corner is not.
			if(edgerot == 0){
				switch(cornerrot){
					case 0: return 7;	
					case 1: return 8;	
					default: return 31;	//move 8 flipped
				}
			}else{
				switch(cornerrot){
					case 0: return 9;	
					case 1: return 10;	
					default: return 33;	//move 10 flipped
				}
			}
		} else { //edge and corner both out of place. Corner is above where it wants to be. lets look at the edge.
			if(edgeplace == 0 || edgeplace == 3){ //edge and corner are touching.   HERE!!!!!!!!
				if(edgeplace == 0){
					if(edgerot == 0){
						switch(cornerrot){
							case 0: return 34;		//move 11 flipped	
							case 1: return 36;		//move 13 flipped
							default: return 14;	
						}
					} else {
						switch(cornerrot){
							case 0: return 35;	//move 12 flipped
							case 1: return 39;	//move 16 flipped
							default: return 15;
						}
					}
				}else{
					if(edgerot == 0){
						switch(cornerrot){
							case 0: return 11;	
							case 1: return 37;		//14 flipped	
							default: return 13;
						}
					} else {
						switch(cornerrot){
							case 0: return 12;	
							case 1: return 38;		//move 15 flipped	
							default: return 16;	
						}
					}
				}
			} else {		// corner and edge not touching.
				if(edgeplace == 1){
					if(edgerot == 0){
						switch(cornerrot){
							case 0: return 40; //move 17 flipped	
							case 1: return 42; // move 19 flipped	
							default: return 20;	
						}
					} else {
						switch(cornerrot){
							case 0: return 41;	//move 18 flipped	
							case 1: return 44;	// move 21 flipped
							default: return 22;	
						}
					}
				}else{
					if(edgerot == 0){
						switch(cornerrot){
							case 0: return 17;	
							case 1: return 43;	//move 20 flipped
							default: return 19;	
						}
					} else {
						switch(cornerrot){
							case 0: return 18;	
							case 1: return 45;	//move 22 flipped	
							default: return 21;	
						}
					}
				}
			}
		}
	}
}

void middle(void){
	unsigned char i=3, k, donecorners=0, edgeplace, cornerplace, edgerot, cornerrot, turns, cornercorrect, move, flipped, thismove, front, edge_offset;
	unsigned char desperate = 0;
	for(k=0;k<4;k++) cornersdone[k] = 0;
	while(donecorners<4){					//search through lower corners to find any with edge or corner in right spot already.
		i++;		//look at next corner.
		if(i>7){
			if(desperate == 0){
				desperate = 1;		//loop through again, this time allowing edges/corners both not in right spot.
			} 
			else release_pieces();
			i=4;
		}
		if(cornersdone[i-4] == 1) continue;		//corner has already been fixed.
		edgeplace = find_edge(i);
		cornerplace = find_corner(i);
		if(edgeplace != i && cornerplace != i && desperate == 0) continue;	//neither piece is in correct spot. we'll get to these later.
		if(edgeplace != i && edgeplace > 3) continue;		//edge piece not accessible. skip.
		if(cornerplace != i && cornerplace > 3) continue;	//corner piece not accessible. skip.
		if(cornerplace != i && i-cornerplace != 4){
				turns = ((i-cornerplace)%4);		//number of times top needs turned clockwise.
				turn_face(6*(turns-1)); //rotate top to get corner piece above where it should be.
				cornerplace = i-4;		//set new cornerplace.
				if(edgeplace != i) edgeplace = (edgeplace + turns) % 4;		//set new edgeplace.
		}
		if(corners[cornerplace][0] == 0 || corners[cornerplace][0] == 5) cornerrot = 0;		//find rotation of corner to be placed. 
		else {																				//0=normal 1=clockwise 2=counterclockwise
			if(corners[cornerplace][1] == 0 || corners[cornerplace][1] == 5){
				cornerrot = (cornerplace % 2) + 1;
				if (cornerplace > 3) cornerrot = 3 - cornerrot;
			}else{
				cornerrot = ((cornerplace + 1) % 2) + 1;
				if (cornerplace > 3) cornerrot = 3 - cornerrot;
			}
		}
		if(edgeplace != i && cornerplace == i){
			if(edges[edgeplace][1] == i-3) turns = (i-edgeplace)%4;		//turns to get lower side of edge piece to match its face.
			else turns = ((i-edgeplace)+1)%4;
			if(turns != 0){
				turn_face(6*(turns-1));
				edgeplace = (edgeplace + turns) % 4;		//set new edge place.
			}
			edgerot = 0;
		} else {
			if(edgeplace == i){
				if(edges[i][0] == 1 || edges[i][0] == 3) edgerot = 0;
				else edgerot = 1;
			} else {
				if((edges[edgeplace][1]%2) == ((edgeplace + 1)%2)) edgerot = 0;
				else edgerot = 1;
			}
		}
		cornercorrect = 0;
		if(cornerplace == i) cornercorrect = 1;
		if(edgeplace > 3) edge_offset = 7;
		else edge_offset = (edgeplace + 8 - i - 1) % 4;
		move = find_move(cornercorrect, edge_offset, cornerrot, edgerot);
		flipped = 0;
		if(move > 22) { //moves need to be flipped for the sequence.
			flipped = 1;
			move -= 23;
		}
		front = (i + 2) % 4;
		if (front == 0) front = 4;
		for(k=0;k<9;k++){
			thismove = stage2_table[move][k];
			if(thismove==20) break;
			if(flipped == 1) thismove = flip_move(thismove);		//flip move if necessary
			thismove = translate_front_move(front, thismove);				//translate move.
			turn_face(thismove);		//complete each move from the table.
		}
		donecorners++;
		cornersdone[i-4]=1;		//corner has now been fixed.
		desperate = 0;
		i = 3;
	}
}

void release_pieces(void){
	unsigned char front = 4, i, j, desperate = 0, top = 4;
	unsigned char corner_options[4] = {2,2,2,2};
	unsigned char top_options[4] = {0,0,0,0};
	for(i=0; i<4; i++){
		for(j=0; j<3; j++){
			if(corners[i+4][j] == 0) corner_options[i]--;
			if(corners[(i+3)%4][j] == 0) top_options[i]++;
			if(j < 2){
				if(edges[i+4][j] == 0) corner_options[i]--;
				if(edges[i][j] == 0) top_options[i]++;
			}
		}
		if(cornersdone[i] == 1) {
			corner_options[i] = 0;
		}
	}
	for(i=0;i<4;i++){
		if(corner_options[i] == 2 || (desperate == 1 && corner_options[i] == 1)){
			front = i;
		}
		if(front != 4) break;
		if(i == 3) {
			desperate = 1;
			i = 0;
		}
	}
	desperate = 0;
	j = i;
	while(1){
		if(top_options[j] == 2 || (desperate == 1 && top_options[j] == 1)){
			top = j;
		}
		if(top != 4) break;
		j++;
		if(j > 3) j = 0;
		if(j == i) {
			desperate = 1;
		}
	}
	if(front != top) turn_face(6*(((4 + front - top)%4)-1));
	turn_face(translate_front_move(front + 1, 14));
	turn_face(translate_front_move(front + 1, 0));
	turn_face(translate_front_move(front + 1, 2));
}

#endif