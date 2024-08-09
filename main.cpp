#include <iostream>
#include "cst_ostream_fmtr.hpp"

// "{ESC_CHAR}[{FORMAT_ATTRIBUTE};{FORGROUND_COLOR};{BACKGROUND_COLOR}m{TEXT}\033[{RESET_FORMATE_ATTRIBUTE}m"

int main() {
    using std::cout;
    using enum cst::ostream_attr;

    cout << "this just a normal text" << "\n";


    cst::send_esc_seq({bold_on, fg_red, bg_gray});
    cout << "this text has ugly formatting";
    cst::reset_ostream_format();
    cout << "\n";


    cout << "this just a normal text" << "\n";


    cst::println("this text has nice formatting", {bg_yellow, fg_black, underline_on, bold_on});


    cout << "this just a normal text" << "\n";


    cout << bg_red << fg_black << bold_on << "[ERROR]" << reset_ostream_fmt << ": something goes wrong" << "\n";
    cout << bg_green << fg_black << bold_on << "[SUCCESS]" << reset_ostream_fmt << ": good job, dude" << "\n";
    cout << bg_yellow << fg_black << underline_on << bold_on << "[WARNING]" << reset_ostream_fmt << ": wtf just happend?" << "\n";


    cout << "this just a normal text" << "\n";

    return 0;
}
