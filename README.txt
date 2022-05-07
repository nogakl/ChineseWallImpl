/*
 * This file is part of ChineseWall.
 *
 * Developed for 22923 course final project by Noga Klein - Open University.
 * This product includes software developed by jsoncpp
 * (https://github.com/open-source-parsers/jsoncpp).
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 ================================================================================================
 An Implemetation For Chinese Wall Model

# Running command:
	Open the command line from the project directory, cd to Release and enter "ChineseWall" (same for Debug)

# Running UT command:
	Open the command line from the project directory, cd to Release and enter "ChineseWallUT" (same for Debug)


# Simulation Database:
	you can build the whole system based on json file: you can find them in the project directory.
	1 - as example1 is an empty system, you can add subject, objects (Files or Threads), permissions...
	and do some actions, as read or write, based on your and your DB rules.
	4 - same DB as in figure 13.6 [SB]

# Important information:
	1. The simulation can handle subjects and objects creation and deletion changes

	2. You can login as any subject you wish, 
	if the subject isn't exists in the system you, should register by its name (ie add it to the system)

	3. In this model you can't add permissions by yourself directly, but you can try to read/ write
	and if access accepted, the permission will be added automatically.

	4. The program's behavior is like a loop - 
		- in every iteration you can sign in as new user name, or the same as previous iteration.
		- you can choose between the commands: read, write, add subject, add object
		- in case of read cmd - you have to enter the object name, the position to start read from and how many bytes to read. 
		if the action succeed, the data will be printed to your screen.
		- in case of write cmd - you have to enter the object name, the position to start to write to, the string to write and how many bytes to write
		You can check this action by the relevant read action
		- in case of add a subject - you have to enter the new subject name
		- in case of add an object - you have to enter the new object name, its type (ie Thread or File) and its dataset.
		if the action succedd, you are the object's owner, in the next iteration you can try to get read/write access.
		-if you want to exit the program, enter 0 when you asked to.

# Simulation example:
	See 'simulation_figure13.6_sb.txt' for simulation example.
	You can see the next steps in the simulation output:
	1. The system created with one subject : admin
	2. login as admin and add a new subject, named John
	3. login as John and read file G
	4. Jhon write to file G (*-property) : "Hello"
	5. Jhon read from file G : "Hello"
	6. Jhon can't read from file H and I since those files in another dataset in the same CI of G
	7. Jhon read from file A
	8. Jhon can't read from file D since this file in another dataset in the same CI of A
	9. Jhon add a new subject, named Jane
	10. login as Jane and read file C and B (same DS)
	11. Jane can't read from file E since this file in another dataset in the same CI of B and C
	12. Jane read from file H and I
	13. Jane can't read from file G since this file in another dataset in the same CI of H and I

	============================================================================================================
	Now we can see *-property: the system prevent an indirect flow of information that 
	would cause a conflict : Jhon can't read the data from file G, that Jane can't read, and put it
	in file B, that Jane can read 
	============================================================================================================

	14. login as Jhon and read the data from file G : "Hello"
	15. John failed to write "Hello" to file B