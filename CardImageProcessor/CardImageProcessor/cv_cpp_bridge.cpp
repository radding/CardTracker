/** A file that defines the bridge for Python -> C and C -> C++
*/

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <ios>

#include "cv_cpp_bridge.h"
#include "Card.h"

using std::string;
using std::vector;
using std::ofstream;
using cv::Mat;

typedef unsigned char byte;

extern "C" {
	/**Python facing function
	* This is the python facing function that calls the CPP code. and open CV.
	* The python arguments are a byte string representing some image and a 
	* an int representing the height and the width.
	* will return a touple wit card info.
	*/

	static PyObject * image_process(PyObject *self, PyObject *args) {
	    const char *command;
	    if (!PyArg_ParseTuple(args, "s", &command))
	        return NULL;
	    //char **credit_card;
            
            Mat image = cv::imread(command, 1);
            //process_image(image);
            string ccn = processImage(image, command);
	    return Py_BuildValue("s", ccn.c_str());
	}
	
	static PyMethodDef SpamMethods[] = {
	    {"process",  image_process, METH_VARARGS,
	     "Process an image"},
	    {NULL, NULL, 0, NULL}        /* Sentinel */
	};
	
	PyMODINIT_FUNC
	initimage(void)
	{
	    (void) Py_InitModule("image", SpamMethods);
	}
	
	char** process_image(Mat img) {
            
            cv::imwrite("test_image.jpg", img);
            return NULL;
	}
 
}
