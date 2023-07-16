/*
	Adjusted from the original file https://github.com/apache/thrift/blob/master/tutorial/tutorial.thrift.
	
	LICENCE for Original: 
	 * Licensed to the Apache Software Foundation (ASF) under one
	 * or more contributor license agreements. See the NOTICE file
	 * distributed with this work for additional information
	 * regarding copyright ownership. The ASF licenses this file
	 * to you under the Apache License, Version 2.0 (the
	 * "License"); you may not use this file except in compliance
	 * with the License. You may obtain a copy of the License at
	 *
	 *   http://www.apache.org/licenses/LICENSE-2.0
	 *
	 * Unless required by applicable law or agreed to in writing,
	 * software distributed under the License is distributed on an
	 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
	 * KIND, either express or implied. See the License for the
	 * specific language governing permissions and limitations
	 * under the License.

		# Thrift Tutorial
		# Mark Slee (mcslee@facebook.com)
		#

	* Changes made by Dustin Clark on 2023-07-16
*/

namespace cpp calculator

const i32 WINDOW_WIDTH = 320
const i32 WINDOW_HEIGHT = 416

const i32 BUTTON_SIZE_X = 48
const i32 BUTTON_SIZE_Y = 48

enum Operation 
{
  ADD = 1,
  SUBTRACT = 2,
  MULTIPLY = 3,
  DIVIDE = 4
}

struct Work 
{
  1: i32 num1 = 0,
  2: i32 num2,
  3: Operation op,
  4: bool bNumFirstNumSet = false,
  5: bool bNumSecondNumSet = false,
}


exception InvalidOperation 
{
  1: i32 op,
  2: string why
}

service Calculator
{
   i32 calculate(1:Work w) throws (1:InvalidOperation io),
}
