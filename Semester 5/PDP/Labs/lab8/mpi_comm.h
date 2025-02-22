#pragma once
#include "mpi.h"
#include <sstream>
#include <iostream>


void sendSubscribe(char varName, int who, int to);
void sendUpdate(char varName, int newValue, int to);
int* getMessage();
