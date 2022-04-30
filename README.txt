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
	option 1 : Open VS and Set "ChineseWall" As Stratup Project and than use local Windows Debugger
	option 2 : Open the command line from the project directory, enter "Release\ChineseWall" (same for Debug)

# Simulation Database:
	you can build the whole system based on json file, you can find them in the project directory.
	1 - as example1 is an empty system, you can add subject, objects (Files or Threads), permissions...
	and do some actions, as read or write, based on your and your DB rules.

# Important information:
	1. The simulation can handle subjects and objects creation and deletion changes

	2. You can login as any subject you wish, 
	if the subject isn't exists in the system you should register by its name (ie add it to the system)

	3. In this model you can't add permissions by yourself directly, but you can try to read/ write
	and if access accepted, the permission will be added automatically.

# Simulation example:
	See 'simulation_example.txt' for simulation example