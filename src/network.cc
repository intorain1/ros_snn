#include "train.h"
#include "model.h"
#include "reader/mnist/mnist.h"
#include "gnuplot.h"
#include "drafting.h"
#include "file_recorder.h"
#include "evaluation.h"
#include "file_read.h"

#include <cuda_runtime.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>

using namespace std;

#include "../global.h"
#include "../model_CODE/definitions.h"