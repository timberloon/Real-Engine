#include "novapch.h"
#include "input/input.h"
#include "input/glfwinput.h"

namespace nova {

    // Create the GLFW platform instance.
    // Swap this line for a different platform implementation when porting.
    input* input::s_instance = new glfw_input();

} // namespace nova