/*
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME:
 * ANDREW ID:
 * LAST UPDATE:
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 *
 */

#include "student.h"

 // Ignore this line until project 5
turtleMove studentTurtleStep(bool bumped) {
	return MOVE;
}

// OK TO MODIFY BELOW THIS LINE

#define TIMEOUT 40 // bigger number slows down simulation so you can see what's happening
float w, state;
float fx1, fy1, fx2, fy2;
float z, aend, mod, bp, q;

// this procedure takes the current turtle position and orientation and returns
// true=submit changes, false=do not submit changes
// Ground rule -- you are only allowed to call the helper functions "bumped(..)" and "atend(..)",
// and NO other turtle methods or maze methods (no peeking at the maze!)
bool studentMoveTurtle(QPointF& position_coord, int& new_orientation) {
	ROS_INFO("Turtle update Called  w=%f", w);
	mod = true;
	//if update is called 
	if (w == 0) {
		// set 
		fx1 = position_coord.x();
		fy1 = position_coord.y();
		fx2 = position_coord.x();
		fy2 = position_coord.y();
		if (new_orientation < 2)
			if (new_orientation == 0) fy2 += 1;
			else fx2 += 1;
		else {
			fx2 += 1;
			fy2 += 1;
			if (new_orientation == 2) fx1 += 1;
			else fy1 += 1;
		}
		bp = bumped(fx1, fy1, fx2, fy2);
		aend = atend(position_coord.x(), position_coord.y());
		if (new_orientation == 0)
			if (cs == 2) {
				new_orientation = 3;
				cs = 1;
			}
			else if (bp) {
				new_orientation = 1;
				cs = 0;
			}
			else cs = 2;
		else if (new_orientation == 1)
			if (cs == 2) {
				new_orientation = 0;
				cs = 1;
			}
			else if (bp) {
				new_orientation = 2;
				cs = 0;
			}
			else cs = 2;
		else if (new_orientation == 2)
			if (cs == 2) {
				new_orientation = 1;
				cs = 1;
			}
			else if (bp) {
				new_orientation = 3;
				cs = 0;
			}
			else cs = 2;
		else if (new_orientation == 3)
			if (cs == 2) {
				new_orientation = 2;
				cs = 1;
			}
			else if (bp) {
				new_orientation = 0;
				cs = 0;
			}
			else cs = 2;
		ROS_INFO("Orientation=%f  STATE=%f", new_orientation, cs);
		z = state == 2;
		mod = true;
		if (z == true && aend == false) {
			if (new_orientation == 1) position_coord.setY(position_coord.y() - 1);
			if (new_orientation == 2) position_coord.setX(position_coord.x() + 1);
			if (new_orientation == 3) position_coord.setY(position_coord.y() + 1);
			if (new_orientation == 0) position_coord.setX(position_coord.x() - 1);
			z = false;
			mod = true;
		}
	}
	if (aend) return false;
	if (w == 0) w = TIMEOUT;
	else w -= 1;
	if (w == TIMEOUT) return true;
	return false;
}