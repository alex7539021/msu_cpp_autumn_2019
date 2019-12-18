#pragma once 

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <thread>
#include <queue>
#include <iterator>

const size_t CHUNK = 1024 * 1024;
const std::string FileName = "input.txt";
const std::string newFileName = "output.txt";

void FileSort(const std::string &FileName);