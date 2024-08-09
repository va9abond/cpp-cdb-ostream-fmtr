// Simple terminal(console?)*(1) output stream formatter.
//
// *(1) Terminal(console?) should support ANSI/VT100 escape sequences.
//
// style: bold | underlined | reversed | hidden;
// 3 bit - 8 colors: black | red | green | yellow | blue | magenta | cyan | gray;
// (no light versions)
//
// ESC CHAR: \e   (Windows, attr[ibute])
//           \033 (Unix, escapce char)
//           \x1B (Unix, escapce char)
//
// TODO [[maybe]] Extending styles
//      |
//      +-- italic | strikithrough
// TODO Windows support
// TODO Truecolor support (24 bit)
// TODO Extending print()
//      |
//      +-- Width of output (+ alignment: left | center | right)
// TODO [[maybe]] Fix naming by following the wikipedia
//      |
//      +-- ESC_ENTER --> SGR_BEGIN = CSI
//      |   ESC_EXIT  --> SGR_END
//      |
//      +-- add constexpr const char* ESC_CHAR_e
//      |       constexpr const char* ESC_CHAR_033
//      |       constexpr const char* ESC_CHAR_x1B
//      |
//      +-- ostream_attr --> display_attr
//      |
//      +-- send_esc_seq --> send_control_seq
//
// ---
#ifndef CST_OSTREAM_FMTR
#define CST_OSTREAM_FMTR 1


#include <iostream>
#include <initializer_list>

// \e | \033 | \x1B
#define ESC_CHAR "\033" // ESCAPE control character

namespace cst {
    // (Select Graphic Rendition) [SGR] = SCI n m
    constexpr const char* ESC_ENTER = ESC_CHAR"["; // = [CSI] Control Sequence Introducer
    constexpr const char* ESC_EXIT  = "m";

    enum class ostream_attr : int {
        reset_ostream_fmt = 0, // resets all *attributes*

        bold_on       =  1, // -----------------------------
        bold_off      = 21, //                         Style
        underline_on  =  4,
        underline_off = 24,
        reverse_on    =  7,
        reverse_off   = 27,
        hidden_on     =  8,
        hidden_off    = 28, // -----------------------------

        fg_black      = 30, // -----------------------------
        fg_red        = 31, //                        Colors
        fg_green      = 32, //                 3-bit palette
        fg_yellow     = 33,
        fg_blue       = 34,
        fg_magenta    = 35,
        fg_cyan       = 36,
        fg_gray       = 37,
        fg_default    = 39,

        bg_black      = 40,
        bg_red        = 41,
        bg_green      = 42,
        bg_yellow     = 43,
        bg_blue       = 44,
        bg_magenta    = 45,
        bg_cyan       = 46,
        bg_gray       = 47, //                      8 colors
        bg_default    = 49, // -----------------------------
    };



    // NOTE why I implicitly passing ostream type? because I want it works
    //      with std::cerr also
    inline void send_esc_seq (std::initializer_list<ostream_attr> attrs,
                              std::ostream& os = std::cout) {
        os << ESC_ENTER;
        for (const ostream_attr& attr : attrs)
            os << ";" << static_cast<int>(attr);
        os << ESC_EXIT;
    }

    inline void reset_ostream_format (std::ostream& os = std::cout) {
        send_esc_seq({ostream_attr::reset_ostream_fmt}, os);
    }

    inline std::ostream& operator<< (std::ostream& os, ostream_attr attr) {
        return os << ESC_ENTER
                  << static_cast<int>(attr)
                  << ESC_EXIT;
    }

    template <typename ty>
    void print (const ty& print_what,
                std::initializer_list<ostream_attr> print_how,
                std::ostream& print_where = std::cout) {
        send_esc_seq(print_how);
        print_where << print_what;
        reset_ostream_format();
    }

    template <typename ty>
    void println (const ty& print_what,
                  std::initializer_list<ostream_attr> print_how,
                  std::ostream& print_where = std::cout) {
        print(print_what, print_how, print_where);
        print_where << "\n";
    }
};


#endif // CST_OSTREAM_FMTR
